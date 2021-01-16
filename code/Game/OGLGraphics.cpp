#include "stdafx.h"
#include "OGLGraphics.h"
#include "Window.h"
#include "WGLFunc.h"
#include "Engine.h"

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_3_0[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	0
};

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_3_1[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 1,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	0
};

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_3_2[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 2,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_3_3[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 3,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_4_0[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_4_1[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 1,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int OGLGraphics::ATTRIB_LIST_GL_VERSION_4_2[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 2,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int* const OGLGraphics::ATTRIB_LISTS[] =
{
	OGLGraphics::ATTRIB_LIST_GL_VERSION_3_0,
	OGLGraphics::ATTRIB_LIST_GL_VERSION_3_1,
	OGLGraphics::ATTRIB_LIST_GL_VERSION_3_2,
	OGLGraphics::ATTRIB_LIST_GL_VERSION_3_3,
	OGLGraphics::ATTRIB_LIST_GL_VERSION_4_0,
	OGLGraphics::ATTRIB_LIST_GL_VERSION_4_1,
	OGLGraphics::ATTRIB_LIST_GL_VERSION_4_2
};

OGLGraphics::~OGLGraphics()
{
	if (m_isInit)
		close();
}

#if SE_PLATFORM_WINDOWS
bool OGLGraphics::Init(HWND hwnd, const GraphicsConfig& config)
#endif
{
#if SE_PLATFORM_WINDOWS
	m_hwnd = hwnd;

	if (!(m_deviceContext = GetDC(hwnd)))
		throw std::runtime_error("GetDC() failed: Can not create context.");

	// Create and set a pixel format for the window.

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pf = 0;
	if (m_antiAliasingSamples == 0)
		pf = ChoosePixelFormat(m_deviceContext, &pfd);
	else if (m_antiAliasingSamples == BEST_ANTI_ALIASING_SAMPLES)
		gl::ChooseBestAntiAliasingPixelFormat(pf);
	else
		gl::ChooseAntiAliasingPixelFormat(pf, m_antiAliasingSamples);

	if (!pf)
		pf = ChoosePixelFormat(m_deviceContext, &pfd);

	if (!SetPixelFormat(m_deviceContext, pf, &pfd))
		throw std::runtime_error("SetPixelFormat() failed.");

	pfd.dwFlags |= PFD_SUPPORT_COMPOSITION;

	// Verify that this OpenGL implementation supports the required extensions.
	if (!gl::ExtensionSupported("WGL_ARB_create_context"))
		throw std::runtime_error("Required extension WGL_ARB_create_context is not supported.");

	if (m_preferredGLVersion == GL_VERSION_UNKNOWN)
		m_preferredGLVersion = static_cast<GLVersion>((sizeof(ATTRIB_LISTS) / sizeof(ATTRIB_LISTS[0])) - 1);

	for (int i = m_preferredGLVersion; i >= 0; --i)
	{
		m_renderContext = wglCreateContextAttribsARB(m_deviceContext, 0, ATTRIB_LISTS[i]);
		if (m_renderContext)
		{
			m_actualGLVersion = static_cast<GLVersion>(i);
			break;
		}
	}

	if (!m_renderContext)
	{
		m_actualGLVersion = GL_VERSION_UNKNOWN;
		throw std::runtime_error("wglCreateContextAttribsARB() failed.");
	}

	if (!wglMakeCurrent(m_deviceContext, m_renderContext))
		throw std::runtime_error("wglMakeCurrent() failed.");

#endif

	int major = 0;
	int minor = 0;
	gl::GetGLVersion(major, minor);
	std::ostringstream title;
	title << "OpenGL " << major << "." << minor;
	SetWindowTextA(hwnd, title.str().c_str());

	m_isInit = true;
	return true;
}

void OGLGraphics::BeginFrame()
{
	static Engine& engine = GetEngine();

	glViewport(0, 0, engine.GetConfig().window.width, engine.GetConfig().window.height);
	glClearColor(0.129f, 0.586f, 0.949f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OGLGraphics::EndFrame()
{
#if SE_PLATFORM_WINDOWS
	SwapBuffers(m_deviceContext);
#endif
}

void OGLGraphics::SetVsync()
{
	// TODO:
	if (wglSwapIntervalEXT)
		wglSwapIntervalEXT(1);
}

void OGLGraphics::close()
{
	if (m_deviceContext)
	{
		if (m_renderContext)
		{
			wglMakeCurrent(m_deviceContext, 0);
			wglDeleteContext(m_renderContext);
			m_renderContext = 0;
		}

		ReleaseDC(m_hwnd, m_deviceContext);
		m_deviceContext = 0;
	}

	m_isInit = false;
}