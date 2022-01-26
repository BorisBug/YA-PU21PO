clear && mkdir -p build

gcc ./src/main.c ./module/module.c -I./module -o ./build/main

gcc ./test/double/double.c ./module/module.c ./test/test.c -I./module -I./test/double -DTEST -lunity -o ./build/test

./build/test
