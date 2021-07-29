#include <vector>
#include <array>

void Parser::parseOBJ(const char* file, ParsedModel3D* model)
{
	std::ifstream f(file);
	std::string line;

	std::vector<std::array<float, 3>> vertices;
	std::vector<std::array<float, 3>> normals;
	std::vector<std::array<float, 2>> textureCoords;
	std::vector<std::array<std::array<int, 3>, 3>> faces;

	while (std::getline(f, line))
	{
		std::string prefix = line.substr(0, 2);
		if (prefix == "v ")
		{
			std::array<float, 3> vertex;
			sscanf(line.c_str(), "v %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
			vertices.push_back(vertex);
		}
		else if (prefix == "vn")
		{
			std::array<float, 3> vertex;
			sscanf(line.c_str(), "vn %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
			normals.push_back(vertex);
		}
		else if (prefix == "vt")
		{
			std::array<float, 2> vertex;
			sscanf(line.c_str(), "vt %f %f", &vertex[0], &vertex[1]);
			textureCoords.push_back(vertex);
		}
		else if (prefix == "f ")
		{
			std::array<std::array<int, 3>, 3> f;
			sscanf(line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &f[0][0], &f[0][1], &f[0][2], &f[1][0], &f[1][1], &f[1][2], &f[2][0], &f[2][1], &f[2][2]);
			faces.push_back(f);
		}
	}

	model->vSize = faces.size() * 9;
	model->vertices = new float[model->vSize];
	model->normals = new float[model->vSize];

	model->tcSize = faces.size() * 6;
	model->texCoords = new float[model->tcSize];

	model->vSize *= sizeof(float);
	model->tcSize *= sizeof(float);

	for (int i = 0; i < faces.size(); i++)
	{
		for (int j = 0; j < 3; j++)
			switch (j)
			{
			case 0:
				for (int k = 0; k < 3; k++)
					for (int l = 0; l < 3; l++)
						model->vertices[i * 9 + k * 3 + l] = vertices[faces[i][k][0] - 1][l];
				break;
			case 1:
				for (int k = 0; k < 3; k++)
					for (int l = 0; l < 2; l++)
						model->texCoords[i * 6 + k * 2 + l] = textureCoords[faces[i][k][1] - 1][l];
				break;
			case 2:
				for (int k = 0; k < 3; k++)
					for (int l = 0; l < 3; l++)
						model->normals[i * 9 + k * 3 + l] = normals[faces[i][k][2] - 1][l];
				break;
			}
	}
}