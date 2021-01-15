#include "stdafx.h"
#include "Engine.h"
#include "Input.h"

#if SE_COMPILER_MSVC
#   pragma comment(lib, "OpenGL32.lib")
#	pragma comment (lib, "gdiplus.lib")
#endif

struct 
{
	const char* vertex, *fragment;
	GLuint vertexId, fragmentId;
} shader = { 
	"#version 130\n\nin vec3 positionIn;\nin vec4 colorIn;\nout vec4 fragementColor;\n\nuniform mat4 projection = mat4(1.0);\nuniform mat4 model = mat4(1.0);\n\nvoid main() {\n\tgl_Position = projection * model * vec4(positionIn, 1.0f);\n\tfragementColor = colorIn;\n}", 

	"#version 130\n\nin vec4 fragementColor;\nout vec4 color;\n\nvoid main() {\n\tcolor = fragementColor;\n}", 
	0, 
	0 
};

struct 
{
	GLuint id, vbo, vao;
} program = { 0, 0, 0 };

void checkShader(GLuint shaderId)
{
	GLint result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == FALSE)
	{
		GLsizei length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			GLchar* infoLog = new GLchar[length];
			WCHAR* msg = new WCHAR[length];
			glGetShaderInfoLog(shaderId, length, &length, infoLog);
			MultiByteToWideChar(CP_ACP, 0, infoLog, -1, (LPWSTR)msg, length + 1);
#if SE_PLATFORM_WINDOWS
			MessageBox(0, msg, L"Error", MB_ICONERROR);
#endif
			delete[] infoLog;
			throw std::runtime_error("Shader Error");			
		}
		else if (shader.vertexId == shaderId)
			throw std::runtime_error("glCompileShader failed: Can not compile vertex shader.");
		else
			throw std::runtime_error("glCompileShader failed: Can not compile fragmet shader.");
	}
}

void initShader()
{
	shader.vertexId = glCreateShader(GL_VERTEX_SHADER);
	shader.fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader.vertexId, 1, &shader.vertex, NULL);
	glShaderSource(shader.fragmentId, 1, &shader.fragment, NULL);

	glCompileShader(shader.vertexId);
	glCompileShader(shader.fragmentId);

	checkShader(shader.vertexId);
	checkShader(shader.fragmentId);
}

void checkProgram(GLuint shaderId, GLenum param)
{
	GLint result;
	glGetProgramiv(shaderId, param, &result);
	if (result == FALSE)
	{
		GLsizei length;
		glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			GLchar* infoLog = new GLchar[length];
			WCHAR* msg = new WCHAR[length];
			glGetProgramInfoLog(shaderId, length, &length, infoLog);
			MultiByteToWideChar(CP_ACP, 0, infoLog, -1, (LPWSTR)msg, length + 1);
#if SE_PLATFORM_WINDOWS
			MessageBox(0, msg, L"Error", MB_ICONERROR);
#endif
			delete[] infoLog;
			throw std::runtime_error("Program Error");			
		}
		else if (param == GL_LINK_STATUS)
			throw std::runtime_error("glLinkProgram failed: Can not link program.");
		else
			throw std::runtime_error("glValidateProgram() failed: Can not execute shader program.");
	}
}

void initProgram()
{
	program.id = glCreateProgram();
	glAttachShader(program.id, shader.vertexId);
	glAttachShader(program.id, shader.fragmentId);
	glLinkProgram(program.id);
	checkProgram(program.id, GL_LINK_STATUS);
	glValidateProgram(program.id);
	checkProgram(program.id, GL_VALIDATE_STATUS);
}

void initVertexObjects()
{
	GLint positionLocation = glGetAttribLocation(program.id, "positionIn");
	GLint colorLocation = glGetAttribLocation(program.id, "colorIn");

	glGenBuffers(1, &program.vbo);
	glGenVertexArrays(1, &program.vao);

	// x, y, z, r, g, b (triangle)
	float vertices[] =
	{
		0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0,
	};
	glBindVertexArray(program.vao);
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, program.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(0));
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	glUseProgram(program.id);
}

void draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
#if SE_DEBUG
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif

	try
	{
		EngineConfig config;

		Engine& engine = GetEngine();

		if (engine.Init(config))
		{
			initShader();
			initProgram();
			initVertexObjects();

			while (!engine.IsEnd())
			{
				engine.Update();
				engine.BeginFrame();
				draw();
				engine.EndFrame();

				if (Keyboard::Get().KeyPressed(Keyboard::KEY_ESCAPE))
					break;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::ostringstream msg;
		msg << "Application initialization failed!" << std::endl << std::endl;
		msg << e.what();
#if SE_PLATFORM_WINDOWS
		MessageBoxA(0, msg.str().c_str(), "Error", MB_ICONERROR);
#endif
	}


	return 0;
}