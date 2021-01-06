--==<lua library for c++>==--
project "lua_lib"
	kind "staticlib"
	language "c"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/"..dir_out.. "/%{prj.name}")
	objdir ("bin-int/"..dir_out.. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",

		"src/lapi.c",
		"src/lcode.c",
		"src/lctype.c",
		"src/ldebug.c",
		"src/ldo.c",
		"src/ldump.c",
		"src/lfunc.c",
		"src/lgc.c",
		"src/llex.c",
		"src/lmem.c",
		"src/lobject.c",
		"src/lopcodes.c",
		"src/lparser.c",
		"src/lstate.c",
		"src/lstring.c",
		"src/ltable.c",
		"src/ltm.c",
		"src/lundump.c",
		"src/lvm.c",
		"src/lzio.c",
		"src/lauxlib.c",
		"src/lbaselib.c",
		"src/lcorolib.c",
		"src/ldblib.c",
		"src/liolib.c",
		"src/lmathlib.c",
		"src/loadlib.c",
		"src/loslib.c",
		"src/lstrlib.c",
		"src/ltablib.c",
		"src/lutf8lib.c",
		"src/linit.c"
	}
	includedirs
	{
		"src/"
	}

	filter "configurations:debug"
		runtime "debug"
		symbols "on"

	filter "configurations:release"
		runtime "release"
		optimize "on"
--[[
--==<lua interpreter for script development>==--
project "lua_interp"
	kind "consoleapp"
	language "C"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/"..dir_out.. "/%{prj.name}")
	objdir ("bin-int/"..dir_out.. "/%{prj.name}")

	files
	{
		"src/lua.c"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

--==<lua compiler for script development>==--
project "lua_compl"
	kind "consoleapp"
	language "C"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/"..dir_out.. "/%{prj.name}")
	objdir ("bin-int/"..dir_out.. "/%{prj.name}")

	files
	{
		"src/luac.c"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
]]