add_subdirectory(selectors)

set(
    SOURCES
    main.cpp
    application.cpp
    application.hpp
    endpoints.cpp
    endpoints.hpp
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
target_link_libraries(proxy
    ${yaml-cpp_LIBRARIES}
    Boost::program_options
)

# INTERNAL LIBS
target_link_libraries(proxy
    libselectors
)

# OTHER DEPENDENCIES
add_dependencies(proxy copy_configs)
