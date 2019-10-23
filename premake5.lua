workspace "Craft"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "Depends/Glad/include"
IncludeDir["ImGui"] = "Depends/ImGui"

group "Dependencies"
	include "Depends/Glad"
	include "Depends/ImGui"

group ""

project "Craft"
	location "Craft"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	characterset "MBCS"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links {
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"		

		pchheader "crpch.h"
		pchsource "Craft/src/crpch.cpp"
		
		defines {
			"CRAFT_BUILD_DLL",
			"CRAFT_PLATFORM_WINDOWS"
		}
		
		buildoptions { 
			"/FI " .. "crpch.h"
		}

		filter "configurations:Debug"
			defines "CR_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "CR_RELEASE"
			optimize "on"
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	characterset "MBCS"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Craft/src",
		"Depends/Glad/include"
	}

	defines {
		"CRAFT_PLATFORM_WINDOWS",
	}

	links {
		"Craft"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CR_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "CR_RELEASE"
		optimize "on"
