#ifndef ABOUT_H
#define ABOUT_H

#include <windows.h>

// Deklaracja callback dla okna dialogowego
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

// Funkcja do wyświetlania okna "About" z przekazanym tekstem
void ShowAboutDialog(const char* text);

#endif // ABOUT_H
