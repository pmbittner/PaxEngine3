{
  description = "PaxEngine3: a plugin-based game engine";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";
    polypropylene = {
      url = "github:pmbittner/Polypropylene";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs =
    {
      self,
      nixpkgs,
      polypropylene,
    }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f system nixpkgs.legacyPackages.${system});
    in
    {
      # The plugins to build can be chosen with
      #   paxengine3.packages.${system}.default.override { plugins = [ "sdl" "opengl" ]; }
      packages = forAllSystems (
        system: pkgs: {
          default = pkgs.callPackage ./package.nix {
            polypropylene = polypropylene.packages.${system}.default;
          };

          # All plugins and the demo games.
          everything = self.packages.${system}.default.override {
            plugins = [
              "sdl"
              "opengl"
              "physics"
              "tiles"
              "assimp"
              "font"
              "imgui"
            ];
            withDemos = true;
          };
        }
      );

      devShells = forAllSystems (
        system: pkgs: {
          default = pkgs.mkShell {
            inputsFrom = [ self.packages.${system}.default ];
            packages = [ pkgs.ninja ];
          };
        }
      );

      formatter = forAllSystems (_: pkgs: pkgs.nixfmt);
    };
}
