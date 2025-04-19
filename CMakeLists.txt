cmake_minimum_required(VERSION 3.27)
project(MichelinMunch)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(MichelinMunch
        include/HashMapChaining.h
        include/HashMapOpen.h
        src/main.cpp
        include/Restaurant.h
        include/DatasetLoader.h
        src/DatasetLoader.cpp
)
