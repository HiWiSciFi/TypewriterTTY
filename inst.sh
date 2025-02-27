# apt update
# apt upgrade -y
# apt update
# apt full-upgrade -y
apt install build-essential git python3 curl -y
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build debian
mv debian-template/wiringpi*.deb .
apt install ./wiringpi*.deb
cd ..

curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
mkdir $HOME/.local
mkdir $HOME/.local/bin
ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
export PATH=$PATH:$HOME/.local/bin
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | tee /etc/udev/rules.d/99-platformio-udev.rules
# service udev restart

# git clone https://github.com/HiWiSciFi/TypewriterTTY.git
# cd TypewriterTTY/Raspi
# git submodule init
# git submodule update
