solution "tlgr"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TLGR_BUILD" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSpeed",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "tlgr"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

project "tlgr-dynamic"
kind "SharedLib"
files { "src/**.c", "src/**.cpp" }
targetname "tlgr"

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "tlgr" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
