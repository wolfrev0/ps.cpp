cmake_minimum_required(VERSION 3.21)
project(ps.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(debug_flag OFF) # Set this variable to ON for debug builds

set(SOURCES ${CMAKE_SOURCE_DIR}/src/a.cpp)
set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/incl)
set(RESULT_DIR ${CMAKE_BINARY_DIR}/res)
file(MAKE_DIRECTORY ${RESULT_DIR})

if (debug_flag)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -iquote ${INCLUDE_DIRS} -DDEBUG=1 -O0 -g -fsanitize=address")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -iquote ${INCLUDE_DIRS} -O2")
endif()

# Generate the list of dependencies
function(generate_dependency_list source_file output_list)
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} ${source_file} -MM -I${INCLUDE_DIRS}
        OUTPUT_VARIABLE dependencies
        RESULT_VARIABLE result
        ERROR_QUIET
    )

    if (result EQUAL 0)
        string(REGEX REPLACE "(^| |\t)([^/\\.\n]*\\.cpp)" "${CMAKE_CURRENT_SOURCE_DIR}/\\2" dependencies "${dependencies}")
        string(REGEX REPLACE "[ \\\t]*\\\\[\n \\\t]*" " " dependencies "${dependencies}")
        string(REPLACE "\\\n" "" dependencies "${dependencies}")
        string(REGEX REPLACE "\n" ";" dependencies "${dependencies}")
        set(${output_list} ${dependencies} PARENT_SCOPE)
    else()
        message(FATAL_ERROR "Failed to generate dependency list for ${source_file}")
    endif()
endfunction()

# # Generate the list of source files and their dependencies
# set(all_sources ${SOURCES})
# foreach(source_file ${SOURCES})
#     generate_dependency_list(${source_file} dependencies)
#     list(APPEND all_sources ${dependencies})
# endforeach()

if (NOT "$2" MATCHES ".*\\.h")
    set(generated_source ${RESULT_DIR}/submit.cpp)
    add_custom_command(
        OUTPUT ${generated_source}
        COMMAND ${CMAKE_CXX_COMPILER} ${SOURCES} -I${INCLUDE_DIRS} -E -C -o ${generated_source}
        DEPENDS ${all_sources}
    )

    add_custom_target(generate_submit_source DEPENDS ${generated_source})

    # Set the properties for generated source file
    set_source_files_properties(${generated_source} PROPERTIES GENERATED TRUE)

    # Copy necessary headers
    file(GLOB_RECURSE headers incl/*.h)
    foreach(header ${headers})
        add_custom_command(
            TARGET generate_submit_source
            COMMAND ${CMAKE_COMMAND} -E copy ${header} ${RESULT_DIR}/
            DEPENDS ${header}
        )
    endforeach()

    # Configure the final build target
    # add_executable(${PROJECT_NAME} ${generated_source})
    add_executable(${PROJECT_NAME} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()
