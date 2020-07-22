#pragma once
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

class Shader
{
public:
    Shader(const char* file);
	Shader(const char* vertex_file_path, const char* fragment_file_path);
	~Shader();
	GLuint						GetShaderID() const;
	void						Use();
    void                        SetFloat(const char* name, GLfloat data);
private:
	GLuint						LoadShader(const char* vertex_file_path, const char* fragment_file_path);
	std::string					ReadShaderFile(const char* file_path);
	void						CompileShaders(GLuint ID, const char* ShaderPointer);
	GLint						Check(GLuint ID);
	GLuint                      LoadComputeShader(const char* cs_file_path);
	GLuint						_id;

};

