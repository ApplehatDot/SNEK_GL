# Compiling SNEK for win32 

Keep in mind that MinGW port of freeglut is available <a href="https://www.transmissionzero.co.uk/software/freeglut-devel/">Here</a>, and its contents are extracted in `MinGW/freeglut/*.*`, putting them into the MinGW files (a.k.a `MinGW/include` etc.) will work.

Compiling SNEK (this project) for Microsoft Windows (win32) requires a MinGW 6.2.0 compiler and a code editor (if you will change some fragments in the code). Having win32 source files from `SNEK/source/win32/` extracted in the folder, like these below:
<div align="center">
  <img src="image/win32-files.png">
</div>

what I do when compiling, is to create `make.bat` and there I add lines for compiling, something like `Cmake` does:
```batch

windres snek.rc -O coff -o snek.res
rem Having freeglut files at C:\MinGW\freeglut\
g++ -shared -o AboutDialog.dll AboutDiag.c -lgdi32
gcc -c -o s_core.o core.c -I"C:\MinGW\freeglut"
gcc -c -o obj/ReadPackets.o src/ReadPackets.c

rem linking 3 object files to one executable
gcc -o SNEK.exe s_core.o snek.res ReadPackets.o -L"C:\MinGW\freeglut" -lfreeglut -lopengl32 -lglu32 -lgdi32 -luser32 -lwinmm -mwindows
SNEK.exe
```

by running `make.bat` it'll compile the application and will run it - 
### Congratulations! You've compiled win32 release of SNEK!

<img src="image/success-win32.png">




