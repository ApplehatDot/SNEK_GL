#ifndef DEBUGWIN_H
#define DEBUGWIN_H

#include <windows.h>

void CreateDebugWindow(HINSTANCE hInstance, int nCmdShow);
void UpdateDebugWindow(float DotX, float DotY, float FoodX, float FoodY, int LiczbaSegmentow);

#endif // DEBUGWIN_H
