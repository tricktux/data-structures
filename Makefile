.PHONY: all cmake_debug cmake_release ninja_debug ninja_release clean clean_debug clean_release rerelease redebug debug release tests valgrind install

all: debug

cmake_debug:
	cmake -B build_debug -S . \
				-DCMAKE_BUILD_TYPE="Debug" \
				-DCMAKE_CXX_COMPILER="clang++" \
				-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
				-DENABLE_TESTING=ON \
				-DENABLE_INSTALL=ON \
				-GNinja

cmake_release:
	cmake -B build_release -S . \
				-DCMAKE_BUILD_TYPE="Release" \
				-DCMAKE_CXX_COMPILER="clang++" \
				-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
				-DENABLE_INSTALL=ON \
				-GNinja

ninja_debug:
	@[ -d build_debug ] || $(MAKE) cmake_debug
	ninja -C build_debug

ninja_release:
	@[ -d build_release ] || $(MAKE) cmake_release
	ninja -C build_release

clean: clean_debug clean_release

clean_debug:
	@[ -d build_debug ] && rm -rf build_debug || true

clean_release:
	@[ -d build_release ] && rm -rf build_release || true

debug: ninja_debug

redebug: clean_debug cmake_debug ninja_debug

release: ninja_release

rerelease: clean_release cmake_release ninja_release

tests: debug
	./build_debug/tests/dsa_tests

valgrind: debug
	valgrind --tool=memcheck --leak-check=full --vgdb=yes --vgdb-error=0 ./build_debug/tests/dsa_tests

install: release
	cd build_release && sudo ninja install
