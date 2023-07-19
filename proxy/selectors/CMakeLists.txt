set(
    SELECTORS_SOURCES
    selectors.hpp
    selection_strategy.hpp
    round_robin_strategy.hpp
    round_robin_strategy.cpp
)

add_library(libselectors ${SELECTORS_SOURCES})