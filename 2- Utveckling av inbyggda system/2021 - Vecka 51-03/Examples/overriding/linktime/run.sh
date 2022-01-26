clear && mkdir -p build

gcc ./test/test.c ./module/module.c ./test/double/dependency.c -I./module -I./test/double -lunity -o ./build/test
gcc ./src/main.c ./module/module.c ./dependency/dependency.c -I./module -I./dependency -o ./build/main

./build/main
./build/test
