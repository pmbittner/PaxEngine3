set(PAX_ASSIMP_SOURCE_FILES
        src/Plugin.cpp
        src/AssimpResourceLoader.cpp)

# Assimp
option(PAX_ASSIMP_BUILDMANUALLY OFF)

set(ASSIMP_DIRECTORY ${PAX_LIB_DIR}/assimp)
set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY})
set(ASSIMP_LINK_DIRECTORIES)
set(ASSIMP_LIBRARIES)

set(ASSIMP_LOCAL_BUILD_DIR)

if (WIN32 AND ${PAX_COMPILER_IS_MSVC})
    if (PAX_ASSIMP_BUILDMANUALLY)
        message("Building PaxAssimp (Manual Build) with MSVC - Release")
        set(ASSIMP_LOCAL_BUILD_DIR bin/msvc-release)
        set(ASSIMP_LIBRARY_NAME_ASSIMP assimp-vc142-mt.lib)
        set(ASSIMP_LIBRARY_NAME_DRACO draco.lib)
        set(ASSIMP_LIBRARY_NAME_ZLIB zlibstatic.lib)
    else()
        # TODO: Deprecated?
        set(ASSIMP_BUILD_TYPE_DIR Release)
        set(ASSIMP_ZLIB_NAME zlibstatic.lib)

        if(${CMAKE_BUILD_TYPE} MATCHES Debug)
            set(ASSIMP_BUILD_TYPE_DIR Debug)
            set(ASSIMP_ZLIB_NAME zlibstaticd.lib)
        endif(${CMAKE_BUILD_TYPE} MATCHES Debug)
        message("Building PaxAssimp with MSVC - ${ASSIMP_BUILD_TYPE_DIR}")

        set(ASSIMP_ARCH x64)
        if (${PAX_OS_ARCHITECTURE} MATCHES x86)
            set(ASSIMP_ARCH Win32)
        endif()

        set(ASSIMP_TEMP_LIBSDIR ${ASSIMP_DIRECTORY}/lib/${ASSIMP_ARCH}/${ASSIMP_BUILD_TYPE_DIR})
        set(ASSIMP_LINK_DIRECTORIES ${ASSIMP_TEMP_LIBSDIR})

        set(ASSIMP_LIBRARIES
                ${ASSIMP_LIBRARIES}
                ${ASSIMP_TEMP_LIBSDIR}/assimp-vc140-mt.lib
                ${ASSIMP_TEMP_LIBSDIR}/IrrXML.lib
                ${ASSIMP_TEMP_LIBSDIR}/${ASSIMP_ZLIB_NAME})
    endif()
elseif(UNIX)
    message("Building PaxAssimp on Unix")
    set(ASSIMP_LOCAL_BUILD_DIR bin/build-release)
    set(ASSIMP_LIBRARY_NAME_ASSIMP libassimp.a)
    set(ASSIMP_LIBRARY_NAME_DRACO libdraco.a)
    set(ASSIMP_LIBRARY_NAME_ZLIB libzlibstatic.a)

    # For now we always use the zlib version, assimp builds on its own to
    # avoid version conflicts.

    #FIND_PACKAGE(ZLIB)
    #if(ZLIB_FOUND)
    #    set(ASSIMP_LIBRARIES
    #            ${ASSIMP_LIBRARIES}
    #            ${ZLIB_LIBRARIES})
    #else()
        # use z3 files built by assimp
    #endif(ZLIB_FOUND)
endif()

# If we do not have the case that we are on windows with a prebuild assimp
if (NOT (WIN32 AND NOT PAX_ASSIMP_BUILDMANUALLY))
    set(ASSIMP_BUILD_DIRECTORY ${ASSIMP_DIRECTORY}/${ASSIMP_LOCAL_BUILD_DIR})
    set(ASSIMP_LIBS_DIRECTORY ${ASSIMP_BUILD_DIRECTORY}/lib)
    set(ASSIMP_ZLIB_DIR ${ASSIMP_BUILD_DIRECTORY}/contrib/zlib)
    set(ASSIMP_LINK_DIRECTORIES
            ${ASSIMP_LINK_DIRECTORIES}
            ${ASSIMP_LIBS_DIRECTORY}
            ${ASSIMP_ZLIB_DIR}
            )
    set(ASSIMP_LIBRARIES
            ${ASSIMP_LIBRARIES}
            ${ASSIMP_LIBS_DIRECTORY}/${ASSIMP_LIBRARY_NAME_ASSIMP}
            ${ASSIMP_LIBS_DIRECTORY}/${ASSIMP_LIBRARY_NAME_DRACO}
            ${ASSIMP_ZLIB_DIR}/${ASSIMP_LIBRARY_NAME_ZLIB}
            )

    include_directories(${ASSIMP_BUILD_DIRECTORY}/include)
endif()

#message("PaxAssimp - Includes: ${ASSIMP_DIRECTORY}/include")
#message("PaxAssimp - Links: ${ASSIMP_LINK_DIRECTORIES}")
#message("PaxAssimp - Libs: ${ASSIMP_LIBRARIES}")
include_directories(${ASSIMP_DIRECTORY}/include)
link_directories(${ASSIMP_LINK_DIRECTORIES})

include_directories(include)
set(HEADERS_FOR_CLION include/paxassimp/Plugin.h include/paxassimp/AssimpResourceLoader.h)
add_library(paxassimp ${HEADERS_FOR_CLION} ${PAX_ASSIMP_SOURCE_FILES})
target_link_libraries(paxassimp ${ASSIMP_LIBRARIES})