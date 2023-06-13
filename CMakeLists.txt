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

set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/incl)
include_directories(${INCLUDE_DIRS})

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG=1 -O0 -g fsanitize=address")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# set(RESULT_DIR ${CMAKE_BINARY_DIR}/res)
# file(MAKE_DIRECTORY ${RESULT_DIR})

# # Generate the list of source files and their dependencies
# set(all_sources ${SOURCES})
# foreach(source_file ${SOURCES})
#     generate_dependency_list(${source_file} dependencies)
#     list(APPEND all_sources ${dependencies})
# endforeach()

# set(generated_source ${RESULT_DIR}/submit.cpp)
# add_custom_command(
# 	OUTPUT ${generated_source}
# 	COMMAND ${CMAKE_CXX_COMPILER} ${SOURCES} -I${INCLUDE_DIRS} -E -C -o ${generated_source}
# 	DEPENDS ${all_sources}
# )

# add_custom_target(generate_submit_source DEPENDS ${generated_source})

# # Set the properties for generated source file
# set_source_files_properties(${generated_source} PROPERTIES GENERATED TRUE)

# # Copy necessary headers
# file(GLOB_RECURSE headers incl/*.h)
# foreach(header ${headers})
# 	add_custom_command(
# 		TARGET generate_submit_source
# 		COMMAND ${CMAKE_COMMAND} -E copy ${header} ${RESULT_DIR}/
# 		DEPENDS ${header}
# 	)
# endforeach()

get_filename_component(EXEC_NAME ${SOURCE_PATH} NAME)
set(EXEC_NAME ${EXEC_NAME}.${CMAKE_BUILD_TYPE})

# Configure the final build target
# add_executable(${PROJECT_NAME} ${generated_source})
add_executable(${EXEC_NAME} ${SOURCES})