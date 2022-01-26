clear && mkdir -p build && rm -rf ./build/*

gcc ./src/main.c ./module/module.c -I./module -o ./build/main && ./build/main

gcc ./test/test.c ./module/module.c  ./test/double/double.c -I./module -I./test/double -lunity -o ./build/test && ./build/test
