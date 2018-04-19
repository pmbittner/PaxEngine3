##### PaxEngine3 -- Cross-Platform 2D/3D Game Engine with Focus on 2D

### Build Instructions

## Windows

The project should build with MinGW as well as MSVC. Additional libraries are needed. Those have to be located in a directory called ```lib``` next to the git repository.
Ask Paul to get the necessary files.

The build folder has to have at least two levels of directories. That is to allow split your builds for different configurations or compilers:

	build/
	    mingw/
		    MinGW build files here
	    msvc/
		    MSVC build files here

Otherwise, the program won't be able to find the ``res`` directory to load its resources (for now).