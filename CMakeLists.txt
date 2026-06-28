cmake_minimum_required(VERSION 3.25)

project(GeodeAutoDecorator)

find_package(Geode REQUIRED)

add_geode_mod(
    geode-auto-decorator
    VERSION v1.0.0
    
    SOURCES
        src/main.cpp
)
