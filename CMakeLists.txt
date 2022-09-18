cmake_minimum_required(VERSION 3.16)

project(blibc)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CMAKE_C_FLAGS "-std=c89 -Wall -Wextra -Werror -pedantic -O3")
