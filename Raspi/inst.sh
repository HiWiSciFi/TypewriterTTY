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

curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
mkdir $HOME/.local/bin
ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
# export PATH=$PATH:$HOME/.local/bin

git clone --recursive https://github.com/HiWiSciFi/TypewriterTTY.git
cd TypewriterTTY/Raspi
make typewriter


# RUN
pio run -t upload -d ../Arduino
