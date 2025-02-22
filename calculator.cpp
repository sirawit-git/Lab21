#if defined(UNICODE) && !defined(_UNICODE)

    #define _UNICODE

#elif defined(_UNICODE) && !defined(UNICODE)

    #define UNICODE

#endif



#include <tchar.h>

#include <windows.h>

#include <stdio.h>



LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);



HWND TextBox1, TextBox2;

HWND button_plus, button_mi, button_time, button_divi;



TCHAR szClassName[] = _T("CodeBlocksWindowsApp");



int WINAPI WinMain(HINSTANCE hThisInstance,

                   HINSTANCE hPrevInstance,

                   LPSTR lpszArgument,

                   int nCmdShow)

{

    HWND hwnd;

    MSG messages;

    WNDCLASSEX wincl;



    wincl.hInstance = hThisInstance;

    wincl.lpszClassName = szClassName;

    wincl.lpfnWndProc = WindowProcedure;

    wincl.style = CS_DBLCLKS;

    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);

    wincl.lpszMenuName = NULL;

    wincl.cbClsExtra = 0;

    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;



    if (!RegisterClassEx(&wincl))

        return 0;



    hwnd = CreateWindowEx(

        0,

        szClassName,

        _T("My Calculator"),

        WS_MINIMIZE | WS_SYSMENU,

        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,

        HWND_DESKTOP, NULL, hThisInstance, NULL);



    ShowWindow(hwnd, nCmdShow);



    while (GetMessage(&messages, NULL, 0, 0))

    {

        TranslateMessage(&messages);

        DispatchMessage(&messages);

    }



    return messages.wParam;

}



LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{

    switch (message)

    {

    case WM_ERASEBKGND:

    {

        HDC hdc = (HDC)wParam;

        RECT rc;

        GetClientRect(hwnd, &rc);

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 51, 255));

        FillRect(hdc, &rc, hBrush);

        DeleteObject(hBrush);

        return 1;

    }



    case WM_CREATE:

        CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD,

                     20, 20, 200, 25, hwnd, NULL, NULL, NULL);



        TextBox1 = CreateWindow("EDIT", "", WS_BORDER | WS_VISIBLE | WS_CHILD,

                                20, 50, 200, 25, hwnd, (HMENU)101, NULL, NULL);

        TextBox2 = CreateWindow("EDIT", "", WS_BORDER | WS_VISIBLE | WS_CHILD,

                                20, 80, 200, 25, hwnd, (HMENU)102, NULL, NULL);



        button_plus = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER,

                                   30, 120, 30, 30, hwnd, (HMENU)1, NULL, NULL);

        button_mi = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER,

                                 70, 120, 30, 30, hwnd, (HMENU)2, NULL, NULL);

        button_time = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER,

                                   110, 120, 30, 30, hwnd, (HMENU)3, NULL, NULL);

        button_divi = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER,

                                   150, 120, 30, 30, hwnd, (HMENU)4, NULL, NULL);

        break;



    case WM_COMMAND:

        if (HIWORD(wParam) == BN_CLICKED)

        {

            char num1[10], num2[10];

            GetWindowText(TextBox1, num1, 10);

            GetWindowText(TextBox2, num2, 10);



            long double val1 = strtold(num1,NULL);

            long double val2 = strtold(num2,NULL);

            long double result = 0;

            char resText[100];



            switch (LOWORD(wParam))

            {

            case 1:

                result = val1 + val2;

                break;

            case 2:

                result = val1 - val2;

                break;

            case 3:

                result = val1 * val2;

                break;

            case 4:

                result = val1 / val2;

                break;

            }



            snprintf(resText, sizeof(resText), "%.7Lf", result);

            MessageBox(hwnd, resText, "Result", MB_OK );

        }

        break;



    case WM_DESTROY:

        PostQuitMessage(0);

        break;



    default:

        return DefWindowProc(hwnd, message, wParam, lParam);

    }



    return 0;

}