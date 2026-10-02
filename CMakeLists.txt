cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

option(RT_NATIVE      "Optimise for the build machine's CPU (-march=native / AVX2)" ON)
option(RT_SANITIZERS  "Build with AddressSanitizer + UBSan (GCC/Clang only)"      OFF)
option(RT_BUILD_TESTS "Build unit tests"                                          ON)

# ---------------------------------------------------------------------------
# Shared warning / optimisation flags, applied per-target via rt_set_options()
# ---------------------------------------------------------------------------
function(rt_set_options target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8)
    if(RT_NATIVE)
      target_compile_options(${target} PRIVATE /arch:AVX2)
    endif()
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
    if(RT_NATIVE)
      target_compile_options(${target} PRIVATE -march=native)
    endif()
    if(RT_SANITIZERS)
      target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
      target_link_options(${target}    PRIVATE -fsanitize=address,undefined)
    endif()
  endif()
endfunction()

# ---------------------------------------------------------------------------
# rt_core: everything except main(). The executable, tests and benchmarks all
# link against this, so add new .cpp files here as you write them.
# ---------------------------------------------------------------------------
add_library(rt_core
  src/render/image.cpp
  src/render/camera.cpp
)
target_include_directories(rt_core PUBLIC src)
target_include_directories(rt_core SYSTEM PRIVATE third_party)  # silence warnings in vendored code
rt_set_options(rt_core)

find_package(Threads REQUIRED)
target_link_libraries(rt_core PUBLIC Threads::Threads)  # needed from Week 3 (thread pool)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE rt_core)
rt_set_options(raytracer)

if(RT_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
