set(
    SOURCES
    main.cpp
    application.cpp
    endpoints.cpp
    server.cpp
    selectors.cpp
)


add_executable(proxy ${SOURCES}) 

# EXTERNAL LIBS
target_link_libraries(proxy
    ${yaml-cpp_LIBRARIES}
    Boost::program_options
)

# INTERNAL LIBS
#target_link_libraries(proxy
#    ANY_INTERNAL_LIB
#)

# OTHER DEPENDENCIES
add_dependencies(proxy copy_configs)
