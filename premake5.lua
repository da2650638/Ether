workspace "Ether"
    architecture "x86_64"
    startproject "Sandbox"
    configurations { "Debug", "Release", "Dist" }

IncludeDirs = {}
IncludeDirs["spdlog"] = "Ether/vendor/spdlog/include"
IncludeDirs["GLFW"] = "Ether/vendor/GLFW/include"
IncludeDirs["Glad"] = "Ether/vendor/Glad/include"

group "Dependencies"
    include "Ether/vendor/spdlog"
    include "Ether/vendor/GLFW"
    include "Ether/vendor/Glad"
group ""

project "Ether"
    location "Ether"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    pchheader "etherpch.h"
    pchsource "Ether/src/ether.cpp"

    files 
    { 
        "%{prj.name}/src/**.cpp", 
        "%{prj.name}/src/**.h" 
    }

    includedirs 
    { 
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}",
        "%{prj.name}/src" 
    }

    links
    {
        "GLFW",
        "Glad"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        { 
            "ETH_PLATFORM_WINDOWS",
            "ETH_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter { "configurations:Debug", "system:Windows" }
        defines "ETH_DEBUG"
        symbols "On"
        buildoptions "/MTd"
        runtime "Debug"

    filter { "configurations:Release", "system:Windows" }
        defines "ETH_RELEASE"
        symbols "Off"
        buildoptions "/MT"
        optimize "On"
        runtime "Release"

    filter { "configurations:Dist", "system:Windows" }
        defines "ETH_DIST"
        symbols "Off"
        buildoptions "/MT"
        optimize "On"
        runtime "Release"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files 
    { 
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    { 
        "%{IncludeDirs.spdlog}",
        "Ether/src" 
    }

    links
    {
        "Ether"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        defines 
        { 
            "ETH_PLATFORM_WINDOWS"
        }

    filter { "configurations:Debug", "system:windows" }
        defines "ETH_DEBUG"
        symbols "On"
        buildoptions "/MTd"
        runtime "Debug"

    filter { "configurations:Release", "system:windows" }
        defines "ETH_RELEASE"
        symbols "Off"
        buildoptions "/MT"
        optimize "On"
        runtime "Release"

    filter { "configurations:Dist", "system:windows" }
        defines "ETH_DIST"
        symbols "Off"
        buildoptions "/MT"
        optimize "On"
        runtime "Release"