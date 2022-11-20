workspace "Ether"
    architecture "x86_64"
    startproject "Sandbox"
    configurations { "Debug", "Release", "Dist" }

project "Ether"
    location "Ether"
    kind "SharedLib"
    language "C++"
    staticruntime "Off"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files 
    { 
        "%{prj.name}/src/**.cpp", 
        "%{prj.name}/src/**.h" 
    }

    includedirs 
    { 
        "%{prj.name}/src" 
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        { 
            "ETH_PLATFORM_WINDOWS",
            "ETH_BUILD_DLL"
        }

        postbuildcommands { "{COPY} %{cfg.buildtarget.relpath} ../bin/%{cfg.buildcfg}/Sandbox-%{cfg.system}-%{cfg.buildcfg}" }

    filter { "configurations:Debug", "system:Windows" }
        defines "ETH_DEBUG"
        symbols "On"
        buildoptions "/MDd"
        runtime "Debug"

    filter { "configurations:Release", "system:Windows" }
        defines "ETH_RELEASE"
        symbols "Off"
        buildoptions "/MD"
        optimize "On"
        runtime "Release"

    filter { "configurations:Dist", "system:Windows" }
        defines "ETH_DIST"
        symbols "Off"
        buildoptions "/MD"
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
        buildoptions "/MDd"
        runtime "Debug"

    filter { "configurations:Release", "system:windows" }
        defines "ETH_RELEASE"
        symbols "Off"
        buildoptions "/MD"
        optimize "On"
        runtime "Release"

    filter { "configurations:Dist", "system:windows" }
        defines "ETH_DIST"
        symbols "Off"
        buildoptions "/MD"
        optimize "On"
        runtime "Release"