# Defines:
#
# PAX_CPP_STANDARD
# CMAKE_CXX_FLAGS
# CMAKE_CXX_FLAGS_DEBUG
# CMAKE_CXX_FLAGS_RELEASE

set(PAX_CPP_STANDARD 11)

if (WIN32)
    message("Set flags for WIN32")
    if (${COMPILER_IS_MSVC})
        message("    and MSVC")

        set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /std:c++latest")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

        # Replace each occurence of /MD with /MT for static linking an avoid warnings for multiple definition
        set(CompilerFlags
                CMAKE_CXX_FLAGS
                CMAKE_CXX_FLAGS_DEBUG
                CMAKE_CXX_FLAGS_RELEASE
                CMAKE_C_FLAGS
                CMAKE_C_FLAGS_DEBUG
                CMAKE_C_FLAGS_RELEASE
                )
        foreach(CompilerFlag ${CompilerFlags})
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        endforeach()
    else(${COMPILER_IS_MSVC}) # condition for nested if
        message("    but not MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -std=c++${PAX_CPP_STANDARD}")# "-static-libgcc -static-libstdc++") #this may be wrong for unix
    endif(${COMPILER_IS_MSVC}) # condition for nested if
elseif(UNIX)
    message("Set flags for UNIX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${PAX_CPP_STANDARD}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
else(WIN32) # condition for nested if
    message(WARNING "Platform not specified. Correct behaviour not guaranteed.")
endif(WIN32) # condition for nested if