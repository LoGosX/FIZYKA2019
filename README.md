# Cloning and building the project

## Cloning directory
To clone a project run this command
```bash
git clone --recurse-submodules https://github.com/LoGosX/FIZYKA2019
```
this command will download source for this project and for third party libraries.

## Building 
To build a project run following commands (in bash or Windows Power Shell) from project directory (directory that was created by ```git clone``` command):
```bash
cd build
cmake ..
cmake --build . --config Release
```

To build a project again run 
```bash
cmake --build . --config Release
``` 
from ```build``` directory.

## Summary
This chain of commands should clone repository and build it using cmake:
```bash
git clone --recurse-submodules https://github.com/LoGosX/FIZYKA2019
cd FIZYKA2019
cd build
cmake ..
cmake --build . --config Release
```

You can find the executable in ```FIZYKA2019/build/Release/FIZYKA2019``` or in ```FIZYKA2019/build/FIZYKA2019```.

# Dependencies:
To build this project the only thing that needs to be installed is ```cmake``` program.
## Linux dependencies
These packages reguired to make SFML work on Linux.
+ freetype
+ x11
+ xrandr
+ udev
+ opengl
+ flac
+ ogg
+ vorbis
+ vorbisenc
+ vorbisfile
+ openal
+ pthread

You can use following commands to install those on Ubuntu:
```bash
sudo apt-get install -y libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev
```
