## Build Instructions

PaxEngine3 uses CMake. Third-party libraries are found with `find_package`, so any way of providing them works.
The recommended way is the included [Nix flake](https://nixos.wiki/wiki/Flakes), which pins all dependencies (including the compiler) and works on Linux and macOS.
Flakes have to be enabled once with `experimental-features = nix-command flakes` in `~/.config/nix/nix.conf`.

```bash
nix build                # engine with the default plugins -> ./result
nix build .#everything   # all plugins and the demo games
nix develop              # shell with all dependencies, for building with CMake directly
```

### Plugins and their dependencies

The engine core (`paxutil`, `paxio`, `paxrendering`, `paxcore`) always needs [Polypropylene](https://github.com/pmbittner/Polypropylene) and [glm](https://github.com/g-truc/glm).
Everything else is a plugin. Only the libraries of the plugins you select are looked up and required:

| Plugin    | CMake target | Additional dependencies                  | Needs plugin |
|-----------|--------------|------------------------------------------|--------------|
| `opengl`  | `paxopengl`  | OpenGL, GLEW                             |              |
| `sdl`     | `paxsdl`     | SDL2, SDL2_image (`WITH_SDL_IMAGE`)      | `opengl`     |
| `physics` | `paxphysics` | Box2D 2.4                                |              |
| `tiles`   | `paxtiles`   |                                          | `physics`    |
| `assimp`  | `paxassimp`  | assimp                                   |              |
| `font`    | `paxfont`    |                                          |              |
| `imgui`   | `paximgui`   | SDL2, GLEW, ANTLR 4.10 C++ runtime       | `sdl`, `opengl` |

The plugins are selected with the CMake variable `PAX_PLUGINS`, a semicolon-separated list (default: all plugins but `imgui`).
Plugins that others need are added automatically.
With Nix, the same is done with `override`, which also adds only the dependencies of these plugins:

```nix
paxengine3.packages.${system}.default.override { plugins = [ "sdl" "opengl" ]; }
```

The demo games in `plugins/games` are built with `-DPAX_BUILD_DEMOS=ON` (or `withDemos = true` in Nix), as far as their plugins are selected.

### Using the engine in a game

Install the engine (or take the Nix package) and request the plugins as components:

```cmake
find_package(PaxEngine3 3 CONFIG REQUIRED COMPONENTS sdl opengl physics)
target_link_libraries(MyGame PRIVATE PaxEngine3::paxcore PaxEngine3::sdl PaxEngine3::opengl PaxEngine3::physics)
```

The targets bring include directories, compile definitions, and the third-party libraries of the plugin.
`PaxEngine3_RESOURCE_DIR` points to the resources that ship with the engine (see below).
[Meshfold](https://github.com/pmbittner/Meshfold) is a complete example, including a Nix flake for the game.

### Working on the engine and a game together

A game can include the engine and Polypropylene from local checkouts, so all three are built in one incremental build, as an alternative to the installed packages.
Meshfold supports this through the CMake variables `MESHFOLD_LOCAL_ENGINE_DIR` and `MESHFOLD_LOCAL_POLYPROPYLENE_DIR`.
Your own game can do the same with `add_subdirectory` of both directories before using the targets above.
Polypropylene must be added first: the engine uses the target `Polypropylene::polypropylene` if it exists, and looks for an installed package otherwise.

With Nix, the pinned versions of the engine and Polypropylene can be replaced by local checkouts without editing any file:

```bash
nix build --override-input paxengine3 path:../PaxEngine3 --override-input polypropylene path:../Polypropylene
```

### Resources and `core.paxconfig`

The engine reads a file `core.paxconfig` from the working directory.
It defines two resource directories:

-   `core_engineResourceDirectory`: The resources that ship with the engine, i.e., this repository's `res` directory. It is installed to `share/paxengine3/res`.
-   `core_customResourceDirectory`: The resources of the game.

See `bin/core.example.paxconfig` for an example.

### Windows

Windows and MSVC are currently not supported by the build files.
Cross-compiling from Nix with MinGW (`pkgsCross.mingwW64`) is a possible way to bring it back with the same CMake files.
