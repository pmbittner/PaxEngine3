cmake_minimum_required(VERSION 3.6)

cmake_policy(SET CMP0091 NEW) # for specifying MSVC RuntimeLibrary
project(PaxEngine3)

### DEFINITIONS #########################################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(PAX_LIB_DIR_RELATIVE ../pax3libs)
set(PAX_LIB_DIR ${CMAKE_SOURCE_DIR}/${PAX_LIB_DIR_RELATIVE})
include(cmake/PaxSetup.cmake)

### CONFIGURE MSVC #####################################

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    if (PAX_BUILD_TYPE_RELEASE)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif()
    message("Set MSVC RuntimeLibrary to ${CMAKE_MSVC_RUNTIME_LIBRARY}")
endif()

### FLAGS ###############################################
set(CMAKE_CXX_STANDARD ${PAX_CXX_STANDARD_MINIMUM})
message("CMAKE_CXX_STANDARD is ${CMAKE_CXX_STANDARD}")

### INCLUDES ########################################

include_directories(include)

### API INCLUDES ########################################

message("=== Including Internal Libraries ===================================")
add_subdirectory(libs)
message("=== Including Internal Libraries DONE ==============================")

# Polypropylene
include_directories(libs/Polypropylene/include)
add_definitions(-DPAX_WITH_JSON)

### SUBDIRECTORIES ######################################
add_subdirectory(src)

### PLUGINS #############################################
add_subdirectory(plugins)