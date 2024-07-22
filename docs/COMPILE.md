*kompilacja dla linux jest na dole - albo naciśnij <a href=https://github.com/ApplehatDot/SNEK/edit/main/docs/COMPILE.md#kompilacja-gierki-snek-dla-system%C3%B3w-rodziny-gnulinux>tutaj...</a>*

# Kompilacja Gierki SNEK dla systemów win32 
Kompilowanie SNEK dla systemów Microsoft Windows (win32) wymaga kompilatora MinGW 6.2.0 i edytora kodu (jeśli masz zamiar dopisywać do kodu). Mając pliki z `SNEK/source/win32/`
<div align="center">
  <img src="image/win32-files.png">
</div>

zwykle kompilując tworze plik `make.bat` i tam dodaje linijki kompilujące, tak coś w stylu make:
```batch
rem Mając pliki freeglut w C:\MinGW\freeglut\
gcc -c -o s_core.o core.c -I"C:\MinGW\freeglut"
gcc -c -o debugwin.o debugwin.c -I"C:\MinGW"

rem linkowanie 3 plików *.object do jednego pliku *.EXE
gcc -o SNEK.exe s_core.o debugwin.o -L"C:\MinGW\freeglut" -lfreeglut -lopengl32 -lglu32 -lgdi32 -luser32 -lwinmm -mwindows
SNEK.exe
```

uruchamiając plik `make.bat` skompiluje aplikacje i ją uruchomi - 
### brawo, skompilowałeś SNEK dla win32!

<img src="image/success-win32.png">

# Kompilacja Gierki SNEK dla systemów rodziny GNU/Linux
`NOTE: Kompilacja programu SNEK dla systemów Linux działa dynamicznie, program musi być skompilowany na komputerze, na którym ma być uruchamiany`

wstępnie, żeby skompilować projekt dla systemów Linux trzeba zainstalować biblioteki:
```bash
sudo apt-get update
sudo apt-get install libgtk2.0-dev freeglut3 freeglut3-dev libglew-dev libglu1-mesa-dev
```
i w tym kompilator gcc.
kiedy pliki już są w folderze, otwórz terminal i wpisz komende:
```bash
$ gcc -o SNEK_linux main.c `pkg-config --cflags --libs gtk+-2.0` -lGL -lGLU -lglut -lm -std=c99
$ ./SNEK_linux
```

<img src="image/linux_compile.png">


### brawo, skompilowałeś SNEK'a dla linux!

<img src="image/linux-success.png">



