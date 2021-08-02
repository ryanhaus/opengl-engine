#include <picopng.cpp>

class Texture
{
public:
	Texture(const char* file, GLuint filter = GL_LINEAR)
	{
		std::vector<unsigned char> buffer, image;
		loadFile(buffer, file);
		int error = decodePNG(image, width, height, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int getID()
	{
		return texture;
	}
private:
	unsigned long width, height;
	unsigned int texture;
};