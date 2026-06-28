cmake_minimum_required(VERSION 3.22)

project(AutoDecorator)

find_package(geode PROFILE REQUIRED)

add_geode_mod(
    AutoDecorator
    VERSION v1.0.0
    DEVELOPER "Daniil"
)

target_sources(AutoDecorator PRIVATE src/main.cpp)
