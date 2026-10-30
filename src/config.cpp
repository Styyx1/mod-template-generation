#include "config.hpp"
#include "toml11/parser.hpp"
#include "toml11/result.hpp"
#include <cstdio>
#include <expected>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <print>
#include <stdexcept>

#define EMPTY "'\n"

#ifdef DEBUG
constexpr auto FNAME = "xmake_test.lua";
#else
constexpr auto FNAME = "xmake.lua";
#endif

namespace CONF{

    template <typename... Args>
    void LogIt(std::format_string<Args...> fmt, Args&&... args)
    {
#ifdef DEBUG
    std::println(fmt, std::forward<Args>(args)...);
#endif
    }

// read toml file with the settings that change per mod. easier to work with toml than passing a bunch of arguments to a cli tool imo
std::expected<ModConfig, std::string> ParseConfig() {

    ModConfig m {};

    try{
        const auto config = toml::parse("moddata.toml");

        m.name = toml::find<std::string>(config, "modname");
        LogIt("found config modname it is: {}", m.name);

        m.description = toml::find<std::string>(config, "description");
        LogIt("found config description, it is: {}", m.description);

        m.license = toml::find<std::string>(config, "license");
        LogIt("found config license, it is: {}", m.license);

        m.version = toml::find<std::string>(config, "modversion");
        LogIt("found config version, it is: {}", m.version);

        const auto& configs = toml::find(config, "Configs");

        if (!configs.is_table())
            //Note: TOML table means [Configs] in the toml file. not sure if case sensitive, i just assume it is
            return std::unexpected("Configs must be a TOML table");

        for (const auto& [key, value] : configs.as_table())
        {
            if (value.is_boolean())
            {
                m.settings.emplace_back(key, value.as_boolean());
            }
        }

        for (const auto& [name, enabled] : m.settings)
        {
            LogIt("{} = {}", name, enabled);
        }

    }
    catch (const toml::exception& err){
        std::cerr << "Failed to parse moddata.toml:\n" << err.what() << '\n';
        return std::unexpected(std::string{err.what()});
    };
    return m;
}
//load lua file as string for replacements later
//https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c
std::string LoadLua() {

    std::ifstream file(FNAME);

    if(!file){
        throw std::runtime_error("Can't open xmake.lua file");
    }

    return {
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };

}

void ReplaceAll(std::string &text, std::string_view placeholder,
                std::string_view replacement) {

                    std::size_t pos = 0;

                    while ((pos = text.find(placeholder, pos)) != std::string::npos){
                        text.replace(pos, placeholder.size(), replacement);
                        pos += replacement.size();
                    }
}
std::string GenerateConfStr(const ModConfig &conf) {

    //can not create empty string here cause it'll cause it to put a ' into a line apparently
    std::string result;

    for (const auto& [setting, enabled] : conf.settings){

        result += std::format(
            "set_config(\"{}\", {})\n",
            setting,
            enabled ? "true" : "false"
        );

    }
    return result;
}
void WriteLuaFile(const std::string &contents) {


    std::ofstream file(FNAME);

    if(!file){
        throw std::runtime_error("could not create xmake.lua file");
    }

    file << contents;

    if(!file){
        throw std::runtime_error("could not write to lua file");
    }

};

std::string ReplaceLua(const ModConfig& conf) {


    auto lua = LoadLua();

    if(lua.empty()){
        return EMPTY;
    }

    ReplaceAll(lua, "{{MOD_NAME}}", conf.name);
    ReplaceAll(lua, "{{MOD_DESC}}", conf.description);
    ReplaceAll(lua, "{{MOD_VERSION}}", conf.version);
    ReplaceAll(lua, "{{MOD_LICENSE}}", conf.license);
    ReplaceAll(lua, "{{ADDITIONAL_CONFIGS}}", GenerateConfStr(conf));

    return lua;
}
void GenerateTemp() {

    auto conf = ParseConfig();
    if(!conf){
        std::println("Config error: {}", conf.error());
        return;
    }

    auto lua = ReplaceLua(*conf);
    WriteLuaFile(lua);
}

// simple check to see if lua exists cause it will get replaced
// the template should come with one anyway
bool IsLuaPresent()
{
    return std::filesystem::is_regular_file(FNAME);
}

// moddata.toml must exist to grab settings for the .lua file
bool IsConfigPresent()
{
    return std::filesystem::is_regular_file("moddata.toml");
}

} // namespace CONF
