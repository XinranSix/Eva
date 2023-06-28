add_rules("mode.debug", "mode.release")

add_linkdirs("./lib")
 add_includedirs("./include")
-- set_languages("cxx17")

-- add_cxxflags("msvc::utf-8")
-- add_cflags("msvc::utf-8")

target("main")
    set_kind("binary")
    add_files("./src/*.cpp", "./src/glad.c")
    add_links("glfw3dll")
