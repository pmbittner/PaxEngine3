set(HEADERS_FOR_CLION
        ../../include/utility/macros/OSDefines.h
        ../../include/utility/Sleep.h

        ../../include/utility/lib/LibIncludes.h
        ../../include/utility/stdutils/CollectionUtils.h
        ../../include/utility/macros/MacroIncludes.h
        ../../include/utility/io/CSVSettingsLoader.h
        ../../include/utility/io/CSVRow.h
        ../../include/utility/StringUtils.h
        ../../include/utility/reflection/MemberCheck.h
        ../../include/utility/Dependency.h
        ../../include/utility/datastructures/TypeMap.h
        ../../include/utility/Signature.h
        ../../include/utility/io/FileTypeChecker.h
        ../../include/utility/math/Conversion.h
        ../../include/utility/reflection/TemplateTypeToString.h
        ../../include/utility/macros/CompilerDetection.h
        ../../include/utility/macros/BuildType.h
        ../../include/utility/reflection/TypeInfo.h
        ../../include/utility/reflection/TypeHierarchy.h
        ../../include/utility/math/Functions.h
        ../../include/utility/math/BoundingBox.h ../../include/utility/stdutils/OstreamOverloads.h)

add_library(paxutil ${HEADERS_FOR_CLION} StringUtils.cpp io/CSVSettingsLoader.cpp io/CSVRow.cpp math/Conversion.cpp reflection/TypeHierarchy.cpp)
target_link_libraries(paxutil)