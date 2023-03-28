project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        buildoptions "/MTd"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"