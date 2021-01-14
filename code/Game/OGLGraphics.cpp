#include "stdafx.h"
#include "OGLGraphics.h"
#include "Window.h"
#include "OGLFunc.h"

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
	if (!(m_hDC = GetDC(hwnd)))
		throw std::runtime_error("GetDC() failed.");

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags |= PFD_SUPPORT_COMPOSITION;

	int pf = ChoosePixelFormat(m_hDC, &pfd);

	if (!SetPixelFormat(m_hDC, pf, &pfd))
		throw std::runtime_error("SetPixelFormat() failed.");
	
	std::string extensions = wglGetExtensionsStringARB(m_hDC);
	if (extensions.find("WGL_ARB_create_context") == std::string::npos)
		throw std::runtime_error("Required extension WGL_ARB_create_context is not supported.");

	int attribList[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0, 0
	};

	if (!(m_hRC = wglCreateContextAttribsARB(m_hDC, 0, attribList)))
		throw std::runtime_error("wglCreateContextAttribsARB() failed for OpenGL 3 context.");

	if (!wglMakeCurrent(m_hDC, m_hRC))
		throw std::runtime_error("wglMakeCurrent() failed for OpenGL 3 context.");

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
	glClearColor(0.3f, 0.5f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OGLGraphics::EndFrame()
{
#if SE_PLATFORM_WINDOWS
	SwapBuffers(m_hDC);
#endif
}

void OGLGraphics::close()
{
	if (m_hDC)
	{
		if (m_hRC)
		{
			wglMakeCurrent(m_hDC, 0);
			wglDeleteContext(m_hRC);
			m_hRC = 0;
		}

		ReleaseDC(m_hwnd, m_hDC);
		m_hDC = 0;
	}

	m_isInit = false;
}