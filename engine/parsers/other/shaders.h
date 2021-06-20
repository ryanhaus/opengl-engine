#pragma once

int Parser::parseShaderFile(const char* file, int type)
{
	FILE* s = fopen(file, "rb");
	fseek(s, 0, SEEK_END);
	size_t s_length = ftell(s);
	fseek(s, 0, SEEK_SET);

	char* source = new char[s_length + 1];
	fread(source, s_length, 1, s);
	source[s_length] = 0;

	fclose(s);

	int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	delete[] source;

	return shader;
}