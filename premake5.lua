-- LunaLynx-Dynamic
workspace "LunaLynx-Dynamic"
	architecture "x86"
	startproject "LunaLynx-Dynamic"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

project "LunaLynx-Dynamic"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/build/%{cfg.buidcfg}")
	objdir ("%{wks.location}/.build/%{cfg.buildcfg}")

	pchheader "ccpch.h"
	pchsource "src/ccpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs "src"