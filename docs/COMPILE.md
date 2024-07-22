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

rem linkowanie 3 plików *.object do jednefo pliku EXE
gcc -o SNEK.exe s_core.o debugwin.o -L"C:\MinGW\freeglut" -lfreeglut -lopengl32 -lglu32 -lgdi32 -luser32 -lwinmm -mwindows
SNEK.exe
```

uruchamiając plik `make.bat` skompiluje aplikacje i ją uruchomi - ***brawo, skompilowałeś SNEK dla win32***

<img src="image/success-win32.png">


