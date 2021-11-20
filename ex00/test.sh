#!/bin/bash

tst(){
	echo "====================="
	echo -e "arg     : $@\n"
	./conv "$@"
	echo -e "=====================\n"
}

make

tst 1 1
tst 2147483647
tst 2147483647.0f
tst 2147483648
tst 2147483648.0f
tst -2147483649
tst -2147483649.0f
tst -0
tst -0.0
tst ""
tst a
tst b
tst 97
tst $(echo -e "\x01")

tst 0.000000001
tst 0.1
tst 1.902754389275