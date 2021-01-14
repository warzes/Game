#pragma once

class OGLWindowContext
{
public:
	void Init();
	void Close();

	HWND hndl = nullptr;
	HDC deviceContext = nullptr;
	HGLRC renderContext = nullptr;
};

inline void OGLWindowContext::Init()
{
	hndl = CreateWindow(WINDOWCLASS, L"Fake Window", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, nullptr, nullptr, nullptr, nullptr);
	if (!hndl)
	{
		throw std::runtime_error("CreateWindow() failed: Can not create fake window.");
	}

	deviceContext = GetDC(hndl);
	if (deviceContext)
	{
		int pixelFormat;
		PIXELFORMATDESCRIPTOR pixelFormatDesc;
		memset(&pixelFormatDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDesc.nVersion = 1;
		pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
		pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits = 32;
		pixelFormatDesc.cAlphaBits = 8;
		pixelFormatDesc.cDepthBits = 24;
		pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDesc);
		if (pixelFormat)
		{
			if (SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDesc))
			{
				renderContext = wglCreateContext(deviceContext);
				if (!renderContext)
				{
					throw std::runtime_error("wglCreateContext() failed: Can not create fake render context.");
				}
			}
			else
			{
				throw std::runtime_error("SetPixelFormat() failed: Can not create fake render context.");
			}
		}
		else
		{
			throw std::runtime_error("ChoosePixelFormat() failed: Can not create fake render context.");
		}
	}
	else
	{
		throw std::runtime_error("GetDC() failed: Can not create fake device context.");
	}
}

inline void OGLWindowContext::Close()
{
	wglMakeCurrent(deviceContext, NULL);
	wglDeleteContext(renderContext);
	ReleaseDC(hndl, deviceContext);
	DestroyWindow(hndl);
	renderContext = nullptr;
	deviceContext = nullptr;
	hndl = nullptr;

	// очистка событий
	// TODO: переделать
	MSG msg;
	while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_DESTROY)
			PostQuitMessage(0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}