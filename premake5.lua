project "yaml-cpp"
    kind "StaticLib"
    language "C"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- bin/Debug-Windows-x64/GLFW 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- bin-int/Debug-Windows-x64/GLFW

    files
    {
        "include/**.h",
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        -- staticruntime "On"

        defines
        {
            "YAML_CPP_STATIC_DEFINE",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        staticruntime "off"
        runtime "Debug"