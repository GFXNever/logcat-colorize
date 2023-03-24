cmake_minimum_required(VERSION 3.20)
include(cmake-scripts/read_configuration.cmake)
read_properties()

project(${NAME})
set(CMAKE_CXX_STANDARD 20)

add_definitions(-DVERSION="${VERSION}")

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/**.cpp)

add_subdirectory(contrib/argparse)
add_subdirectory(contrib/termcolor)

set(JSON_MultipleHeaders OFF CACHE INTERNAL "" FORCE)
add_subdirectory(contrib/json)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json termcolor::termcolor argparse::argparse)

