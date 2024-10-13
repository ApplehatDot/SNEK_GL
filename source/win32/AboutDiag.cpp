#include <windows.h>

//definicje

#define wWidth 500
#define wHeight 390
#define PACKET_SUCCESS 0
#define IDC_MYBUTTON 1

HBITMAP hBanner;
HWND Banner;

extern "C" __declspec(dllexport) void ShowAboutDialog(HINSTANCE hInstance, HWND hwndParent);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddControl(HWND);


//koniec definicji

extern "C" __declspec(dllexport) void ShowAboutDialog(HINSTANCE hInstance, HWND hwndParent){
	const wchar_t CLASS_NAME[] = L"WndAboutDialog";
	
	WNDCLASSW wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	RegisterClassW(&wc);
	
	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"About",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wWidth, wHeight,
		hwndParent,
		NULL,
		hInstance,
		NULL);
		
	if (hwnd == NULL) {
        return;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg){
		case WM_CREATE:{
			AddControl(hwnd);
			break;
		}
		
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

void AddControl(HWND hwnd){
	Banner = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 0, 0, hwnd, NULL, NULL, NULL);
	
	hBanner = (HBITMAP)LoadImageW(NULL, L"assets\\hBanner\\Banner.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(hBanner == NULL){
		MessageBoxW(hwnd, L"bitmap missing error [extension - hBanner == NULL]", L"error loading bitmap", MB_OK | MB_ICONERROR);
		return;
	}
	
	SendMessageW(Banner, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBanner);
	
	CreateWindowW(
		L"static", 
		L"   About SNEK\n\n   Development enviroment\n   v1.0.0.2-dev (kopia programisty)\n\n   Stworzone przez Applehat (ApplehatDoesStuff)\n\n   SNEK_GL Project is distributed under MIT License.\n\n   Copyright (C) 2024 ApplehatDoesStuff\n",
		WS_VISIBLE | WS_CHILD | SS_LEFT, 33, 110, 400, 180, hwnd, NULL, NULL, NULL);
		
	CreateWindowExW(
                0,                          // Dodatkowe style
                L"BUTTON",                  // Klasa przycisku
                L"OK",                       // Tekst przycisku 
                WS_CHILD | WS_VISIBLE, // Style okna i przycisku
                150, 300, 100, 25,            // Pozycja i wymiary przycisku
                hwnd,                       // Rodzic (główne okno)
                (HMENU)IDC_MYBUTTON,        // Identyfikator przycisku
                NULL, // Uchwyt instancji
                NULL                        // Dodatkowe parametry
            );

}
