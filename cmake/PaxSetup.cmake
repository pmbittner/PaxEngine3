add_definitions(-DPAX_WITH_JSON)

include(${CMAKE_CURRENT_LIST_DIR}/PaxCompilerDetection.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/PaxArchitectureDetection.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/PaxFlagsDefinition.cmake)

set(PAX3_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
set(PAX3_PLUGINS_DIR ${PAX3_DIR}/plugins)
set(PAX_LIB_DIR ${CMAKE_SOURCE_DIR}/${PAX_LIB_DIR_RELATIVE})
message("[PaxSetup.cmake] Setting PAX3_DIR to ${PAX3_DIR}")
message("[PaxSetup.cmake] Setting PAX3_PLUGINS_DIR to ${PAX3_PLUGINS_DIR}")
message("[PaxSetup.cmake] Setting PAX_LIB_DIR to ${PAX_LIB_DIR}")

include_directories(${PAX3_DIR}/libs/Polypropylene/include)
include_directories(${PAX3_DIR}/include)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    include_directories(${PAX_LIB_DIR}/win/include)
endif()
