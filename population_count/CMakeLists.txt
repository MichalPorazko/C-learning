cmake_minimum_required(VERSION 3.28)

# https://cmake.org/cmake/help/latest/command/project.html
project(my_project
        VERSION 1
        LANGUAGES C
)

#https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD_REQUIRED.html
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


#https://cmake.org/cmake/help/latest/variable/CMAKE_C_EXTENSIONS.html
#https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#manual:cmake-compile-features(7)
set(CMAKE_C_EXTENSIONS OFF)


#https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_NAME pop_count_lib)


add_library(${TARGET_NAME}/static STATIC 
        "${PROJECT_SOURCE_DIR}/src/*.c"
)

target_include_directories(${TARGET_NAME}/static PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_library(${TARGET_NAME}/shared SHARED
            "/home/michal/Documents/C-learning/printing/printing_binary"
)

target_include_directories(${TARGET_NAME}/static INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)

