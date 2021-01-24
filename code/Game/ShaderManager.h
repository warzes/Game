#pragma once

#include "ShaderProgram.h"

class ShaderManager
{
public:
	// loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static ShaderProgram LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name);
	// retrieves a stored sader
	static ShaderProgram GetShader(const std::string &name);
	
	static void Clear();

	static std::map<std::string, ShaderProgram> Shaders;
private:
	ShaderManager() = delete;
	// loads and generates a shader from file
	static ShaderProgram loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
};