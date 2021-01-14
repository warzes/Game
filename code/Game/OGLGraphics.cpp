#include "stdafx.h"
#include "OGLGraphics.h"
#include "Window.h"
#include "OGLWindowContext.h"

OGLGraphics::~OGLGraphics()
{
	if (m_isInit)
		close();
}

#if SE_PLATFORM_WINDOWS
bool OGLGraphics::Init(HWND hwnd, const WindowConfig& window, const GraphicsConfig& config)
#endif
{
#if SE_PLATFORM_WINDOWS
	m_hwnd = hwnd;

	OGLWindowContext tempContext;

	tempContext.Init();

	if (!(m_deviceContext = GetDC(hwnd)))
		throw std::runtime_error("GetDC() failed: Can not create context.");

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

	wglMakeCurrent(tempContext.deviceContext, tempContext.renderContext);

	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
	if (!wglChoosePixelFormatARB)
		throw std::runtime_error("wglGetProcAddress() failed: Can not find wglChoosePixelFormatARB.");
	
	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	if (!wglCreateContextAttribsARB)
		throw std::runtime_error("wglGetProcAddress() failed: Can not find wglCreateContextAttribsARB.");

	const int pixelAttribs[] = 
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		/* WGL_SWAP_EXCHANGE_ARB causes problems with window menu in fullscreen */
		WGL_SWAP_METHOD_ARB, WGL_SWAP_COPY_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		0
	};

	int contextAttributes[] = 
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 4,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	int pixelFormat;
	UINT numFormats;
	BOOL status = wglChoosePixelFormatARB(m_deviceContext, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats);
	if (status && numFormats)
	{
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		DescribePixelFormat(m_deviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		if (SetPixelFormat(m_deviceContext, pixelFormat, &pfd))
		{
			m_renderContext = wglCreateContextAttribsARB(m_deviceContext, 0, contextAttributes);
			if (!m_renderContext)
			{
				throw std::runtime_error("wglCreateContextAttribsARB() failed: Can not create context.");
			}
		}
		else
		{
			throw std::runtime_error("SetPixelFormat() failed: Can not create context.");
		}
	}
	else
	{
		throw std::runtime_error("GetDC() failed: Can not create context.");
	}

	tempContext.Close();

	if (!wglMakeCurrent(m_deviceContext, m_renderContext))
		throw std::runtime_error("wglMakeCurrent() failed for OpenGL 3 context.");

	LoadGLExtensions();

	const char* pszGLVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	std::ostringstream text;
	text << "GL_VERSION: " << pszGLVersion;

	SetWindowTextA(hwnd, text.str().c_str()); // TODO: del
#endif
	m_isInit = true;
	return true;
}

void OGLGraphics::BeginFrame()
{
	glViewport(0, 0, 1024, 768);
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