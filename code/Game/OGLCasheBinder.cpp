#include "stdafx.h"
#include "OGLCasheBinder.h"

//-----------------------------------------------------------------------------
OGLCasheBinder *OGLCasheBinder::m_instance = nullptr;
//-----------------------------------------------------------------------------
void OGLCasheBinder::glUseProgram(GLuint program)
{
#if SE_OGL_CASHE_BINDER
	if (m_shaderProgram != program)
#endif
	{
		m_shaderProgram = program;
		glUseProgram(m_shaderProgram);
	}
}
//-----------------------------------------------------------------------------