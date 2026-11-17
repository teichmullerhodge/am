
cmake_minimum_required(VERSION 3.16)

project(am LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# GLAD
add_library(glad STATIC
    "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c"
)

target_include_directories(glad PUBLIC
    "${CMAKE_SOURCE_DIR}/external/glad/include"
)

# Common dependencies for all executables
add_library(am_dependencies INTERFACE)

target_link_libraries(am_dependencies INTERFACE
    glad
    glfw
    OpenGL::GL
)

# Automatically create an executable from a directory
function(am_add_program TARGET_NAME SOURCE_DIR)

    file(GLOB_RECURSE SOURCES
        CONFIGURE_DEPENDS
        "${SOURCE_DIR}/*.c"
        "${SOURCE_DIR}/*.cpp"
    )

    if(NOT SOURCES)
        return()
    endif()

    add_executable("${TARGET_NAME}" ${SOURCES})

    target_include_directories("${TARGET_NAME}" PRIVATE
        "${SOURCE_DIR}"
    )

    target_link_libraries("${TARGET_NAME}" PRIVATE
        am_dependencies
    )

endfunction()

# LESSONS
file(GLOB LESSON_DIRS
    CONFIGURE_DEPENDS
    LIST_DIRECTORIES true
    "${CMAKE_SOURCE_DIR}/lessons/*"
)

foreach(LESSON_DIR IN LISTS LESSON_DIRS)

    if(NOT IS_DIRECTORY "${LESSON_DIR}")
        continue()
    endif()

    get_filename_component(LESSON_NAME "${LESSON_DIR}" NAME)

    am_add_program(
        "${LESSON_NAME}"
        "${LESSON_DIR}"
    )

endforeach()

# ENGINE
if(EXISTS "${CMAKE_SOURCE_DIR}/engine")
    am_add_program(
        "am_engine"
        "${CMAKE_SOURCE_DIR}/engine"
    )
endif()

