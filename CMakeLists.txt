    cmake_minimum_required(VERSION 3.22)
    enable_language(CUDA)
    find_program(CCACHE_PROGRAM ccache)

    #project(Fractal LANGUAGES CUDA)

    if(CCACHE_PROGRAM)
        MESSAGE("CCACHE support enabled")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
    endif()

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CUDA_STANDARD 23)
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
    #set(CMAKE_CXX_COMPILER /usr/bin/clang++)
    set(CUDA_HOST_COMPILER /usr/bin/clang++)
    set(CMAKE_CUDA_COMPILER /usr/bin/clang++)

    set(CMAKE_BUILD_TYPE "Release")

    set(FETCHCONTENT_QUIET FALSE)
    include(FetchContent)

    set(BUILD_SHARED_LIBS OFF)
    set(BUILD_STATIC_LIBS ON)
    set(BUILD_TESTING OFF)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY "https://github.com/fmtlib/fmt"
        GIT_TAG 9.1.0
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
    )

    set(GLFW_SHARED_LIBS OFF)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_INSTALL OFF)
    #set(GLFW_BUILD_X11 OFF)
    #set(GLFW_USE_WAYLAND ON)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw"
        GIT_TAG 3.3.8
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
    )

    set(GLM_TEST_ENABLE OFF)
    set(GLM_TEST_ENABLE_CXX_20 ON)
    set(GLM_TEST_ENABLE_FAST_MATH ON)
    set(GLM_TEST_ENABLE_SIMD_AVX2 ON)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY "https://github.com/g-truc/glm"
        GIT_TAG 0.9.9.8
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(glfw glm fmt)

    set(BUILD_TESTING ON)

    #add_compile_options(-Wall -Wextra -pedantic -Werror)

    add_executable(fractal src/EntryPoint.cpp)

    target_include_directories(fractal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")

        target_include_directories(fractal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/release/include/)
        target_sources(fractal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/release/src/glad.c)

    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_include_directories(fractal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/debug/include/)
        target_sources(fractal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/debug/src/glad.c)

    endif()

    target_link_libraries(fractal glfw glm fmt::fmt)

    #add_executable(cuda-fractal src/CudaEntryPoint.cu)
    #target_link_libraries(${name} )

    # https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.6&api=gles1%3D1.0&api=gles2%3D3.2&api=glsc2%3D2.0&profile=core&loader=on
    # https://glad.dav1d.de/#language=c-debug&specification=gl&api=gl%3D4.6&api=gles1%3D1.0&api=gles2%3D3.2&api=glsc2%3D2.0&profile=core&loader=on