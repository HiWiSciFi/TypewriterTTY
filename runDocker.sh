#!/bin/bash
sudo docker run --rm -h tty.int --device /dev/mem --device /dev/gpiomem --device /dev/ttyACM0 --restart always typewritertty
