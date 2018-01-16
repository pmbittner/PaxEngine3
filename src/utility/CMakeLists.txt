add_library(paxutil StringUtils.cpp io/CSVSettingsLoader.cpp io/CSVRow.cpp math/Conversion.cpp reflection/TypeHierarchy.cpp)
target_link_libraries(paxutil)