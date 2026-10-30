#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <toml.hpp>
#include <filesystem>
#include <utility>

//here is the .lua file this tool replaces.
//placeholders are mandatory (could probably be made better and more dynamic but it does the trick for me)

/*
if is_plat("windows") then
    add_cxxflags("cl::/std:c++23preview", {force = true})
else
    set_languages("c++23")
end

local clib_path = os.getenv("CLIB_PATH")
local util_path = os.getenv("ST_UTIL_PATH")

includes(clib_path, util_path)
local MOD_NAME = {{MOD_NAME}}
local MOD_VERSION = {{MOD_VERSION}}
local MOD_DESC = {{MOD_DESC}}
local MOD_LICENSE = {{MOD_LICENSE}}
set_project(MOD_NAME)
set_version(MOD_VERSION)
set_license(MOD_LICENSE)
set_warnings("allextra")

-- xmake rules
add_rules("mode.debug", "mode.releasedbg")
set_defaultmode("releasedbg")
--add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"}) --useful for clion or vscode
add_rules("plugin.vsxmake.autoupdate")
includes("xmake-rules.lua")

-- commonlib options
if get_config("skyrim_ae") == nil then
    set_config("skyrim_ae", true)
end

{{ADDITIONAL_CONFIGS}}

-- add plugin target
target(MOD_NAME)
    add_deps("commonlibsse", {public = true})
    add_deps("styyx-util", {public = true})

    if has_config("skyrim_ae") then
        set_targetdir("build/AE/skse/plugins")
    else
        set_targetdir("build/SE/skse/plugins")
    end

    add_rules("skse-template.plugin", {
        name = MOD_NAME,
        author = "styyx",
        description = MOD_DESC
    })

    if has_config("skyrim_ae") then
        add_defines("SKSE_TEMPLATE_SKYRIM_AE=1", { public = true })
    else
        add_defines("SKSE_TEMPLATE_SKYRIM_SE=1", { public = true })
    end

    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")
*/
