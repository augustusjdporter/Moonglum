cmake_minimum_required(VERSION 3.6)
project(Moonglum)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    baseClasses/barnesHut/BarnesHutTree.cpp
    baseClasses/barnesHut/BarnesHutTree.h
    baseClasses/barnesHut/BarnesHutTree3D.cpp
    baseClasses/barnesHut/BarnesHutTree3D.h
    baseClasses/barnesHut/Quadrant.cpp
    baseClasses/barnesHut/Quadrant.h
    baseClasses/barnesHut/Quadrant3D.cpp
    baseClasses/barnesHut/Quadrant3D.h
    baseClasses/body.cpp
    baseClasses/body.h
    baseClasses/Constants.h
    baseClasses/system.cpp
    baseClasses/system.h
    baseClasses/Universe.cpp
    baseClasses/Universe.h
    galaxy-simulation/BlackHole.cpp
    galaxy-simulation/BlackHole.h
    galaxy-simulation/DarkMatterHalo.cpp
    galaxy-simulation/DarkMatterHalo.h
    galaxy-simulation/Galaxy.cpp
    galaxy-simulation/Galaxy.h
    galaxy-simulation/Gas.cpp
    galaxy-simulation/Gas.h
    galaxy-simulation/Star.cpp
    galaxy-simulation/Star.h
    planetary-simulation/ProtoplanetaryCloud.cpp
    planetary-simulation/ProtoplanetaryCloud.h
    Utilities/rapidxml-1.13/rapidxml.hpp
    Utilities/OpenCLFunctions.h
    Utilities/Utilities.cpp
    Utilities/Utilities.h
    Utilities/XmlReader.cpp
    Utilities/XmlReader.h
    main.cpp)

add_executable(Moonglum ${SOURCE_FILES})