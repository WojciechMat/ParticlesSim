# tests/CMakeLists.txt
set(TEST_SOURCES
    tests.cpp
)

add_executable(Tests ${TEST_SOURCES})

target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Link Boost and the main project library
find_package(Boost 1.65.1 COMPONENTS unit_test_framework REQUIRED)
target_link_libraries(Tests PRIVATE Boost::unit_test_framework ParticleLib)