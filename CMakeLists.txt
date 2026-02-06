cmake_minimum_required(VERSION 3.13)
project(HighGraphicsFix)
find_package(Geode REQUIRED)
add_geode_mod(HighGraphicsFix "v1.0.0" SOURCES main.cpp)
