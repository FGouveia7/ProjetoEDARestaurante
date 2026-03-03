cmake_minimum_required(VERSION 3.30)
project(Projeto)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projeto 1main.cpp
        5mesa.cpp
        5mesa.h
        3cliente.cpp
        3cliente.h
        2estruturas.h
        4fila.cpp
        4fila.h
        6balcao.cpp
        6balcao.h
        7Menus.cpp
        7Menus.h
        8carregarEguardar.cpp
        8carregarEguardar.h
)
