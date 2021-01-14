#pragma once

#define LOAD_ENTRYPOINT(name, var, type)                       \
	if (!var)                                                  \
	{                                                          \
		var = reinterpret_cast<type>(wglGetProcAddress(name)); \
		assert(var != 0);                                      \
	}

#define ERROR_INVALID_VERSION_ARB               0x2095
#define WGL_CONTEXT_DEBUG_BIT_ARB               0x0001
#define WGL_CONTEXT_FLAGS_ARB                   0x2094
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  0x0002
#define WGL_CONTEXT_LAYER_PLANE_ARB             0x2093
#define WGL_CONTEXT_MAJOR_VERSION_ARB           0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           0x2092

const char* wglGetExtensionsStringARB(HDC hdc)
{
	typedef const char* (APIENTRY* PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
	static PFNWGLGETEXTENSIONSSTRINGARBPROC pfnGetExtensionsStringARB = 0;

	const char* pszExtStr = 0;
	HGLRC hCurrentContext = wglGetCurrentContext();
	if (!hCurrentContext)
	{
		if (!(hCurrentContext = wglCreateContext(hdc)))
			return 0;

		if (!wglMakeCurrent(hdc, hCurrentContext))
		{
			wglDeleteContext(hCurrentContext);
			return 0;
		}

		LOAD_ENTRYPOINT("wglGetExtensionsStringARB", pfnGetExtensionsStringARB, PFNWGLGETEXTENSIONSSTRINGARBPROC);

		if (pfnGetExtensionsStringARB)
			pszExtStr = pfnGetExtensionsStringARB(hdc);

		wglMakeCurrent(hdc, 0);
		wglDeleteContext(hCurrentContext);
	}
	else
	{
		if (!wglMakeCurrent(hdc, hCurrentContext))
			return 0;

		LOAD_ENTRYPOINT("wglGetExtensionsStringARB", pfnGetExtensionsStringARB, PFNWGLGETEXTENSIONSSTRINGARBPROC);

		if (pfnGetExtensionsStringARB)
			pszExtStr = pfnGetExtensionsStringARB(hdc);
	}

	return pszExtStr;
}

HGLRC wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int* attribList)
{
    typedef HGLRC(APIENTRY* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);
    static PFNWGLCREATECONTEXTATTRIBSARBPROC pfnCreateContextAttribsARB = 0;

    HGLRC hContext = 0;
    HGLRC hCurrentContext = wglGetCurrentContext();

    if (!hCurrentContext)
    {
        if (!(hCurrentContext = wglCreateContext(hDC)))
            return 0;

        if (!wglMakeCurrent(hDC, hCurrentContext))
        {
            wglDeleteContext(hCurrentContext);
            return 0;
        }

        LOAD_ENTRYPOINT("wglCreateContextAttribsARB", pfnCreateContextAttribsARB, PFNWGLCREATECONTEXTATTRIBSARBPROC);

        if (pfnCreateContextAttribsARB)
            hContext = pfnCreateContextAttribsARB(hDC, hShareContext, attribList);

        wglMakeCurrent(hDC, 0);
        wglDeleteContext(hCurrentContext);
    }
    else
    {
        if (!wglMakeCurrent(hDC, hCurrentContext))
            return 0;

        LOAD_ENTRYPOINT("wglCreateContextAttribsARB", pfnCreateContextAttribsARB, PFNWGLCREATECONTEXTATTRIBSARBPROC);

        if (pfnCreateContextAttribsARB)
            hContext = pfnCreateContextAttribsARB(hDC, hShareContext, attribList);
    }

    return hContext;
}