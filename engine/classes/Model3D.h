#pragma once

class Model3D
{
public:
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 rotation;

	Model3D(const char* file)
	{
		ParsedModel3D parsed;
		Parser::parseSTL(file, &parsed);
		vSize = parsed.vSize;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vSize, parsed.vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		delete[] parsed.vertices;

		glGenBuffers(1, &nbo);
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glBufferData(GL_ARRAY_BUFFER, parsed.vSize, parsed.normals, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);

		delete[] parsed.normals;

		translation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
		rotation = glm::vec3(0.0f);
	}

	void draw(ShaderProgram program)
	{
		program.use();

		glm::mat4 modelMat = MatrixGenerator::generateModelMatrix(translation, scale, rotation);
		glm::mat4 viewMat = MatrixGenerator::generateViewMatrix(program.cameraPosition);
		glm::mat4 projMat = MatrixGenerator::generateProjectionMatrix();
		glm::mat4 mvp = projMat * viewMat * modelMat;
		glUniformMatrix4fv(program.getUniform("mvp"), 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vSize / (3 * sizeof(float)));
	}
private:
	unsigned int vSize;
	unsigned int vao, vbo, nbo;
};