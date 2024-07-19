#include "about.h"

// Callback dla okna dialogowego "About"
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_INITDIALOG:
            // Ustawienie tekstu okna dialogowego
            SetDlgItemText(hwnd, IDC_ABOUT_TEXT, (LPCTSTR)lParam);
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case IDOK:
                case IDCANCEL:
                    EndDialog(hwnd, 0);
                    return TRUE;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

// Funkcja do wyświetlania okna "About"
void ShowAboutDialog(const char* text) {
    // Utworzenie okna dialogowego modalnego
    DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), NULL, AboutDlgProc, (LPARAM)text);
}
