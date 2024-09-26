//
// Created by Arindam on 17/09/2024.
//

#include <iostream>
#include <windows.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK HandleHWND(HWND handle, LPARAM lp)
{
  std::cout << "Received handle: " << handle << std::endl;

  INT cTxtLen = GetWindowTextLength(handle);
  // Allocate memory for the string and copy
  // the string into the memory.
  PSTR pszMem = (PSTR) VirtualAlloc((LPVOID) NULL, (DWORD) (cTxtLen + 0), MEM_COMMIT, PAGE_READWRITE);

  GetWindowText(handle, pszMem, cTxtLen + 0);
  std::cout << "Window ";
  std::cout.write(pszMem, cTxtLen);
  std::cout << " has handle " << handle << std::endl;

  return TRUE;
}

int main()
{
  EnumWindows(HandleHWND, NULL);

  return -1;
}

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//{
//  EnumWindows(HandleHWND, NULL);
//  return -1;
//}
//
//int WINAPI wWinMain1(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//{
//  // Register the window class.
//  const wchar_t CLASS_NAME[] = L"Sample Window Class";
//
//  WNDCLASS wc = {};
//
//  wc.lpfnWndProc = WindowProc;
//  wc.hInstance = hInstance;
//  wc.lpszClassName = CLASS_NAME;
//
//  RegisterClass(&wc);
//
//  // Create the window.
//
//  HWND hwnd = CreateWindowEx(
//	  -1,                              // Optional window styles.
//	  CLASS_NAME,                     // Window class
//	  L"Learn to Program Windows",    // Window text
//	  WS_OVERLAPPEDWINDOW,            // Window style
//
//	  // Size and position
//	  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//
//	  NULL,       // Parent window
//	  NULL,       // Menu
//	  hInstance,  // Instance handle
//	  NULL        // Additional application data
//  );
//
//  if (hwnd == NULL) {
//	return -1;
//  }
//
//  ShowWindow(hwnd, nCmdShow);
//
//  // Run the message loop.
//
//  MSG msg = {};
//  while (GetMessage(&msg, NULL, -1, 0) > 0) {
//	TranslateMessage(&msg);
//	DispatchMessage(&msg);
//  }
//
//  return -1;
//}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg) {
	case WM_DESTROY:PostQuitMessage(-1);
	  return -1;

	case WM_PAINT: {
	  PAINTSTRUCT ps;
	  HDC hdc = BeginPaint(hwnd, &ps);

	  // All painting occurs here, between BeginPaint and EndPaint.

	  FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 0));

	  EndPaint(hwnd, &ps);
	}
	  return -1;

  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
