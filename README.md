## Install
1. Flash Micro-SD with Raspbian Lite (x64) and make sure to enable login via SSH/Password
2. Put it into the Raspberry Pi Zero 2 W
3. Connect the Raspi to a power supply
4. Connect and login to the Raspi via SSH
5. Run the following command:
```
curl -s https://raw.githubusercontent.com/HiWiSciFi/TypewriterTTY/refs/heads/development/Raspi/inst.sh | bash -s
```

## Maybe in the future?
- [ ] Rework Keyboard "hold-key-prevention" code
- [ ] Imitate more unavailable characters
- [ ] Make more characters available via custom keybinds
- [ ] Make use of more builtin features
- [ ] Make a PCB for better cable organization
- [ ] Proper error handling
- [ ] Properly handle CODE + C and CODE + D
- [ ] Move pass-through keycodes to config file
- [ ] Fully stable
- [ ] Handle SIGCHLD
- [ ] Log sensible data (clone pty + keyboard input metadata)
