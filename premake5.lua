workspace "Ether"
    architecture "x86_64"
    startproject "Sandbox"
    configurations { "Debug", "Release", "Dist" }

IncludeDirs = {}
IncludeDirs["GLFW"] = "Ether/vendor/GLFW/include"
IncludeDirs["ImGui"] = "Ether/vendor/imgui"
IncludeDirs["Glad"] = "Ether/vendor/Glad/include"

group "Denepdencies"
    include "Ether/vendor/GLFW"
    include "Ether/vendor/Glad"
    include "Ether/vendor/imgui"
group ""

project "Ether"
    location "Ether"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files 
    { 
        "%{prj.name}/src/**.cpp", 
        "%{prj.name}/src/**.h" 
    }

    includedirs 
    { 
        "%{prj.name}/src", 
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.Glad}"
    }

    links
    {
		"GLFW",
		"Glad",
        "ImGui",
		"opengl32.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        { 
            "ETH_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE",
            "ETH_BUILD_DLL"
        }

        postbuildcommands { "{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}/Sandbox-%{cfg.system}-%{cfg.buildcfg}" }

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
    staticruntime "Off"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files 
    { 
        "%{prj.name}/src/**.cpp"
    }

    includedirs 
    { 
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