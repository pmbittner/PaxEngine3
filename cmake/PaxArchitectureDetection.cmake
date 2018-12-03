# Requires: Set variable CMAKE_MODULE_PATH
# Defines: PAX_OS_ARCHITECTURE

include(${CMAKE_MODULE_PATH}/TargetArch.cmake)
set(PAX_OS_ARCHITECTURE x64) # This is the default value
target_architecture(PAX_OS_ARCHITECTURE)
simplifyArchitecture(PAX_OS_ARCHITECTURE)
message("PAX_OS_ARCHITECTURE is ${PAX_OS_ARCHITECTURE}")