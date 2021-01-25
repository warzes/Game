#pragma once

/* класс-утилита кеширующий состояния OpenGL*/

class OGLCasheBinder
{
public:
	// retrieves a single instance of this object
	static OGLCasheBinder& Get()
	{
		if (!m_instance)
			m_instance = new OGLCasheBinder;
		return *m_instance;
	}

	void glUseProgram(GLuint program);

private:
	static OGLCasheBinder *m_instance; // the specific singleton instance of the class

	GLuint m_shaderProgram = 0;
};