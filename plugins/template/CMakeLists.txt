project(PaxTemplatePlugin)

find_package(PythonInterp 3 REQUIRED)
set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
        COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
        COMMENT "Precompiling ${PROJECT_NAME} (via Python)"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
        VERBATIM
)

include_directories(include)
set(HEADERS_FOR_CLION include/Plugin.h include/FollowEntityBehaviour.h)
add_library(TemplatePlugin ${HEADERS_FOR_CLION} src/Plugin.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp)