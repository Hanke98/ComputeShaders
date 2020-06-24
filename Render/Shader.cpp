#include "Shader.h"

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path)
{
	_id = LoadShader(vertex_file_path, fragment_file_path);
}


Shader::~Shader()
{
}

GLuint Shader::GetShaderID() const
{
	return _id;
}

void Shader::Use()
{
	glUseProgram(_id);
}

GLuint Shader::LoadShader(const char* vertex_file_path, const char* fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// load file
	std::string VertexShaderCode = ReadShaderFile(vertex_file_path);
	std::string FragmentShaderCode = ReadShaderFile(fragment_file_path);
	// compile shader
	CompileShaders(VertexShaderID, VertexShaderCode.c_str());
	CompileShaders(FragmentShaderID, FragmentShaderCode.c_str());

	// std::cout << "Linking program" << std::endl;
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	Check(ProgramID);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}

std::string Shader::ReadShaderFile(const char* file_path)
{
	std::string ShaderCode;
	std::ifstream ShaderCodeStream(file_path, std::ios::in);
	if (ShaderCodeStream.is_open()) {
		std::stringstream sstr;
		sstr << ShaderCodeStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderCodeStream.close();
	}
	else {
		std::cout << "Impossible to open " << file_path << ".\n";
		return "";
	}
	return ShaderCode;
}

void Shader::CompileShaders(GLuint ID, const char* ShaderPointer)
{
	// std::cout <<"[log] void Shader::CompileShaders" << std::endl;
	glShaderSource(ID, 1, &ShaderPointer, nullptr);
	glCompileShader(ID);
	Check(ID);
}

GLint Shader::Check(GLuint ID)
{
	GLint Result = GL_FALSE;
	int InfoLogLength = 0;
	if (glIsShader(ID)) {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	}

	if (InfoLogLength > 0) {
		std::vector<char> ErrorMessage(InfoLogLength + 1);
		if (glIsShader(ID)) {
			glGetShaderInfoLog(ID, InfoLogLength, nullptr, &ErrorMessage[0]);
		}
		else
			glGetProgramInfoLog(ID, InfoLogLength, nullptr, &ErrorMessage[0]);
		for (int i = 0; i < ErrorMessage.size(); i++) {
			std::cout << ErrorMessage[i];
		}
		std::cout << std::endl;
	}
	return Result;
}
