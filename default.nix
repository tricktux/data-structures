{ lib
, clangStdenv
, cmake
, spdlog
, abseil-cpp }:

clangStdenv.stdenv.mkDerivation rec {
    pname = "data-structures";
    version = "0.1.0";

    src = ./.;

    nativeBuildInputs = [ cmake ];
    buildInputs = [ spdlog abseil-cpp ];

    cmakeFlags = [
        "-DENABLE_TESTING=OFF"
        "-DENABLE_INSTALL=ON"
    ];

    meta = with lib; {
        homepage = "https://github.com/tricktux/data-structures";
        description = ''
            Opiniated data structures and algorithms library for C++.
        '';
        licencse = licenses.mit;
        platforms = with platforms; linux ++ darwin;
        maintainers = [ maintainers.breakds ];    
    };
}
