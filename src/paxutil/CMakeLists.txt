set(SOURCE_FILES
        Signature.cpp
        math/Functions.cpp
        math/Conversion.cpp
        math/Angles.cpp
        math/Transformation.cpp
        math/json/JsonToTransformation.cpp
        io/Settings.cpp
        reflection/TypeRegister.cpp
        reflection/TypeHierarchy.cpp
        resources/ResourceHandle.cpp
        resources/Resources.cpp
        resources/ResourceLoader.cpp
        io/PrettyPrint.cpp)

add_library(paxutil ${SOURCE_FILES})
add_library(PaxEngine3::paxutil ALIAS paxutil)
target_include_directories(paxutil PUBLIC
        $<BUILD_INTERFACE:${PAX3_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(paxutil PUBLIC Polypropylene::polypropylene glm::glm)
