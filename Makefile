all:
	g++ -shared -o release/AboutDialog.dll source/win32/AboutDiag.cpp -lgdi32 
	gcc -c -o obj/ReadPackets.o source/win32/ReadPackets.c 

	windres source/win32/snek.rc -O coff -o obj/snek.res
	gcc -c -o obj/s_core.o source/win32/core.c 

	gcc -o release/SNEK.exe obj/s_core.o obj/snek.res obj/ReadPackets.o -lfreeglut -lopengl32 -lglu32 -mwindows
