#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class MatrixGenerator
{
public:
	static glm::mat4 generateModelMatrix(glm::vec3 translation, glm::vec3 scale, glm::vec3 rotation)
	{
		glm::mat4 translationMat = glm::mat4(0.0f);
		translationMat[3][0] = translation.x;
		translationMat[3][1] = translation.y;
		translationMat[3][2] = translation.z;
		translationMat[0][0] = 1.0f;
		translationMat[1][1] = 1.0f;
		translationMat[2][2] = 1.0f;
		translationMat[3][3] = 1.0f;

		glm::mat4 scaleMat = glm::scale(scale);
		glm::quat rotationQuat(radians(rotation));
		glm::mat4 rotationMat = glm::toMat4(rotationQuat);

		return translationMat * rotationMat * scaleMat;
	}

	static glm::mat4 generateViewMatrix(glm::vec3 translation, glm::vec3 eulerAngles)
	{
		glm::vec3 s(sinf(eulerAngles.x), sinf(eulerAngles.y), sinf(eulerAngles.z));
		glm::vec3 c(cosf(eulerAngles.x), cosf(eulerAngles.y), cosf(eulerAngles.z));

		glm::vec3 pointVector(1.0f);

		pointVector.x *= c.x;
		pointVector.z *= s.x;

		pointVector.z *= c.y;
		pointVector.y *= s.y;

		pointVector += translation;

		return glm::lookAt(translation, pointVector, glm::vec3(s.z, c.z, 0));
	}

	static glm::mat4 generateProjectionMatrix(float w = 720.0f, float h = 480.0f, float fov = 70.0f, float zNear = 0.1f, float zFar = 1000.0f)
	{
		return glm::perspective(glm::radians(fov), w / h, zNear, zFar);
	}
};