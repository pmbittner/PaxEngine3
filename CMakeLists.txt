cmake_minimum_required(VERSION 3.6)

cmake_policy(SET CMP0091 NEW) # for specifying MSVC RuntimeLibrary
project(PaxEngine3)

### DEFINITIONS #########################################

# Detect if standalone or included as subdirectory
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(PAX3STANDALONE TRUE)
    message("Building PaxEngine3 as standalone.")
else()
    set(PAX3STANDALONE FALSE)
    message("Building PaxEngine3 as library.")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
if (${PAX3STANDALONE})
    set(PAX_LIB_DIR_RELATIVE ../pax3libs)
    include(cmake/PaxSetup.cmake)
endif()

### CONFIGURE MSVC #####################################

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    if (PAX_BUILD_TYPE_RELEASE)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif()
    message("Set MSVC RuntimeLibrary to ${CMAKE_MSVC_RUNTIME_LIBRARY}")
endif()

#set(CompilerFlags
#        CMAKE_CXX_FLAGS
#        CMAKE_CXX_FLAGS_DEBUG
#        CMAKE_CXX_FLAGS_RELEASE
#        CMAKE_C_FLAGS
#        CMAKE_C_FLAGS_DEBUG
#        CMAKE_C_FLAGS_RELEASE
#        )
#foreach(CompilerFlag ${CompilerFlags})
#    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
#endforeach()

### FLAGS ###############################################
if (${PAX3ENGINE_STANDALONE})
    set(CMAKE_CXX_STANDARD ${PAX_CXX_STANDARD_MINIMUM})
    message("CMAKE_CXX_STANDARD is ${CMAKE_CXX_STANDARD}")
endif()

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