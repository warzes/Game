#pragma once

#include "OGLFunc.h"

struct GraphicsConfig
{
};

class OGLGraphics
{
	friend class Engine;
public:
	enum GLVersion
	{
		GL_VERSION_3_0 = 0,
		GL_VERSION_3_1 = 1,
		GL_VERSION_3_2 = 2,
		GL_VERSION_3_3 = 3,
		GL_VERSION_4_0 = 4,
		GL_VERSION_4_1 = 5,
		GL_VERSION_4_2 = 6,
		GL_VERSION_UNKNOWN = 65536
	};

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

	static const int ATTRIB_LIST_GL_VERSION_3_0[];
	static const int ATTRIB_LIST_GL_VERSION_3_1[];
	static const int ATTRIB_LIST_GL_VERSION_3_2[];
	static const int ATTRIB_LIST_GL_VERSION_3_3[];
	static const int ATTRIB_LIST_GL_VERSION_4_0[];
	static const int ATTRIB_LIST_GL_VERSION_4_1[];
	static const int ATTRIB_LIST_GL_VERSION_4_2[];
	static const int* const ATTRIB_LISTS[];

#if SE_PLATFORM_WINDOWS
	HDC m_deviceContext = nullptr;
	HGLRC m_renderContext = nullptr;
	HWND m_hwnd = nullptr;
#endif

	// TODO:
	static const int BEST_ANTI_ALIASING_SAMPLES = -1;
	int m_antiAliasingSamples = 0;
	GLVersion m_preferredGLVersion = GL_VERSION_UNKNOWN;
	GLVersion m_actualGLVersion = GL_VERSION_UNKNOWN;
	// TODO END

	bool m_isInit = false;
};