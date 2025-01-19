#!/bin/bash
sudo apt update
sudo apt upgrade -y
sudo apt update
sudo apt full-upgrade -y
sudo apt install build-essential git -y
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build debian
mv debian-template/wiringpi*.deb .
sudo apt install ./wiringpi*.deb
cd ..

git clone --recursive https://github.com/HiWiSciFi/TypewriterTTY.git
cd TypewriterTTY/Raspi
make typewriter
