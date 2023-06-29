add_rules("mode.debug", "mode.release")

add_linkdirs("./lib")
add_includedirs("./include")
set_languages("cxx17")

target("imgui")
    set_kind("static")
    add_files("./imgui/*.cpp")

target("Renderer")
    set_kind("static")
    add_files("./Renderer/*.cpp")


target("main")
    set_kind("binary")
    add_files("./src/*.cpp", "./src/*.c")
    add_deps("imgui", "Renderer")
    add_links("glfw3dll")
