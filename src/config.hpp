#include <expected>
#include <format>
namespace CONF{


    struct ModConfig{
        std::string name;
        std::string description;
        std::string version;
        std::string license;

        std::vector<std::pair<std::string, bool>> settings;
    };

    std::expected<ModConfig, std::string> ParseConfig();
    std::string LoadLua();
    void ReplaceAll(std::string &text, std::string_view placeholder,
                    std::string_view replacement);
    std::string GenerateConfStr(const ModConfig &conf);
    void WriteLuaFile(const std::string &contents);
    std::string ReplaceLua(const ModConfig& conf);
    void GenerateTemp();
    bool IsLuaPresent();
    bool IsConfigPresent();
}
