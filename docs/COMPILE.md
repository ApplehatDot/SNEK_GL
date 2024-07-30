*Compiling tutorial for Linux is under - or just press <a href=https://github.com/ApplehatDot/SNEK/blob/main/docs/COMPILE.md#kompilacja-gierki-snek-dla-system%C3%B3w-rodziny-linux>here...</a>*

# Compiling SNEK for win32 
Compiling SNEK (this project) for Microsoft Windows (win32) requires a MinGW 6.2.0 compiler and a code editor (if you will change some fragments in the code). Having win32 source files from `SNEK/source/win32/` extracted in the folder, like these below:
<div align="center">
  <img src="image/win32-files.png">
</div>

what I do when compiling, is to create `make.bat` and there I add lines for compiling, something like `Cmake` does:
```batch

windres snek.rc -O coff -o snek.res
rem Having freeglut files at C:\MinGW\freeglut\
gcc -c -o s_core.o core.c -I"C:\MinGW\freeglut"
gcc -c -o debugwin.o debugwin.c -I"C:\MinGW"

rem linking 3 object files to one executable
gcc -o SNEK.exe s_core.o debugwin.o -L"C:\MinGW\freeglut" -lfreeglut -lopengl32 -lglu32 -lgdi32 -luser32 -lwinmm -mwindows
SNEK.exe
```

by running `make.bat` it'll compile the application and will run it - 
### Congratulations! You've compiled win32 release of SNEK!

<img src="image/success-win32.png">

# Compiling SNEK for Linux 
### `NOTE: Compiling process for Linux release of SNEK is dynamic (to run sucessfully, a computer will require libraries installed); The application must be compiled on the same Computer, where it will be executed (any kind of tips/help would be great :,)`


### 1. Editing `sources.list` to renew support for older ubuntu distributions
If you are like me, and wanted to use Ubuntu 11.04 for compiling, to renew download sources in the `sources.list` use this command:
```bash
sudo sed -i -re 's/([a-z]{2}\.)?XX.archive.ubuntu.com|security.ubuntu.com/old-releases.ubuntu.com/g' /etc/apt/sources.list
```
Where ``XX.archive.ubuntu.com`` and XX are for other languages, like in polish: ``pl.archive.ubuntu.com`` and for it to work it must be ``old-releases.ubuntu.com`` :)

### 2. Compiling SNEK

Firstly, to compile SNEK for Linux you must download libraries:
```bash
sudo apt-get update
sudo apt-get install libgtk2.0-dev freeglut3 freeglut3-dev libglew-dev libglu1-mesa-dev
```
along with GCC compiler - using `build-essential`
When files are in the folder, open up the terminal and execute these commands (in the folder where files are):
```bash
$ gcc -o SNEK_linux main.c `pkg-config --cflags --libs gtk+-2.0` -lGL -lGLU -lglut -lm -std=c99
$ ./SNEK_linux
```

<img src="image/linux_compile.png">


### Congratulations! You've Compiled Linux release of SNEK!

<img src="image/linux-success.png">



