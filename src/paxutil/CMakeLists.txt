set(HEADERS_FOR_CLION
        ../../include/paxutil/genericfactory/GenericFactory.h
        ../../include/paxutil/genericfactory/GenericFactoryService.h

        ../../include/paxutil/io/Settings.h

        ../../include/paxutil/lib/GlmIncludes.h
        ../../include/paxutil/lib/LibIncludes.h

        ../../include/paxutil/macros/PlatformIncludes.h

        ../../include/paxutil/math/Angles.h
        ../../include/paxutil/math/Basis.h
        ../../include/paxutil/math/BoundingBox.h
        ../../include/paxutil/math/Conversion.h
        ../../include/paxutil/math/Functions.h
        ../../include/paxutil/math/MathDefines.h
        ../../include/paxutil/math/Transformation.h
        ../../include/paxutil/math/json/JsonToTransformation.h

        ../../include/paxutil/property/construction/json/parsers/JsonPropertyContainerPrefabTransformationParser.h

        ../../include/paxutil/reflection/MemberCheck.h
        ../../include/paxutil/reflection/TypeHierarchy.h
        ../../include/paxutil/reflection/TypeRegister.h

        ../../include/paxutil/resources/Resources.h
        ../../include/paxutil/resources/ResourceHandle.h
        ../../include/paxutil/resources/ResourceLoader.h

        ../../include/paxutil/stdutils/OstreamOverloads.h

        ../../include/paxutil/Signature.h
        ../../include/paxutil/Sleep.h ../../include/paxutil/reflection/EngineFieldFlags.h)

set(SOURCE_FILES
        reflection/TypeHierarchy.cpp
        math/Conversion.cpp
        math/Angles.cpp
        math/Transformation.cpp
        io/Settings.cpp
        reflection/TypeRegister.cpp
        math/json/JsonToTransformation.cpp
        resources/ResourceLoader.cpp
        Signature.cpp
        resources/Resources.cpp)

add_library(paxutil ${HEADERS_FOR_CLION} ${SOURCE_FILES})
target_link_libraries(paxutil)