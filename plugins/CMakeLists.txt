# Maps a plugin name (as used in PAX_PLUGINS and as component of find_package) to its directory and CMake target.
set(PAX_PLUGIN_DIR_sdl paxsdl)
set(PAX_PLUGIN_DIR_opengl paxopengl)
set(PAX_PLUGIN_DIR_physics paxphysics)
set(PAX_PLUGIN_DIR_tiles paxtiles)
set(PAX_PLUGIN_DIR_assimp paxassetimport)
set(PAX_PLUGIN_DIR_font paxfont)
set(PAX_PLUGIN_DIR_imgui paximgui)

set(PAX_PLUGIN_TARGET_sdl paxsdl)
set(PAX_PLUGIN_TARGET_opengl paxopengl)
set(PAX_PLUGIN_TARGET_physics paxphysics)
set(PAX_PLUGIN_TARGET_tiles paxtiles)
set(PAX_PLUGIN_TARGET_assimp paxassimp)
set(PAX_PLUGIN_TARGET_font paxfont)
set(PAX_PLUGIN_TARGET_imgui paximgui)

# Plugins reference each other (sdl -> opengl, tiles -> physics), so dependencies come first.
set(PAX_PLUGIN_ORDER opengl sdl physics tiles assimp font imgui)
set(PAX_PLUGIN_TARGETS)
foreach (plugin IN LISTS PAX_PLUGIN_ORDER)
    if (plugin IN_LIST PAX_PLUGINS)
        add_subdirectory(${PAX_PLUGIN_DIR_${plugin}})
        install(DIRECTORY ${PAX_PLUGIN_DIR_${plugin}}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
        # The plugin is exported as PaxEngine3::<plugin>, which is also what the alias in the build tree is called.
        set_target_properties(${PAX_PLUGIN_TARGET_${plugin}} PROPERTIES EXPORT_NAME ${plugin})
        list(APPEND PAX_PLUGIN_TARGETS ${PAX_PLUGIN_TARGET_${plugin}})
    endif()
endforeach()

if (PAX_BUILD_DEMOS)
    add_subdirectory(games)
endif()

set(PAX_INSTALLED_TARGETS ${PAX_INSTALLED_TARGETS} ${PAX_PLUGIN_TARGETS} ${PAX_PLUGIN_EXTRA_TARGETS} PARENT_SCOPE)
