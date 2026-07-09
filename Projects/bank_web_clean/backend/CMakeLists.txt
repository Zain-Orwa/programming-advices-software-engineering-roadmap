cmake_minimum_required(VERSION 3.16)

project(bank_backend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bank_api
    src/main.cpp
    src/Client.cpp
    src/Json.cpp
    src/Storage.cpp
    src/BankService.cpp
    src/HttpServer.cpp
    src/Routes.cpp
)

target_include_directories(bank_api PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
