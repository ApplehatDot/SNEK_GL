#include <windows.h>
#include "resource.h"

//definicje

#define wWidth 500
#define wHeight 390
#define IDC_MYBUTTON 1

HBITMAP hBanner;
HFONT hFont;
HWND Banner, hText, hButton, hLicense;
LPCWSTR ImagePath = L"assets\\hBanner\\Banner.bmp";

extern "C" __declspec(dllexport) void ShowAboutDialog(HINSTANCE hInstance, HWND hwndParent);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddControl(HWND);
//koniec definicji

extern "C" __declspec(dllexport) void ShowAboutDialog(HINSTANCE hInstance, HWND hwndParent){
	const char CLASS_NAME[] = L"WndAboutDialog";
	
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	
	RegisterClass(&wc);
	
	HWND hwnd = CreateWindowEx(
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

	// ustaw ikone
	if (hwnd != NULL) {
		HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
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

		case WM_COMMAND:
			//if MessageBox returns IDOK, close the AboutDialog.
			if(wParam == IDOK){	DestroyWindow(hwnd);	}
			break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

void AddControl(HWND hwnd){
	Banner = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 0, 0, hwnd, NULL, NULL, NULL);
	
	hBanner = (HBITMAP)LoadImageW(NULL, ImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(hBanner == NULL){
		MessageBoxW(hwnd, L"bitmap missing error [extension - hBanner == NULL]", L"error loading bitmap", MB_OK | MB_ICONERROR);
		return;
	}
	
	SendMessageW(Banner, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBanner);
	
	hText = CreateWindowExW(
		0,
		L"EDIT", 
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		40, 110, 
		400, 80, 
		hwnd, NULL, NULL, NULL);
	
	SetWindowTextW(
		hText,
		L"			About SNEK\r\n SNEK v1.0.0.5-insiders for win32\r\n Created by Applehat (Github = ApplehatDoesStuff)\r\n\r\n 	Packet Translations were provided by [discord usernames]:\r\n lemoncvm - Lithuanian\r\n tbifo_official - Czech\r\n alokation - French\r\n applehat. - Polish, English (US)\r\n\r\n SNEK_GL and its copies are distributed under MIT License (which its copy is shown under)"
		);
		
	hLicense = CreateWindowExW(
		0,
		L"EDIT", 
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		40, 210, 
		400, 80, 
		hwnd, NULL, NULL, NULL);
		
	SetWindowTextW(
		hLicense,
		L"			MIT License\r\n\r\n Copyright (c) 2025 ApplehatDoesStuff\r\n Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ''Software''), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\r\n\r\n The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\r\n\r\n THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."
		);

	// Pobierz systemowy font	
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	
	SendMessageW(hText, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessageW(hLicense, WM_SETFONT, (WPARAM)hFont, TRUE);
		
	hButton = CreateWindowExW(
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
	
	SendMessageW(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);

}
