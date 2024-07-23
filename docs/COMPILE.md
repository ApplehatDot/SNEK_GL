*kompilacja dla linux jest na dole - albo naciśnij <a href=https://github.com/ApplehatDot/SNEK/blob/main/docs/COMPILE.md#kompilacja-gierki-snek-dla-system%C3%B3w-rodziny-linux>tutaj...</a>*

# Kompilacja Gierki SNEK dla systemów win32 
Kompilowanie SNEK dla systemów Microsoft Windows (win32) wymaga kompilatora MinGW 6.2.0 i edytora kodu (jeśli masz zamiar dopisywać do kodu). Mając pliki z `SNEK/source/win32/` już wyodrębnione w folderze tak jak na ilustracji:
<div align="center">
  <img src="image/win32-files.png">
</div>

zwykle kompilując tworze plik `make.bat` i tam dodaje linijki kompilujące, tak coś w stylu make:
```batch
windres snek.rc -O coff -o snek.res

rem Mając pliki freeglut w C:\MinGW\freeglut\
gcc -c -o s_core.o core.c -I"C:\MinGW\freeglut"
gcc -c -o debugwin.o debugwin.c -I"C:\MinGW"

rem linkowanie 3 plików *.object i *.res do jednego pliku *.EXE
gcc -o SNEK.exe s_core.o debugwin.o snek.res -L"C:\MinGW\freeglut" -lfreeglut -lopengl32 -lglu32 -lgdi32 -luser32 -lwinmm -mwindows
SNEK.exe
```

uruchamiając plik `make.bat` skompiluje aplikacje i ją uruchomi - 
### brawo, skompilowałeś SNEK dla win32!

<img src="image/success-win32.png">

# Kompilacja Gierki SNEK dla systemów rodziny Linux
#### `NOTE: Kompilacja programu SNEK dla systemów Linux działa dynamicznie, program musi być skompilowany na komputerze, na którym ma być uruchamiany`

### 1. edytowanie ``sources.list`` aby wznowić wsparcie dla starych dystrybucji ubuntu
jeżeli jesteś jak ja, I chcesz używać Ubuntu 11.04 do kompilacji, aby przeedytować strony z jakich ma pobierać pakiety, użyj komendy:
```bash
sudo sed -i -re 's/([a-z]{2}\.)?XX.archive.ubuntu.com|security.ubuntu.com/old-releases.ubuntu.com/g' /etc/apt/sources.list
```
gdzie ``XX.archive.ubuntu.com`` to XX odpowiada jak w polskiej wersji ``pl.archive.ubuntu.com`` a chcemy kompletnie zamienić na ``old-releases.ubuntu.com`` :)

### 2. kompilacja SNEK

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



