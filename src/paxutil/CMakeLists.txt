set(HEADERS_FOR_CLION
        ../../include/paxutil/macros/OSDetection.h
        ../../include/paxutil/Sleep.h

        ../../include/paxutil/lib/LibIncludes.h
        ../../include/paxutil/stdutils/CollectionUtils.h
        ../../include/paxutil/macros/MacroIncludes.h
        ../../include/paxutil/StringUtils.h
        ../../include/paxutil/reflection/MemberCheck.h
        ../../include/paxutil/Dependency.h
        ../../include/paxutil/reflection/TypeMap.h
        ../../include/paxutil/Signature.h
        ../../include/paxutil/io/FileTypeChecker.h
        ../../include/paxutil/math/Conversion.h
        ../../include/paxutil/reflection/TemplateTypeToString.h
        ../../include/paxutil/macros/CompilerDetection.h
        ../../include/paxutil/macros/BuildType.h
        ../../include/paxutil/reflection/TypeHandle.h
        ../../include/paxutil/reflection/TypeHierarchy.h
        ../../include/paxutil/math/Functions.h
        ../../include/paxutil/math/BoundingBox.h
        ../../include/paxutil/stdutils/OstreamOverloads.h
        ../../include/paxutil/macros/PlatformIncludes.h
        ../../include/paxutil/stdutils/makeunique.h
        ../../include/paxutil/math/Angles.h
        ../../include/paxutil/math/MathDefines.h
        ../../include/paxutil/math/Basis.h
        ../../include/paxutil/math/Transformation.h ../../include/paxutil/property/Property.h ../../include/paxutil/property/PropertyContainer.h ../../include/paxutil/property/PropertyDependencies.h ../../include/paxutil/memory/Allocator.h ../../include/paxutil/memory/AllocationService.h ../../include/paxutil/memory/allocators/MallocAllocator.h ../../include/paxutil/io/Settings.h ../../include/paxutil/property/PropertyAnnotations.h ../../include/paxutil/property/construction/PropertyContainerPrefab.h ../../include/paxutil/genericfactory/GenericFactoryService.h ../../include/paxutil/genericfactory/GenericFactory.h ../../include/paxutil/reflection/TypeRegister.h ../../include/paxutil/property/construction/ContentProvider.h ../../include/paxutil/macros/Definitions.h)

set(SOURCE_FILES
        StringUtils.cpp
        io/Path.cpp
        reflection/TypeHierarchy.cpp
        math/Conversion.cpp
        math/Angles.cpp
        math/Transformation.cpp property/PropertyContainer.cpp io/Settings.cpp reflection/TypeRegister.cpp property/construction/ContentProvider.cpp)

add_library(paxutil ${HEADERS_FOR_CLION} ${SOURCE_FILES})
target_link_libraries(paxutil)