set(
    SOURCES
    main.cpp
    application.cpp
    endpoints.cpp
)


add_executable(proxy ${SOURCES}) 

target_link_libraries(proxy
    ${yaml-cpp_LIBRARIES}
    Boost::program_options
)

add_dependencies(proxy copy_configs)
