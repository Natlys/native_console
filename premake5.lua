workspace "native_console"
	architecture "x64"
	configurations
	{
		"debug",
		"release",
		"dist"
	}
--compile and build results
dir_out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
--cplusplus code
dir_cpp = {}
dir_cpp["ncw"] = "nc_world/src_cpp/"
dir_cpp["nce"] = "nc_engine/src_cpp/"
dir_cpp["lua_lib"] = "nc_engine/ext/lua_lib/src/"
--external libraries
dir_lib = {}
dir_lib["ncw"] = "nc_world/ext/"
dir_lib["nce"] = "nc_engine/ext/"
dir_lib["lua_lib"] = "nc_engine/ext/lua_lib/"

--editor_project--
project "nc_world"
	location "nc_world"
	kind "consoleapp"	--.exe file
	language "c++"
	cppdialect "c++17"
	--built binary files
	targetdir ("bin/"..dir_out.."/%{prj.name}")
	--compilation files
	objdir ("bin/int/"..dir_out.."/%{prj.name}")
	--we need to use this in the project
	files
	{
		dir_cpp["ncw"].."**.cpp",
		dir_cpp["ncw"].."**.h**",
		"%{prj.name}/".."**.lua"
	}
	--include directories for cplusplus headers
	includedirs
	{
		dir_cpp["ncw"],
		dir_cpp["nce"],
	}
	--directories for external libs
	libdirs
	{
		dir_lib["ncw"],
		dir_lib["nce"],
	}
	--projects that needs to be built with the current one
	links
	{
		"nc_engine"
	}
	--precompiled_header
	pchheader "ncw_pch.hpp"
	--precompiled_source
	pchsource "%{dir_cpp.ncw}ncw_pch.cpp"

	--filter settings
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"NC_PLATFORM_WINDOWS"
		}
	filter "configurations:debug"
		symbols "on"
		buildoptions "/mdd"
		defines "NC_DEBUG"
	filter "configurations:release"
		optimize "on"
		buildoptions "/md"
		defines "NC_RELEASE"
--editor_project--

--external projects--
include "nc_engine/ext/lua_lib"
include "nc_engine/ext/lua_jit"
--external projects--

--engine_project--
project "nc_engine"
	location "nc_engine"
	kind "staticlib"	--.lib file
	language "c++"
	cppdialect "c++17"
	--built binary files
	targetdir ("bin/"..dir_out.."/%{prj.name}")
	--compilation files
	objdir ("bin/int/"..dir_out.."/%{prj.name}")
	--we need to use this in the project
	files
	{
		dir_cpp["nce"].."**.cpp",
		dir_cpp["nce"].."**.h**",
		"%{prj.name}/".."**.lua"
	}
	--include directories for cplusplus headers
	includedirs
	{
		dir_cpp["nce"],
		dir_cpp["lua_lib"]
	}
	--directories for external libs
	libdirs
	{
		dir_lib["nce"],
		dir_lib["lua_lib"]
	}
	--projects that needs to be built with the current one
	links
	{
		"lua_lib"
	}
	--precompiled_header
	pchheader "nc_pch.hpp"
	--precompiled_source
	pchsource "%{dir_cpp.nce}nc_pch.cpp"

	--filter settings
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"NC_PLATFORM_WINDOWS"
		}
	filter "configurations:debug"
		symbols "on"
		buildoptions "/mdd"
		defines "NC_DEBUG"
	filter "configurations:release"
		optimize "on"
		buildoptions "/md"
		defines "NC_RELEASE"
--engine_project--