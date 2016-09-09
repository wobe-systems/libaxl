#!/bin/sh
rm ./test/test_01
cp ./build/freeBSD_x86-32/test/test_01 ./test
cd ./test
./test_01

