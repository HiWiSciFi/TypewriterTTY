# syntax=docker/dockerfile:1.3-labs

FROM balenalib/raspberry-pi-debian
WORKDIR /app
COPY ./config/* /etc/TypewriterTTY/
COPY . .
RUN chmod -R 777 /app/Arduino

RUN groupadd -g 993 gpio
RUN useradd app -G dialout,gpio,kmem

RUN apt update
RUN apt upgrade -y
RUN apt update
RUN apt full-upgrade -y
RUN apt install build-essential git python3 python3-venv curl gettext fakeroot -y
RUN apt install ssh ed netcat man cowsay -y

RUN git clone https://github.com/WiringPi/WiringPi.git
WORKDIR /app/WiringPi
RUN ./build debian
RUN mv debian-template/wiringpi*.deb .
RUN apt install ./wiringpi*.deb
WORKDIR /app

RUN make raspi

USER app

WORKDIR /home/app
RUN curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
RUN python3 get-platformio.py
RUN mkdir $HOME/.local
RUN mkdir $HOME/.local/bin
RUN ln -s ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
RUN ln -s ~/.platformio/penv/bin/pio ~/.local/bin/pio
RUN ln -s ~/.platformio/penv/bin/piodebuggdb ~/.local/bin/piodebuggdb
RUN echo export PATH="$PATH:$HOME/.local/bin" >> /home/app/.bashrc
RUN echo export PATH="$PATH:/usr/games" >> /home/app/.bashrc
RUN echo export PS1='$ ' >> /home/app/.bashrc

WORKDIR /home/app
CMD [ "/app/build.sh" ]
