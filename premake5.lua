workspace "Craft"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Craft"
	location "Craft"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		pchheader "crpch.h"
		pchsource "Craft/src/crpch.cpp"
		
		defines {
			"CRAFT_PLATFORM_WINDOWS",
			"CRAFT_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		--aren't work..
		buildoptions { 
			"/FI " .. "crpch.h"
		}

		filter "configurations:Debug"
			defines "CR_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "CR_RELEASE"
			optimize "On"
		
		filter "configurations:Dist"
			defines "CR_DIST"
			symbols "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Craft/vendor/spdlog/include",
		"Craft/src"
	}

	links {
		"Craft"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { "CRAFT_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "CR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CR_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CR_DIST"
		symbols "On"