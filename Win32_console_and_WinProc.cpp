#include <Windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
HINSTANCE hinst;
HWND hwndMain;

void CallConcoleOutput(void)
{
    int hCrt;
    FILE *hf;
    AllocConsole();
    hCrt = _open_osfhandle((intptr_t)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    hf = _fdopen(hCrt, "w");
    *stdout = *hf;
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("InitConsoleWindow OK!\n");
}

LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        // Initialize the window.
        printf("creat\n");
        return 0;

    case WM_PAINT:
        // printf("paint");
        // Paint the window's client area.
        return 0;

    case WM_SIZE:
        printf("size\n");
        // Set the size and position of the window.
        return 0;

    case WM_DESTROY:
        printf("destroy\n");
        // Clean up window-specific data objects.
        return 0;

        //
        // Process other messages.
        //

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpszCmdLine, int nCmdShow)
{
    MSG msg;
    BOOL bRet;
    WNDCLASSA wc;
    UNREFERENCED_PARAMETER(lpszCmdLine);

    // Register the window class for the main window.
    CallConcoleOutput();
    if (!hPrevInstance)
    {
        wc.style = 0;
        wc.lpfnWndProc = (WNDPROC)WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon((HINSTANCE)NULL,
                            IDI_APPLICATION);
        wc.hCursor = LoadCursor((HINSTANCE)NULL,
                                IDC_ARROW);
        // wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.lpszMenuName = "MainMenu";
        wc.lpszClassName = "MainWndClass";

        if (!RegisterClassA(&wc))
            return FALSE;
    }

    hinst = hInstance; // save instance handle

    // Create the main window.

    hwndMain = CreateWindowW(L"MainWndClass", L"哈哈哈",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL,
                             (HMENU)NULL, hinst, (LPVOID)NULL);

    // If the main window cannot be created, terminate
    // the application.

    if (!hwndMain)
        return FALSE;

    // Show the window and paint its contents.

    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);

    // Start the message loop.

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Return the exit code to the system.

    return msg.wParam;
}