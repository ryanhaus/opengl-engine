#pragma warning(disable: 6031)

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <vector>
#include <utility>
#include <map>
#include <string>

class Scene
{
public:
	Scene(const char* file)
	{
		fillShaderMap();

		rapidxml::file<> src(file);
		rapidxml::xml_document<> doc;
		doc.parse<0>(src.data());

		rapidxml::xml_node<>* sceneNode = doc.first_node("scene");

		for (rapidxml::xml_node<>* currentNode = sceneNode->first_node(); currentNode; currentNode = currentNode->next_sibling())
		{
			if (std::string(currentNode->name()) == "shaders")
				for (rapidxml::xml_node<>* currentProgramNode = currentNode->first_node(); currentProgramNode; currentProgramNode = currentProgramNode->next_sibling())
				{
					ShaderProgram program;

					for (rapidxml::xml_node<>* currentShaderNode = currentProgramNode->first_node(); currentShaderNode; currentShaderNode = currentShaderNode->next_sibling())
						program.addShader(currentShaderNode->first_attribute("src")->value(), shaderMap[std::string(currentShaderNode->first_attribute("type")->value())]);
					program.link();

					programMap[std::string(currentProgramNode->first_attribute("name")->value())] = program;
				}
			else if (std::string(currentNode->name()) == "world")
				for (rapidxml::xml_node<>* currentObjectNode = currentNode->first_node(); currentObjectNode; currentObjectNode = currentObjectNode->next_sibling())
				{
					float x, y, z;
					sscanf(currentObjectNode->first_attribute("position")->value(), "%f,%f,%f", &x, &y, &z);

					if (std::string(currentObjectNode->name()) == "camera")
					{
						float rx, ry, rz;
						sscanf(currentObjectNode->first_attribute("rotation")->value(), "%f,%f,%f", &rx, &ry, &rz);

						Camera cam;
						cam.setPosition(glm::vec3(x, y, z));
						cam.setRotation(glm::vec3(rx, ry, rz));

						cameras.push_back(cam);
					}
					else if (std::string(currentObjectNode->name()) == "light")
					{
						float intensity, r, g, b;
						sscanf(currentObjectNode->first_attribute("intensity")->value(), "%f", &intensity);
						sscanf(currentObjectNode->first_attribute("color")->value(), "%f,%f,%f", &r, &g, &b);

						Light light;
						light.setPosition(glm::vec3(x, y, z));
						light.setIntensity(intensity);
						light.setColor(glm::vec3(r, g, b));

						lights.push_back(light);
					}
					else if (std::string(currentObjectNode->name()) == "model")
					{
						Model3D model(currentObjectNode->first_attribute("src")->value());
						model.translation = glm::vec3(x, y, z);

						std::string name(currentObjectNode->first_attribute("name")->value());

						modelMap[name] = model;

						std::pair<std::string, std::string> modelPair{ name, std::string(currentObjectNode->first_attribute("shader")->value()) };
						models.push_back(modelPair);
					}
				}
		}

		
	}

	void draw(GLFWwindow* window)
	{
		for (int i = 0; i < cameras.size(); i++)
			for (int j = 0; j < models.size(); j++)
				modelMap[models[j].first].draw(&programMap[models[j].second], &cameras[i], lights);
	}

	Camera* getCameras()
	{
		return &cameras[0];
	}

	Light* getLights()
	{
		return &lights[0];
	}

	ShaderProgram* getProgram(std::string name)
	{
		return &programMap[name];
	}

	Model3D* getModel(std::string name)
	{
		return &modelMap[name];
	}
private:
	std::map<std::string, int> shaderMap;
	std::vector<std::pair<std::string, std::string>> models;
	std::map<std::string, ShaderProgram> programMap;
	std::map<std::string, Model3D> modelMap;

	std::vector<Camera> cameras;
	std::vector<Light> lights;

	unsigned int lightSsbo;

	void fillShaderMap()
	{
		shaderMap.insert_or_assign("vertex", GL_VERTEX_SHADER);
		shaderMap.insert_or_assign("fragment", GL_FRAGMENT_SHADER);
	}
};