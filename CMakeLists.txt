cmake_minimum_required(VERSION 3.22)

project(AutoDecorator)

find_package(Geode REQUIRED)

add_geode_mod(
    ID icedog.autodecorator
    SOURCES main.cpp
)
