# PaxEngine3 - A Cross-Platform 2D/3D Game Engine with Focus on Usability and Extensibility

## Build Instructions

### General
The engine needs a `core.paxconfig`. You can just copy the `core.example.paxconfig` in place and rename it.

### Libraries
Additional libraries may be needed by some plugins or the engine core itself. Some of them may have to be build manually.

#### Libraries to install

Required: glm

The following libraries are needed by the respective plugins:

paxopengl: requires glew 2.0.0 or higher

paxsdl: requires SDL2, optional SDL2-image for texture loading

##### Windows and MinGW
**Ask Paul to get the necessary files for your compiler.**
##### Windows and MSVC
The files have to be placed in a directory called 'lib' next to the git repository.

Include files have to be in "lib/win/include".

Libraries have to be in "lib/win/libs".

SDL2 and SDL2_image have their own subdirectories.

**Ask Paul to get the necessary files for your compiler.**

##### Linux
The package names are `libsdl2-dev`, `libglm-dev`, `libsdl2-image-dev`


#### Libraries to build manually
These libraries have to be located in a directory called 'lib' next to the git repository like the files for MSVC.

##### Assimp (required by paxassetimport)
Check out their git repository and build manually. The build directory names
currently are:

    cmake-build-release-msvc
    cmake-build-release-mingw
    cmake-build-debug-mingw
    build (on Linux)

Before building a few adjustments have to be made to their CMakeLists.txt. First we want to build static libraries.
Hence, set the option `BUILD_SHARED_LIBS` to `OFF`.
For `MSVC` we have to set a compiler flag additionally.
Thus, append the compile option `/MT`
Change the lines

    ELSEIF(MSVC)
      # enable multi-core compilation with MSVC
      ADD_COMPILE_OPTIONS(/MP)

to

    ELSEIF(MSVC)
      # enable multi-core compilation with MSVC
      ADD_COMPILE_OPTIONS(/MP /MT)

Fow now we let assimp build its own version of zlib to avoid version conflicts.
Therefore, set `ASSIMP_BUILD_ZLIB` to `ON`.
For the same reason, the option `SYSTEM_IRRXML` has to be `OFF`.

##### Box2D (required by paxphysics)
We created a custom CMake-Project for Box2D, as the original one just delivers a makefile and does not split include and src files
into separate directories.

**Ask Paul to get the necessary files.**


#### DLLs on Windows
Both MinGW and MSVC require certain DLLs:

Dont know anymore who actually requires this one: zlib1.dll

For SDL2: SDL2.dll

For Glew: glew32.dll

For SDL2-Image: SDL2_image.dll
libjpeg-9.dll
libtiff-5.dll
libwebp-7.dll
libpng16-16.dll

For Assimp: assimp-vc140-mt.dll
assimp-vc140-mtd.dll

**Ask Paul to get the necessary files.**

