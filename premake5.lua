workspace "Craft"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {} 

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

	includedirs {
		"%{prj.name}/src",
	}

	links { 
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"		

		pchheader "crpch.h"
		pchsource "Craft/src/crpch.cpp"
		
		defines {
			"CRAFT_PLATFORM_WINDOWS",
			"CRAFT_BUILD_DLL"
		}

		--aren't work..
		buildoptions { 
			"/FI " .. "crpch.h"
		}

		filter "configurations:Debug"
			defines "CR_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "CR_RELEASE"
			optimize "on"
		
		filter "configurations:Dist"
			defines "CR_DIST"
			symbols "on"
		
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
	}

	links {
		"Craft"
		--"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		defines { "CRAFT_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "CR_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "CR_RELEASE"
		optimize "on"
		
	filter "configurations:Dist"
		defines "CR_DIST"
		symbols "on"