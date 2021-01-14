#pragma once

struct WindowConfig
{

};

class Window final
{
	friend class Engine;
public:
	bool Init(const WindowConfig& config);
	bool Broadcast();
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
#endif
	bool m_isInit = false;
};