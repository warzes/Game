#pragma once

#include "OGLFunc.h"

struct WindowConfig;

struct GraphicsConfig
{

};

class OGLGraphics
{
	friend class Engine;
public:
#if SE_PLATFORM_WINDOWS
	bool Init(HWND hwnd, const WindowConfig &window, const GraphicsConfig& config);
#endif

	void BeginFrame();
	void EndFrame();

	void SetVsync();

private:
	OGLGraphics() = default;
	OGLGraphics(const OGLGraphics&) = delete;
	OGLGraphics(OGLGraphics&&) = delete;
	OGLGraphics& operator=(const OGLGraphics&) = delete;
	OGLGraphics& operator=(OGLGraphics&&) = delete;
	~OGLGraphics();

	void initOpenGLFunctions();

	void close();

#if SE_PLATFORM_WINDOWS
	HDC m_deviceContext = nullptr;
	HGLRC m_renderContext = nullptr;
	HWND m_hwnd = nullptr;
#endif

	bool m_isInit = false;
};