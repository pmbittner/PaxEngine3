set(HEADERS_FOR_CLION
        ../../include/paxutil/genericfactory/GenericFactory.h
        ../../include/paxutil/genericfactory/GenericFactoryService.h

        ../../include/paxutil/io/Settings.h
        ../../include/paxutil/io/FileTypeChecker.h

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

        ../../include/paxutil/property/construction/json/parsers/JsonEntityPrefabTransformationParser.h

        ../../include/paxutil/reflection/MemberCheck.h
        ../../include/paxutil/reflection/TypeHierarchy.h
        ../../include/paxutil/reflection/TypeRegister.h

        ../../include/paxutil/resources/Resources.h
        ../../include/paxutil/resources/ResourceHandle.h
        ../../include/paxutil/resources/ResourceLoader.h

        ../../include/paxutil/stdutils/OstreamOverloads.h

        ../../include/paxutil/Signature.h
        ../../include/paxutil/Sleep.h
        ../../include/paxutil/reflection/EngineFieldFlags.h
        ../../include/paxutil/resources/JsonResourceFieldWriter.h
        ../../include/paxutil/macros/Functional.h
        ../../include/paxutil/io/PrettyPrint.h)

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

add_library(paxutil ${HEADERS_FOR_CLION} ${SOURCE_FILES})
target_link_libraries(paxutil)