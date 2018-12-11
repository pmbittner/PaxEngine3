set(PAX_COMPILER_IS_CLANG FALSE)
set(PAX_COMPILER_IS_GCC FALSE)
set(PAX_COMPILER_IS_INTEL FALSE)
set(PAX_COMPILER_IS_MSVC FALSE)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    set(PAX_COMPILER_IS_CLANG TRUE)
    message("Compiler set to CLANG")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(PAX_COMPILER_IS_GCC TRUE)
    message("Compiler set to GCC")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
    set(PAX_COMPILER_IS_INTEL TRUE)
    message("Compiler set to INTEL")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
    set(PAX_COMPILER_IS_MSVC TRUE)
    message("Compiler set to MSVC")
endif()