cmake_minimum_required(VERSION 3.21)
project(ps.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (DEFINED SOURCE_PATH)
	set(SOURCES ${CMAKE_SOURCE_DIR}/${SOURCE_PATH})
else()
	message( FATAL_ERROR "You must specify SOURCE_PATH. For example, cmake -DSOURCE_PATH=./main.cpp .." )
endif()

include_directories(${CMAKE_SOURCE_DIR}/incl)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=1 -O0 -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE}")

add_executable(${PROJECT_NAME}.out ${SOURCES})