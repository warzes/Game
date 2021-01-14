#pragma once

struct WindowConfig
{
	int width = 1024;
	int height = 768;
};

class Window final
{
	friend class Engine;
public:
	bool Init(const WindowConfig& config);
	bool Broadcast();

	void ToggleFullScreen();

#if SE_PLATFORM_WINDOWS
	HWND GetHWND() { return m_hwnd; }
#endif

	bool hasWindowFocus = true; // TODO:
	bool isFullScreen = false;  // TODO:

private:
	Window() = default;
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	~Window();

	void close();
#if SE_PLATFORM_WINDOWS
	HWND m_hwnd = nullptr;
	HINSTANCE m_instance = nullptr;
#endif
	bool m_isInit = false;
};