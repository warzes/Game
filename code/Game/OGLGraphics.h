#pragma once

#include "OGLFunc.h"
#include "Color.h"

struct GraphicsConfig
{
	int OpenGLMajorVersion = 4;
	int OpenGLMinorVersion = 6;

	Color ClearColor = { 0.129f*255.0f, 0.586f * 255.0f, 0.949f * 255.0f, 255.0f };
};

class OGLGraphics
{
	friend class Engine;
public:
#if SE_PLATFORM_WINDOWS
	bool Init(HWND hwnd, const GraphicsConfig& config);
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

	void close();

#if SE_PLATFORM_WINDOWS
	HDC m_deviceContext = nullptr;
	HGLRC m_renderContext = nullptr;
	HWND m_hwnd = nullptr;
#endif

	int m_openGLMajorVersion = 0;
	int m_openGLMinorVersion = 0;
	Color m_clearColor;

	// TODO:
	static const int BEST_ANTI_ALIASING_SAMPLES = -1;
	int m_antiAliasingSamples = 0;
	// TODO END

	bool m_isInit = false;
};