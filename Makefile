.PHONY: all cmake_debug cmake_release ninja_debug ninja_release clean clean_debug clean_release rerelease redebug debug release

all: debug

TEST_DATA_DIR = "submodules/icc-profile-processing/IccProfileAnalysis/tests/data"

cmake_debug:
	cmake -B build_debug -S . \
				-DCMAKE_BUILD_TYPE="Debug" \
				-DCMAKE_CXX_COMPILER="clang++" \
				-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
				-GNinja
	ln -sf build_debug/compile_commands.json compile_commands.json

cmake_release:
	cmake -B build_release -S . \
				-DCMAKE_BUILD_TYPE="Release" \
				-DCMAKE_CXX_COMPILER="clang++" \
				-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
				-GNinja
	ln -sf build_release/compile_commands.json compile_commands.json

ninja_debug:
	ninja -C build_debug

ninja_release:
	ninja -C build_release

clean: clean_debug clean_release

clean_debug:
	[ -d build_debug ] && rm -rf build_debug || true

clean_release:
	[ -d build_release ] && rm -rf build_release || true

debug: ninja_debug

redebug: clean_debug cmake_debug ninja_debug

release: ninja_release

rerelease: clean_release cmake_release ninja_release

