{
  lib,
  stdenv,
  cmake,
  glm,
  polypropylene,
  SDL2,
  SDL2_image,
  libwebp,
  libtiff,
  libpng,
  libjpeg,
  glew,
  libGL,
  box2d_2,
  assimp,
  antlr4_10,
  # The plugins to build. Only the dependencies of these plugins are needed.
  # Available: sdl, opengl, physics, tiles, assimp, font, imgui
  plugins ? [
    "sdl"
    "opengl"
    "physics"
    "tiles"
    "assimp"
    "font"
  ],
  withDemos ? false,
}:

let
  has = plugin: builtins.elem plugin plugins;
  # Plugins that are built on top of others.
  needsOpengl = has "opengl" || has "sdl" || has "imgui";
  needsSdl = has "sdl" || has "imgui";
  needsPhysics = has "physics" || has "tiles";
in
stdenv.mkDerivation {
  pname = "paxengine3";
  version = "3.0.0";

  src = lib.fileset.toSource {
    root = ./.;
    fileset = lib.fileset.unions [
      ./CMakeLists.txt
      ./cmake
      ./include
      ./src
      ./plugins
      ./res
    ];
  };

  nativeBuildInputs = [ cmake ];

  # Propagated, because the installed CMake package looks them up for its consumers.
  propagatedBuildInputs = [
    glm
    polypropylene
  ]
  ++ lib.optionals needsSdl [
    SDL2
    SDL2_image
    # SDL2_image's CMake package looks for the image libraries it was built with.
    libwebp
    libtiff
    libpng
    libjpeg
  ]
  ++ lib.optionals needsOpengl [
    glew
    libGL
  ]
  ++ lib.optional needsPhysics box2d_2
  ++ lib.optional (has "assimp") assimp
  ++ lib.optional (has "imgui") antlr4_10.runtime.cpp;

  cmakeFlags = [
    (lib.cmakeFeature "PAX_PLUGINS" (lib.concatStringsSep ";" plugins))
    (lib.cmakeBool "PAX_BUILD_DEMOS" withDemos)
  ];

  meta = {
    description = "Plugin-based game engine built on the Polypropylene entity-property system";
    license = lib.licenses.gpl3Only;
    platforms = lib.platforms.unix;
  };
}
