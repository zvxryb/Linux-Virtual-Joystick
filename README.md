# Linux-Virtual-Joystick
Allows users to create virtual joysticks in Python code

I wrote this a long, long time ago (it was "old code" according to my commit message 7 years ago...) and do not currently maintain it.  It _should_ still work on any Linux system with Python 2.x and UInput ..._maybe_.

## How do I use this?
1. Build with build.sh, adjust the build script as necessary.
2. Create a python module implementing the necessary callback functions (see example.py or testjoy.py; not sure which is correct or more recent)
3. Add your module to ~/.config/vjoy/modules/
4. Run the executable, vjoy, with your module's name as a command-line argument (no extension)
