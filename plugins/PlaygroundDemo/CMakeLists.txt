project(PlaygroundDemo)

set(PAX_PLAYGROUNDDEMO_SOURCE_FILES src/main.cpp  src/Plugin.cpp)

if (PAX_RUN_PYTHON_PRECOMPILER)
    find_package(PythonInterp 3 REQUIRED)
    set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../precompiler/pluginprecompiler.py)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMAND ${PYTHON_EXECUTABLE} ${SCRIPT_DIR} PAX::PlaygroundDemo ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp
            COMMENT "Precompiling ${PROJECT_NAME} (via Python)"
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/
            VERBATIM
    )
    set(PAX_PLAYGROUNDDEMO_SOURCE_FILES ${PAX_PLAYGROUNDDEMO_SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugin.generated.cpp)
endif (PAX_RUN_PYTHON_PRECOMPILER)

include_directories(include)
include_directories(../paxsdl/include)
include_directories(../paxopengl/include)
include_directories(../paxassetimport/include)
set(HEADERS_FOR_CLION
        include/playgrounddemo/Plugin.h
        include/playgrounddemo/Demo.h)

add_executable(PlaygroundDemo ${PAX_PLAYGROUNDDEMO_SOURCE_FILES} ${HEADERS_FOR_CLION})
target_link_libraries(PlaygroundDemo ${EASYLOGGING_LIBRARY} paxassimp paxutil paxsdl paxopengl paxcore)
set_target_properties(PlaygroundDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Demo)