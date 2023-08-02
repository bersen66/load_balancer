add_subdirectory(selectors)
add_subdirectory(commands)

set(
    SOURCES
    main.cpp
    application.cpp
    application.hpp
    parse_endpoints.cpp
    endpoints.hpp
    endpoints.cpp
    server.cpp
    server.hpp
    session.cpp
    session.hpp
)


add_executable(
    proxy
    ${SOURCES}
    ${SELECTORS_SOURCES}
)

# EXTERNAL LIBS
target_link_libraries(
    proxy
    ${yaml-cpp_LIBRARIES}
    ${ftxui_LIBRARIES}
    Boost::program_options
)

# INTERNAL LIBS
target_link_libraries(
    proxy
    libselectors
    libcommands
)

# OTHER DEPENDENCIES
add_dependencies(proxy copy_configs)
