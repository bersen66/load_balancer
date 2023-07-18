set(
    SOURCES
    main.cpp
    application.cpp
    application.hpp
    endpoints.cpp
    endpoints.hpp
    server.cpp
    server.hpp
    selectors.cpp
    selectors.hpp
    session.cpp
    session.hpp
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
