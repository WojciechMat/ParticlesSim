cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    particle.cpp
    event.cpp
    simulation.cpp
)

# Create a library from the source files
add_library(ParticleLib ${SOURCES})

# Include directories
target_include_directories(ParticleLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(ParticleLib PUBLIC sfml-system sfml-window sfml-graphics)

# Add executable for the main simulation
add_executable(ParticleSimulation main.cpp)
target_link_libraries(ParticleSimulation PRIVATE ParticleLib)

# Add subdirectory for tests
add_subdirectory(tests)