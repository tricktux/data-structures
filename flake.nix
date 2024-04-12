{
  # Source: https://raw.githubusercontent.com/nixvital/flake-templates/main/templates/cpp-starter-kit/flake.nix
  description = "Opinionated Data Structures implemented in C++";

  inputs = {
    # Pointing to the current stable release of nixpkgs. You can
    # customize this to point to an older version or unstable if you
    # like everything shining.
    #
    # E.g.
    #
    # nixpkgs.url = "github:NixOS/nixpkgs/unstable";
    nixpkgs.url = "github:NixOS/nixpkgs/23.11";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }@inputs:
    utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
        llvm = pkgs.llvmPackages_latest;
        data-structures = (with pkgs; llvm.stdenv.mkDerivation {
          pname = "data-structures";
          version = "0.0.1";
          src = ./.;
          nativeBuildInputs = [
            gtest
            clang
            cmake
          ];
        }
        );
      in
      rec {
        defaultApp = utils.lib.mkApp {
          drv = defaultPackage;
        };
        defaultPackage = data-structures;
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            doxygen
            llvm.lldb
            gdb
            ninja
            cppcheck
            valgrind
            cmake
            cmakeCurses

            # Libs
            gtest
            data-structures
          ];
        };
      }
    );
}
