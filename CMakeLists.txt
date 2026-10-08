cmake_minimum_required(VERSION 3.15)
project(activemq-cpp-broker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(activemq-cpp REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<INSTALL_INTERFACE:>/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    activemq-cpp::activemq-cpp
)