#!/bin/sh
rm -f ./test/test_01
cp ./build/freeBSD_x86-64/test/test_01 ./test
cd ./test
./test_01

