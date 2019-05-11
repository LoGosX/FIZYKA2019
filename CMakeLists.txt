cmake_minimum_required(VERSION 3.10.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(FIZYKA2019)


if(MSVC)
    #static library
    add_compile_options(/W3 /O2 /MT)
endif()

add_subdirectory(libraries/SFML)
	
include_directories("include" ${SFML_INCLUDE_DIR})
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")


add_executable(FIZYKA2019 ${SOURCES} ${HEADERS})
target_compile_definitions(FIZYKA2019 PRIVATE SFML_STATIC)

target_link_libraries(FIZYKA2019 sfml-graphics sfml-window sfml-system)
