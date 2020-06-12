cmake_minimum_required(VERSION 2.8)
set(CMAKE_C_STANDARD 99)
project(PocketFFT)

########################################################################
# select the release build type by default to get optimization flags
########################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)


add_library(PocketFFT STATIC
  pocketfft.c
)

set_property(TARGET PocketFFT APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(PocketFFT m)
