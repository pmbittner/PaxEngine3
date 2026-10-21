cmake_minimum_required(VERSION 3.21)
project(PaxEngine3 VERSION 3.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

### OPTIONS #############################################

# The engine core (paxutil, paxio, paxrendering, paxcore) is always built.
# Everything else is a plugin, and every plugin brings its own third-party dependencies.
# Only the dependencies of the selected plugins are looked up and required.
set(PAX_ALL_PLUGINS sdl opengl physics tiles assimp font imgui)
set(PAX_PLUGINS "sdl;opengl;physics;tiles;assimp;font" CACHE STRING
        "Semicolon-separated list of plugins to build. Available: ${PAX_ALL_PLUGINS}")
option(PAX_BUILD_DEMOS "Build the demo games in plugins/games (they need the plugins they use)" OFF)

# Plugins that others are built on top of are added automatically.
if ("sdl" IN_LIST PAX_PLUGINS AND NOT "opengl" IN_LIST PAX_PLUGINS)
    list(APPEND PAX_PLUGINS opengl)
endif()
if ("tiles" IN_LIST PAX_PLUGINS AND NOT "physics" IN_LIST PAX_PLUGINS)
    list(APPEND PAX_PLUGINS physics)
endif()
if ("imgui" IN_LIST PAX_PLUGINS)
    foreach (dependency sdl opengl)
        if (NOT ${dependency} IN_LIST PAX_PLUGINS)
            list(APPEND PAX_PLUGINS ${dependency})
        endif()
    endforeach()
endif()

foreach (plugin IN LISTS PAX_PLUGINS)
    if (NOT plugin IN_LIST PAX_ALL_PLUGINS)
        message(FATAL_ERROR "Unknown plugin '${plugin}' in PAX_PLUGINS. Available: ${PAX_ALL_PLUGINS}")
    endif()
endforeach()
message(STATUS "PaxEngine3: plugins = ${PAX_PLUGINS}")

### DEPENDENCIES ########################################

# Polypropylene can either be installed or be part of the same build (add_subdirectory).
if (NOT TARGET Polypropylene::polypropylene)
    find_package(Polypropylene 1 CONFIG REQUIRED)
endif()
find_package(glm CONFIG REQUIRED)

set(PAX3_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# The directory with the engine's resources; consumers of the engine need it at runtime.
# It is also provided in the build tree for projects that include the engine with add_subdirectory.
if (NOT PROJECT_IS_TOP_LEVEL)
    set(PaxEngine3_RESOURCE_DIR ${PROJECT_SOURCE_DIR}/res PARENT_SCOPE)
endif()

### TARGETS #############################################

add_subdirectory(src)
add_subdirectory(plugins)

### INSTALL #############################################

# Resources the engine needs at runtime. The engine expects them in a single directory.
install(DIRECTORY res/ DESTINATION ${CMAKE_INSTALL_DATADIR}/paxengine3/res)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS ${PAX_INSTALLED_TARGETS}
        EXPORT PaxEngine3Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT PaxEngine3Targets
        NAMESPACE PaxEngine3::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PaxEngine3)

set(PAX_INSTALLED_PLUGINS ${PAX_PLUGINS})
set(PAX_SDL_IMAGE_DEPENDENCY "")
if (WITH_SDL_IMAGE)
    set(PAX_SDL_IMAGE_DEPENDENCY "find_dependency(SDL2_image)")
endif()
set(PAX_RESOURCE_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/paxengine3/res)
configure_package_config_file(
        cmake/PaxEngine3Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/PaxEngine3Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PaxEngine3
        PATH_VARS PAX_RESOURCE_INSTALL_DIR)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/PaxEngine3ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/PaxEngine3Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/PaxEngine3ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PaxEngine3)
