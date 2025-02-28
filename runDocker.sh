#!/bin/bash
sudo docker run -h tty.int -d --device /dev/mem --device /dev/gpiomem --device /dev/ttyACM0 --restart always typewritertty
