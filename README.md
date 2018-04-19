# PaxEngine3 - A Cross-Platform 2D/3D Game Engine with Focus on 2D and Software Architecture

## Build Instructions

### General
Additional libraries are needed. Those have to be located in a directory called `lib` next to the git repository.

**Ask Paul to get the necessary files for your operating system.**

The build folder has to have at least two levels of directories. That allows splitting builds for different configurations, compilers, release/debug:

    CMakeLists.txt
    include/
	src/
	res/
	... other files and directories
	build/
	    mingw/
		    MinGW build files here
	    msvc/
		    MSVC build files here
			
Otherwise, the program won't be able to find the `res` directory to load its resources (for now).
(Detecting the resource folder at runtime is a feature for the future.)

### Windows
The project should build with MinGW as well as MSVC. To execute the program some DLL-files have to be put into the executables directory.

**Ask Paul to get the necessary files for your operating system.**

### Linux
Required packages: `libsdl2-dev`

Optional packages: `libsdl2-image-dev`