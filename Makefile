run-app:
	mkdir -p -v build-release && \
	cd build-release && \
	conan install .. && \
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. && \
	cmake --build . -j $(nproc) && \
	cd proxy && \
	./proxy --config=configs/config.yaml
