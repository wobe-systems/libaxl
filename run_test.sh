#!/bin/sh
rm -f ./test/test_01
cp build/bin/test_01 ./test/test_01
cd test
./test_01

