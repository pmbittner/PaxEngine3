function(assertPathExists name path)
    if (EXISTS ${path})

    else()
        message(FATAL_ERROR "Path ${name} = ${path} does not exist!")
    endif()
endfunction()