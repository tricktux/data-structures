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
      in
      {
        devShell = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
          # Update the name to something that suites your project.
          name = "data-structures";

          packages = with pkgs; [
            # Development Tools
            # debugger
            doxygen
            llvm.lldb
            gdb
            ninja

            # Lsp and tools
            clang-tools

            # other tools
            cppcheck
            valgrind
            cmake
            cmakeCurses

            # Libs
            gtest
          ];

          shellHook = ''
            export MY_ENV_VAR="my-env-value"
          '';
        };

      }
    );
}
