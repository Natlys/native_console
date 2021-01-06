--==<lua jit compiler>==--
project "lua_jit"
	kind "staticlib"
	language "c"
	staticruntime "on"
	systemversion "latest"

	targetdir ("bin/"..dir_out.. "/%{prj.name}")
	objdir ("bin-int/"..dir_out.. "/%{prj.name}")

	files
	{
		"src/**.h**",
		"src/**.c",
		"src/**.inl"
	}
	includedirs
	{
		"src/",
		"src/jit",
		"src/host"
	}

	filter "configurations:debug"
		runtime "debug"
		symbols "on"

	filter "configurations:release"
		runtime "release"
		optimize "on"