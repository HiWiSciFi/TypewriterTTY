#!/bin/bash

# git clone https://github.com/WiringPi/WiringPi.git
# cd WiringPi
# ./build debian
# mv debian-template/wiringpi*.deb .
# apt install ./wiringpi*.deb
# cd ..

export PATH=$PATH:$HOME/.local/bin

cd /app

make all
./typewriter
