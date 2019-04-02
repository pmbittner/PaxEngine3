cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### DEFINITIONS #########################################
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(PAX_LIB_DIR_RELATIVE ../lib)
set(PAX_LIB_DIR ${CMAKE_SOURCE_DIR}/${PAX_LIB_DIR_RELATIVE})

### DETECT COMPILER #####################################
include(cmake/PaxCompilerDetection.cmake)

### DETECT ARCHITECTURE #################################
include(cmake/PaxArchitectureDetection.cmake)

### FLAGS ###############################################
include(cmake/PaxFlagsDefinition.cmake)
set(CMAKE_CXX_STANDARD ${PAX_CXX_STANDARD})
message("CMAKE_CXX_STANDARD is ${CMAKE_CXX_STANDARD}")

if (${CMAKE_BUILD_TYPE} MATCHES Release)
    add_definitions(-DPAX_BUILD_TYPE_RELEASE)
elseif(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DPAX_BUILD_TYPE_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES Release)

#message("CMAKE_CXX_FLAGS        : ${CMAKE_CXX_FLAGS}")
#message("CMAKE_CXX_FLAGS_DEBUG  : ${CMAKE_CXX_FLAGS_DEBUG}")
#message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")


### SOURCE FILES ########################################

include_directories(include)

### API INCLUDES ########################################

include_directories(${PAX_LIB_DIR_RELATIVE}/Easylogging/include)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    include_directories(${PAX_LIB_DIR_RELATIVE}/win/include)

    if (${CMAKE_BUILD_TYPE} MATCHES Release)
        set(EASYLOGGING_LIBRARY ${PAX_LIB_DIR}/Easylogging/bin/msvc-release/easylogging.lib)
    elseif(${CMAKE_BUILD_TYPE} MATCHES Debug)
        set(EASYLOGGING_LIBRARY ${PAX_LIB_DIR}/Easylogging/bin/msvc-debug/easylogging.lib)
    endif(${CMAKE_BUILD_TYPE} MATCHES Release)
else()
    link_directories(${PAX_LIB_DIR}/Easylogging/bin/mingw)
    set(EASYLOGGING_LIBRARY easylogging)
endif()

### SUBDIRECTORIES ######################################
add_subdirectory(src)


### PLUGINS #############################################
add_subdirectory(plugins)