cmake_minimum_required(VERSION 3.22)

project(AutoDecorator)

if(NOT DEFINED GEODE_MOD_ID)
    set(GEODE_MOD_ID "daniil.autodecorator")
endif()

find_package(geode PROFILE REQUIRED)

add_geode_mod(
    AutoDecorator
    VERSION v1.0.0
    DEVELOPER "Daniil"
)

target_sources(AutoDecorator PRIVATE src/main.cpp)
