workspace "Ether"
    architecture "x86_64"
    startproject "EtherNut"
    configurations { "Debug", "Release", "Dist" }

IncludeDirs = {}
IncludeDirs["spdlog"] = "Ether/vendor/spdlog/include"
IncludeDirs["GLFW"] = "Ether/vendor/GLFW/include"
IncludeDirs["Glad"] = "Ether/vendor/Glad/include"
IncludeDirs["imgui"] = "Ether/vendor/imgui"
IncludeDirs["glm"] = "Ether/vendor/glm"
IncludeDirs["stb_image"] = "Ether/vendor/stb_image"
IncludeDirs["entt"] = "Ether/vendor/entt/include"
IncludeDirs["yaml_cpp"] = "Ether/vendor/yaml-cpp/include"
IncludeDirs["ImGuizmo"] = "Ether/vendor/ImGuizmo"

group "Dependencies"
    include "Ether/vendor/spdlog"
    include "Ether/vendor/GLFW"
    include "Ether/vendor/Glad"
    include "Ether/vendor/imgui"
    include "Ether/vendor/glm"
    include "Ether/vendor/yaml-cpp"
group ""

project "Ether"
    location "Ether"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    pchheader "etherpch.h"
    pchsource "Ether/src/ether.cpp"

    files 
    { 
        "%{prj.name}/src/**.cpp", 
        "%{prj.name}/src/**.h",
        "%{prj.name}/vendor/glm/glm/*.hpp",
		"%{prj.name}/vendor/glm/glm/*.inl",
        "%{prj.name}/vendor/stb_image/stb_image.h",
        "%{prj.name}/vendor/stb_image/stb_image.cpp",
        "%{prj.name}/vendor/entt/include/entt.hpp",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"   
    }

    includedirs 
    { 
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb_image}",
        "%{IncludeDirs.entt}",
        "%{IncludeDirs.yaml_cpp}",
        "%{IncludeDirs.ImGuizmo}",
        "%{prj.name}/src" 
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib"
    }

    filter "files:%{prj.name}/vendor/ImGuizmo/**.cpp"
        flags { "NoPCH" }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        { 
            --"ETH_PLATFORM_WINDOWS",
            "ETH_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "GRAPHICS_API_OPENGL"
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

project "EtherNut"
    location "EtherNut"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    
    files 
    { 
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/assets/shaders/**.glsl",
        "%{prj.name}/assets/textures/**.png"
    }
    
    includedirs 
    { 
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb_image}",
        "%{IncludeDirs.entt}",
        "%{IncludeDirs.yaml_cpp}",
        "%{IncludeDirs.ImGuizmo}",
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

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files 
    { 
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/assets/shaders/**.glsl",
        "%{prj.name}/assets/textures/**.png"
    }

    includedirs 
    { 
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb_image}",
        "%{IncludeDirs.entt}",
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