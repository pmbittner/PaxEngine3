cmake_minimum_required(VERSION 3.6)

cmake_policy(SET CMP0091 NEW) # for specifying MSVC RuntimeLibrary
project(PaxEngine3)

### DEFINITIONS #########################################
set(PAX_BUILD_TYPE_RELEASE TRUE)
if (${CMAKE_BUILD_TYPE} MATCHES Release)
    add_definitions(-DPAX_BUILD_TYPE_RELEASE)
    message("BUILD TYPE is Release")
elseif(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(PAX_BUILD_TYPE_RELEASE FALSE)
    add_definitions(-DPAX_BUILD_TYPE_DEBUG)
    message("BUILD TYPE is Debug")
endif(${CMAKE_BUILD_TYPE} MATCHES Release)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(PAX_LIB_DIR_RELATIVE ../pax3libs)
set(PAX_LIB_DIR ${CMAKE_SOURCE_DIR}/${PAX_LIB_DIR_RELATIVE})

### DETECT COMPILER #####################################
include(cmake/PaxCompilerDetection.cmake)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    if (PAX_BUILD_TYPE_RELEASE)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif()
    message("Set MSVC RuntimeLibrary to ${CMAKE_MSVC_RUNTIME_LIBRARY}")

    include_directories(${PAX_LIB_DIR}/win/include)
else()

endif()

### DETECT ARCHITECTURE #################################
include(cmake/PaxArchitectureDetection.cmake)

### FLAGS ###############################################
include(cmake/PaxFlagsDefinition.cmake)
set(CMAKE_CXX_STANDARD ${PAX_CXX_STANDARD})
message("CMAKE_CXX_STANDARD is ${CMAKE_CXX_STANDARD}")


#message("CMAKE_CXX_FLAGS        : ${CMAKE_CXX_FLAGS}")
#message("CMAKE_CXX_FLAGS_DEBUG  : ${CMAKE_CXX_FLAGS_DEBUG}")
#message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")


### SOURCE FILES ########################################

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