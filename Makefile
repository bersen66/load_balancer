run-app:
	mkdir -p -v build && \
	cd build && \
	conan install .. && \
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. && \
	cmake --build . -j $(nproc) && \
	cd proxy && \
	./proxy --config=configs/config.yaml


install:
	mkdir -p -v build && \
	cd build && \
	conan install .. --build=missing
