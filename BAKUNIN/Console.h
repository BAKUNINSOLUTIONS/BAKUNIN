#pragma once
#include <iostream>
#include <windows.h>

inline std::ostream& blue(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
        | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& red(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& green(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& yellow(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}

struct color {
    color(WORD attribute) :m_color(attribute) {};
    WORD m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>&
operator<<(std::basic_ostream<_Elem, _Traits>& i, color& c)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, c.m_color);
    return i;
}

void Type(const char* p, int Speed) {
    if (NULL == p)
        return;

    while (*p) {
        printf("%c\xDB", *p++);
        ::Sleep(Speed);
        printf("\b \b");
        ::Sleep(Speed);
    }
    ::Sleep(Speed * 10);
}

void SetConsole(bool showFlag) {
    SetConsoleTitle(L"RM Pro ~ F E E L   E N E R G Y ");
    int horizontal = 0, vertical = 0;
    int x = 530, y = 400; //Change the window size

    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 22;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    HWND hwnd = GetConsoleWindow();
    MoveWindow(hwnd, 0, 0, x, y, TRUE);
    SetWindowPos(hwnd, HWND_TOPMOST, 10, 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
    lStyle &= ~(WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(hwnd, GWL_STYLE, lStyle);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(console, &csbi);
    COORD scrollbar = {
        csbi.srWindow.Right - csbi.srWindow.Left + 1,
        csbi.srWindow.Bottom - csbi.srWindow.Top + 1
    };
    if (console == 0)
        throw 0;
    else
        SetConsoleScreenBufferSize(console, scrollbar);
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, (255 * 96) / 100, LWA_ALPHA); //Setting the background transparency
}


void TransparentWindow() {
    LONG lRet;
    HWND hWnd = GetConsoleWindow();
    lRet = SetWindowLong(hWnd, GWL_EXSTYLE,
        GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | BS_FLAT);
    lRet = SetLayeredWindowAttributes(hWnd, 0, 0, LWA_ALPHA);
    ITaskbarList* pTaskList = NULL;
    HRESULT initRet = CoInitialize(NULL);
    HRESULT createRet = CoCreateInstance(CLSID_TaskbarList,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_ITaskbarList,
        (LPVOID*)&pTaskList);
    if (createRet == S_OK)
    {
        pTaskList->DeleteTab(GetConsoleWindow());
        pTaskList->Release();
    }
    CoUninitialize();
}