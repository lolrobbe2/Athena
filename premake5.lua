newoption {
    trigger = "enable-WSL",
    description = "enable Windows Subsytem For linux building",
    category    = "Build Options"
}

newoption {
    trigger = "no-sandbox",
    description = "disable sandbox project",
    category    = "Build Options"
}

newoption {
    trigger     = "lib-type",
    value       = "LIB-TYPE",
    description = "Choose a library type Shared or static",
    default     = "SharedLib",
    category    = "project Options",
    allowed = {
        { "SharedLib","Shared"},
        { "StaticLib","Static"}
    }
}

newoption {
    trigger     = "api-type",
    value       = "API-TYPE",
    description = "Choose an api type (C-API is needed for bindings) enables extern c or dllexport",
    default     = "CPP",
    category    = "project Options",
    allowed = {
        { "C","C-API"},
        { "CPP","CPP-API" },
        { "COMBINED"},
        { "NONE","none"}
    }
}

flags
{
    "MultiProcessorCompile"
}



startproject "sandbox"
workspace "Athena"
    architecture "x64"
    
    configurations
    {
        "debug",
        "release",
        "distribution"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

buildmessage("$(VULKAN_SDK)/Include")
IncludeDir = {}
IncludeDir["Athena"] =  "%{wks.location}/Athena/src"
IncludeDir["LZ4"] = "%{wks.location}/Athena/src/thirdparty/LZ4"

group"core"
project "Athena"
    location "Athena"
    kind(_OPTIONS["lib-type"])
    language "c++"
    targetdir("%{wks.location}/bin/" .. outputdir .. "/x64/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/x64/%{prj.name}")
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }
    includedirs
    {
        "%{IncludeDir.Athena}"
    }
    if _OPTIONS["lib-type"] == "Shared" or _OPTIONS["lib-type"] == "SharedLib" then
        defines 
        {
            "AT_BUILD_DLL"
        }
    end
    if _OPTIONS["api-type"] == "C" or _OPTIONS["api-type"] == "C-API" or _OPTIONS["api-type"] == "COMBINED" then
        defines
        {
            "AT_C_API"
        }
    end

    if _OPTIONS["api-type"] == "CPP" or _OPTIONS["api-type"] == "CPP-API" or _OPTIONS["api-type"] == "COMBINED" then
        defines
        {
            "AT_CPP_API"
        }
    end

    if _OPTIONS["api-type"] == "NONE" or _OPTIONS["api-type"] == "none" then
        defines
        {
            "AT_NO_API"
        }
    end
    
    filter "system:windows"
        cppdialect "c++20"
        systemversion "latest"
        links
        {
        }
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"

    filter "system:linux"
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"
    if _OPTIONS["enable-WSL"] then
        toolchainversion "wsl2"
    end
if not _OPTIONS["no-sandbox"] then
group"SANDBOX"
project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "c++"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/x64/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/x64/%{prj.name}")
    includedirs
    {
        "%{IncludeDir.Athena}"
    }
    links
    {
        "Athena"
    }

    filter "system:windows"
        cppdialect "c++20"
        systemversion "latest"
        links
        {
        }
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"

    filter "system:linux"
        filter "configurations:debug"
            symbols "On"
        filter "configurations:release"
            symbols "On"
            optimize "On"
        filter "configurations:distribution"
            symbols "Off"
            optimize "On"
    if _OPTIONS["enable-WSL"] then
        toolchainversion "wsl2"
    end
end