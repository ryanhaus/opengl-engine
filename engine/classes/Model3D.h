#pragma once
#include <vector>
#include <boost/filesystem.hpp>

class Model3D
{
public:
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::vec3 color;
	Texture* texture;

	Model3D()
	{ }

	Model3D(const char* file)
	{
		ParsedModel3D parsed;

		std::string fileExtension = (boost::filesystem::path(file).extension().string());
		if (fileExtension == ".stl")
			Parser::parseSTL(file, &parsed);
		else if (fileExtension == ".obj")
			Parser::parseOBJ(file, &parsed);
		else if (fileExtension == ".dae")
			Parser::parseDAE(file, &parsed);

		vSize = parsed.vSize;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, parsed.vSize, parsed.vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		delete[] parsed.vertices;

		glGenBuffers(1, &nbo);
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glBufferData(GL_ARRAY_BUFFER, parsed.vSize, parsed.normals, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(1);

		delete[] parsed.normals;

		glGenBuffers(1, &tbo);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, parsed.tcSize, parsed.texCoords, GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
		glEnableVertexAttribArray(2);

		delete[] parsed.texCoords;

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		translation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
		rotation = glm::vec3(0.0f);
		color = glm::vec3(1.0f);
		texture = nullptr;
	}

	void draw(ShaderProgram* program, Camera* cam, std::vector<Light> lights)
	{
		int width, height;
		glfwGetWindowSize(cam->getWindow(), &width, &height);

		program->use();

		glm::mat4 modelMat = MatrixGenerator::generateModelMatrix(translation, scale, rotation);
		glm::mat4 viewMat = MatrixGenerator::generateViewMatrix(*cam);
		glm::mat4 projMat = MatrixGenerator::generateProjectionMatrix(width, height);
		glm::mat4 mvp = projMat * viewMat * modelMat;
		glUniformMatrix4fv(program->getUniform("mvp"), 1, GL_FALSE, &mvp[0][0]);

		modelMat = glm::transpose(glm::inverse(modelMat));
		glUniformMatrix4fv(program->getUniform("transformationMatTI"), 1, GL_FALSE, &modelMat[0][0]);

		glUniform3fv(program->getUniform("viewPos"), 1, &cam->getPosition()[0]);
		glUniform3fv(program->getUniform("objectColor"), 1, &color[0]);

		glUniform1i(program->getUniform("lights.count"), lights.size());
		for (int i = 0; i < lights.size(); i++)
			lights[i].uniform(program, i);

		if (texture != nullptr)
			glBindTexture(GL_TEXTURE_2D, texture->getID());
		glUniform1i(program->getUniform("hasTexture"), texture != nullptr);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vSize / (3 * sizeof(float)));

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
private:
	unsigned int vSize;
	unsigned int vao, vbo, nbo, tbo;
};