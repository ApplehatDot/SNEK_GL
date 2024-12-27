# Compiling SNEK for win32 

Keep in mind that MinGW port of freeglut is available <a href="https://www.transmissionzero.co.uk/software/freeglut-devel/">Here</a>, and its contents are extracted in `MinGW/freeglut/*.*`, putting them into the MinGW files (a.k.a `MinGW/include` etc.) will work.

Compiling SNEK (this project) for Microsoft Windows (win32) requires a MinGW 6.2.0 compiler and a code editor (if you will change some fragments in the code). Having win32 source files from `SNEK/source/win32/` extracted in the folder, like these below:
<div align="center">
  <img src="image/win32-files.png">
</div>

... its just running the makefile: `mingw32-make all` and here you go, 
### Congratulations! You've compiled win32 release of SNEK!

<img src="image/success-win32.png">




