#include <picopng.cpp>

struct Image
{
	unsigned long width, height;
	std::vector<unsigned char> data;
};

class Texture
{
public:
	Texture(const char* file, GLuint filter = GL_LINEAR)
	{
		Image image;
		if (textureMap.find(std::string(file)) != textureMap.end())
			image = textureMap[std::string(file)];
		else
		{
			std::vector<unsigned char> buffer;
			loadFile(buffer, file);
			decodePNG(image.data, image.width, image.height, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());

			textureMap[std::string(file)] = image;
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.data[0]);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int getID()
	{
		return texture;
	}
private:
	unsigned int texture;

	static std::map<std::string, Image> textureMap;
};

std::map<std::string, Image> Texture::textureMap = std::map<std::string, Image>();