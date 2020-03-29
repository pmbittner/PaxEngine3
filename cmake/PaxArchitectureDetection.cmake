# Defines: PAX_OS_ARCHITECTURE

set(PAX_OS_ARCHITECTURE x86) # This is the default value

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PAX_OS_ARCHITECTURE x64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PAX_OS_ARCHITECTURE x86)
else()
    message(WARNING "Unknown Architecture: CMAKE_SIZEOF_VOID_P is ${CMAKE_SIZEOF_VOID_P}")
    message(WARNING "Continuing with ${PAX_OS_ARCHITECTURE}")
endif()

message("PAX_OS_ARCHITECTURE is ${PAX_OS_ARCHITECTURE}")