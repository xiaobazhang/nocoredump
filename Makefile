

all:
	mkdir -p build;
	cd build;cmake -DCMAKE_INSTALL_PREFIX=${BUILD_PATH} ..;make

clean:
	rm -rf build;rm -rf core.*;

install:
	cd build;make install;
