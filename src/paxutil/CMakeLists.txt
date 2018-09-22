set(HEADERS_FOR_CLION
        ../../include/paxutil/macros/OSDefines.h
        ../../include/paxutil/Sleep.h

        ../../include/paxutil/lib/LibIncludes.h
        ../../include/paxutil/stdutils/CollectionUtils.h
        ../../include/paxutil/macros/MacroIncludes.h
        ../../include/paxutil/io/CSVSettingsLoader.h
        ../../include/paxutil/io/CSVRow.h
        ../../include/paxutil/StringUtils.h
        ../../include/paxutil/reflection/MemberCheck.h
        ../../include/paxutil/Dependency.h
        ../../include/paxutil/datastructures/TypeMap.h
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
        ../../include/paxutil/math/Transformation.h ../../include/paxutil/property/Property.h ../../include/paxutil/property/PropertyContainer.h ../../include/paxutil/property/PropertyReflectionData.h ../../include/paxutil/property/PropertyDependencies.h ../../include/paxutil/memory/Allocator.h ../../include/paxutil/memory/AllocationService.h ../../include/paxutil/memory/allocators/MallocAllocator.h)

set(SOURCE_FILES
        StringUtils.cpp
        io/CSVSettingsLoader.cpp
        io/CSVRow.cpp
        io/Path.cpp
        reflection/TypeHierarchy.cpp
        math/Conversion.cpp
        math/Angles.cpp
        math/Transformation.cpp property/PropertyContainer.cpp)

add_library(paxutil ${HEADERS_FOR_CLION} ${SOURCE_FILES})
target_link_libraries(paxutil)