# Cloning and building the project

To clone a project run this command
```bash
git clone --recurse-submodules https://github.com/LoGosX/FIZYKA2019
```

To build a project run following commands (in bash or Windows Power Shell) from project directory (directory that was created by ```git clone``` command):
```bash
cd build
cmake ..
cmake --build . --config Release
```
You can find the executable in ```build/Release/FIZYKA2019```

To build a project again run ```cmake --build . --config Release``` from ```build``` directory.

This chain of commands should clone repository, build it using cmake and run a program:
```bash
git clone --recurse-submodules https://github.com/LoGosX/FIZYKA2019
cd FIZYKA2019
cd build
cmake ..
cmake --build . --config Release
build/Release/FIZYKA2019
```

# Linux dependencies:

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
