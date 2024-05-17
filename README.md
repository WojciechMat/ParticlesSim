# Particle Simulation
This project simulates particles moving and interacting within a bounded space. The simulation handles particle collisions and wall bounces using SFML for visualization and Boost for unit testing.
![image](https://github.com/WojciechMat/ParticlesSim/assets/74838859/be9d4710-858f-4030-8667-e3425a2da710)

Project Structure
```plain
├── ParticlesSim
    ├── CMakeLists.txt
    ├── particle.cpp
    ├── particle.h
    ├── event.cpp
    ├── event.h
    ├── simulation.cpp
    ├── simulation.h
    ├── main.cpp
    ├── settings.h
    └── tests
        ├── CMakeLists.txt
        └── tests.cpp
├── build
    └── .keep
└── README.md

```
### Building the Project
#### Prerequisites
Ensure you have the following installed:

CMake (version 3.10 or later)

SFML (version 2.5 or later)

Boost (version 1.65.1 or later)

### Building the Main Simulation

```sh
cd build
cmake ../ParticlesSim

make
```
### Running the Simulation
After building the project, you can run the simulation using:

```sh
./ParticleSimulation 100 0.2 0.5
```
### Running the Tests

```sh
./tests/Tests
```
### Project Components
#### particle.h / particle.cpp
Defines the Particle class, representing a particle in the simulation. This class includes methods for movement, collision detection, and response.

#### event.h / event.cpp
Defines the Event class, representing collision events between particles or with walls. This class includes methods for event handling and validation.

#### simulation.h / simulation.cpp
Defines the Simulation class, which manages the overall simulation, including initializing particles, predicting collisions, and running the simulation loop.

#### main.cpp
Contains the main function that sets up and starts the simulation.

#### settings.h
Contains configuration settings for the simulation, such as window dimensions.

#### tests/CMakeLists.txt
CMake configuration for building and running the unit tests using Boost.

#### tests/test_particle.cpp
Unit tests for the Particle and Event classes using the Boost Test framework.
