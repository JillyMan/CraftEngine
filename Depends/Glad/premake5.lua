project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
		"include/wglext/wglext.h",
		"include/win32gl/win32gl.h",
        "src/win32gl.c",
        "src/glad.c",
	}

	includedirs {
        "include"
    }
    
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
		optimize "on"
		

