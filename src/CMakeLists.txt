add_executable(main EntryPoint.cpp Application.cpp SandBoxApp.cpp Log.cpp)
target_link_libraries(main spdlog)
