#include "stdafx.h"
#include "Window.h"

#if SE_PLATFORM_WINDOWS
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return ::DefWindowProc(hwnd, msg, wparam, lparam);
}
#endif

#define WINDOWCLASS L"SapphireWindowClass"

Window::~Window()
{
	if (m_isInit)
		close();
}

bool Window::Init(const WindowConfig& config)
{
#if SE_PLATFORM_WINDOWS
	WNDCLASSEX wc = {};
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = WINDOWCLASS;
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WINDOWCLASS, L"Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);
	if (!m_hwnd)
		return false;

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);
#endif
	m_isInit = true;
	return true;
}

bool Window::Broadcast()
{
#if SE_PLATFORM_WINDOWS
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#endif
	return true;
}

void Window::close()
{
#if SE_PLATFORM_WINDOWS
	DestroyWindow(m_hwnd);
#endif
	m_isInit = false;
}