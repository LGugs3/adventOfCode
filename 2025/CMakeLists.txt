cmake_minimum_required(VERSION 3.29)

project(AOC2025 CXX)
set(CMAKE_CXX_STANDARD 20)

set(TXT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Inputs")
set(TXT_OUT "${CMAKE_CURRENT_BINARY_DIR}/Inputs/")

file(GLOB TXT_FILES "${TXT_SRC}/*.txt")

#configure_file(${TXT_FILES} ${TXT_OUT} COPYONLY)
file(COPY ${TXT_FILES} DESTINATION ${TXT_OUT})


add_executable(Day1 main.cpp Day1.cpp "Day2.cpp")