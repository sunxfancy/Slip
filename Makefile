slip:
	-mkdir build
	cd build && cmake .. && make

release:
	-mkdir build
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make

test:
	-mkdir build
	cd build && cmake .. -Dtest=ON && make

ci:
	-mkdir build
	cd build && cmake .. -Dtest=ON -DCOVERAGE=ON && make


package:
	-mkdir build
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make package

clean:
	-rm -rf ./build ./bin

.PHONY: package clean ci test release slip
