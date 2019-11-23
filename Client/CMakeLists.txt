cmake_minimum_required(VERSION 3.15)
project(Client C)

set(CMAKE_C_STANDARD 99)

add_executable(Client main.c Socket.h Socket.c ICE-Json.c ICE-Json.h)

target_link_libraries(Client json-c)