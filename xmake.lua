if is_plat("windows") then
    add_cxxflags("cl::/std:c++23preview", {force = true})
else
    set_languages("c++23")
end
add_requires("toml11")
add_rules("mode.debug", "mode.release")

if is_mode("debug") then
    add_defines("DEBUG")
end

target("tempgen")
    add_packages("toml11", {public=true})
    set_kind("binary")
    set_pcxxheader("src/pch.h")
    add_files("src/*.cpp")
    add_headerfiles("src/**.hpp")
