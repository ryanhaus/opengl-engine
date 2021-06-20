#pragma once

class ShaderProgram
{
public:
	glm::vec3 cameraPosition;

	ShaderProgram()
	{
		id = glCreateProgram();
		cameraPosition = glm::vec3(0.0f);
	}

	~ShaderProgram()
	{
		glDeleteProgram(id);
	}

	void addShader(const char* file, int type)
	{
		int shader_id = Parser::parseShaderFile(file, type);
		
		int compiled;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_TRUE)
		{
			glAttachShader(id, shader_id);
			glDeleteShader(shader_id);
		}
		else
		{
			char errors[1024];
			glGetShaderInfoLog(shader_id, 1024, nullptr, errors);
			printf("An error occured while compiling the shader \"%s\":\n%s\n", file, errors);
		}
	}

	int getUniform(const char* name)
	{
		return glGetUniformLocation(id, name);
	}

	void link()
	{
		glLinkProgram(id);
		use();
	}

	void use()
	{
		glUseProgram(id);
	}
private:
	int id;
};