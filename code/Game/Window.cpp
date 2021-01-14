#include "stdafx.h"
#include "Window.h"
#include "Engine.h"

static Window* thisWindow = nullptr;

#if SE_PLATFORM_WINDOWS
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	Engine& engine = GetEngine();

	switch (msg)
	{
	case WM_ACTIVATE:
		switch (wparam)
		{
		default:
			break;

		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			thisWindow->hasWindowFocus = true;
			break;

		case WA_INACTIVE:
			if (thisWindow->isFullScreen)
				ShowWindow(hwnd, SW_MINIMIZE);
			thisWindow->hasWindowFocus = false;
			break;
		}
		break;
	case WM_SIZE:
		engine.GetConfig().window.width = static_cast<int>(LOWORD(lparam));
		engine.GetConfig().window.height = static_cast<int>(HIWORD(lparam));
		break;

	case WM_SYSKEYDOWN:
		if (wparam == VK_RETURN)
			thisWindow->ToggleFullScreen();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
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
	thisWindow = this;

#if SE_PLATFORM_WINDOWS
	m_instance = GetModuleHandle(0);

	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;	
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = m_instance;
	wc.lpszClassName = WINDOWCLASS;
	wc.lpszMenuName = L"";
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	DWORD wndExStyle = WS_EX_OVERLAPPEDWINDOW;
	DWORD wndStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	// TODO: по центру экрана

	m_hwnd = ::CreateWindowEx(wndExStyle, WINDOWCLASS, L"Game", wndStyle, CW_USEDEFAULT, CW_USEDEFAULT, config.width, config.height, 0, 0, m_instance, 0);
	if (!m_hwnd)
		return false;


	RECT rc = { 0 };
	GetClientRect(m_hwnd, &rc);
	GetEngine().GetConfig().window.width = rc.right - rc.left;
	GetEngine().GetConfig().window.height = rc.bottom - rc.top;

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
	while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#endif
	return true;
}

void Window::ToggleFullScreen()
{
	static DWORD savedExStyle;
	static DWORD savedStyle;
	static RECT rcSaved;

	Engine& engine = GetEngine();

	isFullScreen = !isFullScreen;

	if (isFullScreen)
	{
		// Moving to full screen mode.

		savedExStyle = GetWindowLong(m_hwnd, GWL_EXSTYLE);
		savedStyle = GetWindowLong(m_hwnd, GWL_STYLE);
		GetWindowRect(m_hwnd, &rcSaved);

		SetWindowLong(m_hwnd, GWL_EXSTYLE, 0);
		SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
		SetWindowPos(m_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

		engine.GetConfig().window.width = GetSystemMetrics(SM_CXSCREEN);
		engine.GetConfig().window.height = GetSystemMetrics(SM_CYSCREEN);

		SetWindowPos(m_hwnd, HWND_TOPMOST, 0, 0, engine.GetConfig().window.width, engine.GetConfig().window.height, SWP_SHOWWINDOW);
	}
	else
	{
		// Moving back to windowed mode.

		SetWindowLong(m_hwnd, GWL_EXSTYLE, savedExStyle);
		SetWindowLong(m_hwnd, GWL_STYLE, savedStyle);
		SetWindowPos(m_hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

		engine.GetConfig().window.width = rcSaved.right - rcSaved.left;
		engine.GetConfig().window.height = rcSaved.bottom - rcSaved.top;

		SetWindowPos(m_hwnd, HWND_NOTOPMOST, rcSaved.left, rcSaved.top, engine.GetConfig().window.width, engine.GetConfig().window.height, SWP_SHOWWINDOW);
	}
}

void Window::close()
{
#if SE_PLATFORM_WINDOWS
	DestroyWindow(m_hwnd);
	UnregisterClass(WINDOWCLASS, m_instance);
#endif
	m_isInit = false;
}