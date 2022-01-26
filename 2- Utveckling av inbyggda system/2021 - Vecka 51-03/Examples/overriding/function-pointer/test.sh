clear
mkdir -p build
gcc ./test/test.c  ./module/module.c -I./module -lunity -o ./build/test
./build/test
