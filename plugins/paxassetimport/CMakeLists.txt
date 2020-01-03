set(PAX_ASSIMP_SOURCE_FILES
        src/Plugin.cpp
        src/AssimpResourceLoader.cpp)

# Assimp

set(ASSIMP_DIRECTORY ${PAX_LIB_DIR}/assimp)
set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY})
set(ASSIMP_LINK_DIRECTORIES)
set(ASSIMP_LIBRARIES)

if (WIN32)
    if (${PAX_COMPILER_IS_MSVC})
        message("Building PaxAssimp with MSVC - Release")
        set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/cmake-build-release-msvc)
        set(ASSIMP_LIBRARY_NAME assimp-vc142-mt.lib)
        set(ASSIMP_IRRXML_NAME IrrXML.lib)
        set(ASSIMP_ZLIB_NAME zlibstatic.lib)
    elseif(${PAX_COMPILER_IS_GCC})
        if (${CMAKE_BUILD_TYPE} MATCHES Release)
            message("Building PaxAssimp with MinGW - Release")
            set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/cmake-build-release-mingw)
            set(ASSIMP_LIBRARY_NAME libassimp.a)
            set(ASSIMP_IRRXML_NAME libIrrXML.a)
            set(ASSIMP_ZLIB_NAME libzlibstatic.a)
        elseif(${CMAKE_BUILD_TYPE} MATCHES Debug)
            message("Building PaxAssimp with MinGW - Debug")
            set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/cmake-build-debug-mingw)
            set(ASSIMP_LIBRARY_NAME libassimpd.a)
            set(ASSIMP_IRRXML_NAME libIrrXMLd.a)
            set(ASSIMP_ZLIB_NAME libzlibstaticd.a)
        endif(${CMAKE_BUILD_TYPE} MATCHES Release)
    endif(${PAX_COMPILER_IS_MSVC})

    set(ASSIMP_IRRXML_DIR ${ASSIMP_BUILD_DIRECTORY}/contrib/irrXML)
    set(ASSIMP_ZLIB_DIR   ${ASSIMP_BUILD_DIRECTORY}/contrib/zlib)

    set(ASSIMP_LINK_DIRECTORIES
            ${ASSIMP_LINK_DIRECTORIES}
            ${ASSIMP_IRRXML_DIR}
            ${ASSIMP_ZLIB_DIR})

    set(ASSIMP_LIBRARIES
            ${ASSIMP_LIBRARIES}
            ${ASSIMP_BUILD_DIRECTORY}/code/${ASSIMP_LIBRARY_NAME}
            ${ASSIMP_IRRXML_DIR}/${ASSIMP_IRRXML_NAME}
            ${ASSIMP_ZLIB_DIR}/${ASSIMP_ZLIB_NAME})
elseif(UNIX)
    message("Building PaxAssimp on Unix")
    set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/build)
    set(ASSIMP_IRRXML_DIR ${ASSIMP_BUILD_DIRECTORY}/contrib/irrXML)
    set(ASSIMP_ZLIB_DIR   ${ASSIMP_BUILD_DIRECTORY}/contrib/zlib)

    set(ASSIMP_LINK_DIRECTORIES
            ${ASSIMP_LINK_DIRECTORIES}
            ${ASSIMP_IRRXML_DIR})

    set(ASSIMP_LIBRARIES
            ${ASSIMP_LIBRARIES}
            ${ASSIMP_BUILD_DIRECTORY}/code/libassimp.a
            ${ASSIMP_IRRXML_DIR}/libIrrXML.a)


    # For now we always use the zlib version, assimp builds on its own to
    # avoid version conflicts.

    #FIND_PACKAGE(ZLIB)
    #if(ZLIB_FOUND)
    #    set(ASSIMP_LIBRARIES
    #            ${ASSIMP_LIBRARIES}
    #            ${ZLIB_LIBRARIES})
    #else()
        # use z3 files built by assimp
        set(ASSIMP_LINK_DIRECTORIES
                ${ASSIMP_LINK_DIRECTORIES}
                ${ASSIMP_ZLIB_DIR})

        set(ASSIMP_LIBRARIES
                ${ASSIMP_LIBRARIES}
                ${ASSIMP_ZLIB_DIR}/libzlibstatic.a)
    #endif(ZLIB_FOUND)
endif(WIN32)

# Add directory of built assimp lib file
set(ASSIMP_LINK_DIRECTORIES
        ${ASSIMP_LINK_DIRECTORIES}
        ${ASSIMP_BUILD_DIRECTORY}/code)

include_directories(${ASSIMP_DIRECTORY}/include)
include_directories(${ASSIMP_BUILD_DIRECTORY}/include)
link_directories(${ASSIMP_LINK_DIRECTORIES})

##

include_directories(include)
set(HEADERS_FOR_CLION include/paxassimp/Plugin.h include/paxassimp/AssimpResourceLoader.h)
add_library(paxassimp ${HEADERS_FOR_CLION} ${PAX_ASSIMP_SOURCE_FILES})
target_link_libraries(paxassimp ${ASSIMP_LIBRARIES})