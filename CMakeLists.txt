cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### OPTIONS #############################################
option(WITH_SDL_IMAGE "True if build with SDL2Image" ON)
option(WITH_BOX2D "True if 2D physics with Box2D should be integrated" ON)

if(WITH_SDL_IMAGE)
    message("Building with: SDL_Image")
    add_definitions(-DPAX_WITH_SDLIMAGE)
endif()

if (WITH_BOX2D)
    message("Building with: Box2D")
    add_definitions(-DPAX_WITH_BOX2D)
endif()

set(PAX_RUN_PYTHON_PRECOMPILER FALSE)
if (PAX_RUN_PYTHON_PRECOMPILER)
    add_definitions(-DPAX_PYTHON_PRECOMPILED)
endif(PAX_RUN_PYTHON_PRECOMPILER)

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

#message("CMAKE_CXX_FLAGS        : ${CMAKE_CXX_FLAGS}")
#message("CMAKE_CXX_FLAGS_DEBUG  : ${CMAKE_CXX_FLAGS_DEBUG}")
#message("CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")


### SOURCE FILES ########################################

include_directories(include)

### API INCLUDES ########################################

include_directories(${PAX_LIB_DIR_RELATIVE}/Easylogging/include)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    include_directories(${PAX_LIB_DIR_RELATIVE}/win/include)

    set(EASYLOGGING_LIBRARY ${PAX_LIB_DIR}/Easylogging/bin/msvc/easylogging.lib)

    if (WITH_BOX2D)
        include_directories(${PAX_LIB_DIR}/Box2D)
        set(BOX2D_LIBRARY ${PAX_LIB_DIR}/Box2D/bin/msvc/box2d.lib)
    endif()

else()
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})

    link_directories(${PAX_LIB_DIR}/Easylogging/bin/mingw)
    set(EASYLOGGING_LIBRARY easylogging)

    if (WITH_BOX2D)
        include_directories(${PAX_LIB_DIR}/Box2D)
        link_directories(${PAX_LIB_DIR}/Box2D/bin/mingw)
        set(BOX2D_LIBRARY box2d)
    endif()
endif()

### SUBDIRECTORIES ######################################
add_subdirectory(src)


### PLUGINS #############################################
add_subdirectory(plugins)


### EXECUTABLES #########################################
#add_executable(PaxEngine3 ${SOURCE_FILES})
#target_link_libraries(PaxEngine3 ${EASYLOGGING_LIBRARY} paxphysics paxutil paxsdl paxopengl paxcore)
#set_target_properties( yourexe PROPERTIES RUNTIME_OUTPUT_DIRECTORY E:/parsec/bin/ )

#add_executable(ResourceTest src/test/ResourceTest.cpp include/paxutil/stdutils/TuplePrinter.h include/paxutil/stdutils/Templates.h)
#target_link_libraries(ResourceTest paxio paxutil paxlib)
