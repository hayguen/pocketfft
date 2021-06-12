cmake_minimum_required(VERSION 2.8)
project(PocketFFT)

option(POCKET_USE_FAST_MATH  "Build with fast math - non IEEE compliant" ON)
option(DISABLE_LINK_WITH_M  "Disables linking with m library to build with clangCL from MSVC" OFF)

# C90 requires the gcc extensions for function attributes like always_inline
# C99 provides the function attributes: no gcc extensions required
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

# detect compiler
set(COMPILER_IS_GCC false)
set(COMPILER_IS_CLANG false)
set(COMPILER_IS_MSVC false)
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  # using GCC
  set(COMPILER_IS_GCC true)
  message(STATUS "detected compiler: GCC")
  set(ARCH "native" CACHE STRING "gcc target architecture (-march): native/SSE:core2/AVX:sandybridge/ARM-NEON:armv7-a")
elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
  set(COMPILER_IS_CLANG true)
  message(STATUS "detected compiler: CLANG")
  set(ARCH "native" CACHE STRING "gcc target architecture (-march): native/SSE:core2/AVX:sandybridge")
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")  # others: "Clang", "Intel"
  set(COMPILER_IS_MSVC true)
  message(STATUS "detected compiler: MSVC")
  set(ARCH "AVX" CACHE STRING "msvc target architecture (/arch): SSE2/AVX")
else()
  message(WARNING "detected compiler: unknown!")
endif()



########################################################################
# select the release build type by default to get optimization flags
########################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)


# link with math library?
if(DISABLE_LINK_WITH_M)
  set(MATHLIB "")
else()
  message(STATUS "INFO: detected NO MSVC: ${CMAKE_C_COMPILER_ID}: will link math lib m")
  if (COMPILER_IS_MSVC)
    message(WARNING "INFO: detected MSVC: will not link math lib m")
    set(MATHLIB "")
  else()
    set(MATHLIB "m")
  endif()
endif()


# determine compiler specific options for target architecture
# and fast math
set(OPT_ARCH "")
set(OPT_FAST_MATH "")

if (COMPILER_IS_MSVC)
  if (ARCH STREQUAL "")
    message(WARNING "ARCH is not set!")
  else()
    message(STATUS "ARCH is ${ARCH}")
    set(OPT_ARCH "/arch:${ARCH}")
  endif()
  if (POCKET_USE_FAST_MATH)
    set(OPT_FAST_MATH "/fp:fast")
  endif()
endif()

if (COMPILER_IS_GCC OR COMPILER_IS_CLANG)
  if (ARCH STREQUAL "")
    message(WARNING "ARCH is not set!")
  else()
    message(STATUS "ARCH is ${ARCH}")
    set(OPT_ARCH "-march=${ARCH}")
  endif()
  if (POCKET_USE_FAST_MATH)
    set(OPT_FAST_MATH "-ffast-math")
  endif()
endif()

message(STATUS "compiler option for target architecture: ${OPT_ARCH}")
message(STATUS "compiler option for fast math: ${OPT_FAST_MATH}")

######################################################

add_library(PocketFFT STATIC
  pocketfft_double.c pocketfft_single.c
)

set_property(TARGET PocketFFT APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_options(PocketFFT PRIVATE $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -pedantic>)
target_compile_options(PocketFFT PRIVATE "${OPT_ARCH}" "${OPT_FAST_MATH}")
target_link_libraries(PocketFFT ${MATHLIB})
