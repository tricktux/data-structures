{
  # Source: https://raw.githubusercontent.com/nixvital/flake-templates/main/templates/cpp-starter-kit/flake.nix
  description = "A template for Nix based C++ project setup.";

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
    llvm.url = "github:NixOS/llvm-project";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    # Add the system/architecture you would like to support here. Note that not
    # all packages in the official nixpkgs support all platforms.
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let
    pkgs = import nixpkgs {
      inherit system;

      # Add overlays here if you need to override the nixpkgs
      # official packages.
      overlays = [
        (_self: super: {
          llvm_latest = llvm.packages.llvm;
          clang_latest = llvm.packages.clang;
          clang-tools-extra = llvm.packages.clang-tools-extra;
        });
      ];
      
      # Uncomment this if you need unfree software (e.g. cuda) for
      # your project.
      #
      # config.allowUnfree = true;
    };
  in {
    devShells.default = pkgs.mkShell rec {
      # Update the name to something that suites your project.
      name = "data-structures";

      packages = with pkgs; [
        # Development Tools
        clang_latest
        clang-tools-extra
        cppcheck
        cmake
        cmakeCurses

        # Development time dependencies
        gtest

        # Build time and Run time dependencies
        spdlog
        abseil-cpp
      ];

      nativeBuildInputs = with pkgs; [
        clang-tools-extra.clangd
        clang-tools-extra.clangFormat
      ];
    };

    packages.default = pkgs.callPackage ./default.nix {};
  });
}

