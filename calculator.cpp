#include <windows.h>
#include <stdio.h>

HWND hNum1, hNum2, hAdd, hSub, hMul, hDiv;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    char buffer[256];
    double num1, num2, result;
    switch (Message) {
        case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD, 20, 10, 200, 20, hwnd, NULL, NULL, NULL);
            hNum1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 20, 40, 200, 20, hwnd, (HMENU)5, NULL, NULL);
            hNum2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP , 20, 70, 200, 20, hwnd, (HMENU)6, NULL, NULL);
            hAdd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_TABSTOP, 20, 100, 40, 40, hwnd, (HMENU)1, NULL, NULL);
            hSub = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_TABSTOP, 70, 100, 40, 40, hwnd, (HMENU)2, NULL, NULL);
            hMul = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_TABSTOP, 120, 100, 40, 40, hwnd, (HMENU)3, NULL, NULL);
            hDiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_TABSTOP, 170, 100, 40, 40, hwnd, (HMENU)4, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 1 || LOWORD(wParam) == 2 || LOWORD(wParam) == 3 || LOWORD(wParam) == 4) {
                GetWindowText(hNum1, buffer, 256);
                num1 = atof(buffer);
                GetWindowText(hNum2, buffer, 256);
                num2 = atof(buffer);
                switch (LOWORD(wParam)) {
                    case 1: result = num1 + num2; break;
                    case 2: result = num1 - num2; break;
                    case 3: result = num1 * num2; break;
                    case 4: result = (num2 != 0) ? num1 / num2 : 0; break;
                }
                sprintf(buffer, "%.2f", result);
                MessageBox(hwnd, buffer, "Result", MB_OK);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, LoadCursor(NULL, IDC_ARROW), 
                       (HBRUSH)COLOR_WINDOW + 1, NULL, "MyCalculator", NULL };
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindowEx(0, "MyCalculator", "My Calculator", WS_OVERLAPPED | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);
    if (!hwnd) return 0;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}