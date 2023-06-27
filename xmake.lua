add_rules("mode.debug", "mode.release")
add_rules("c++")

add_includedirs("./include")
add_linkdirs("./lib")

target("main")
    set_kind("binary")
    add_files("./src/*cpp")
