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
	std::map<std::string, ShaderProgram> programMap;
	std::map<std::string, Model3D> modelMap;

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
					ShaderProgram* modelProgram = &programMap[std::string(currentObjectNode->first_attribute("shader")->value())];

					float x, y, z;
					sscanf(currentObjectNode->first_attribute("position")->value(), "%f,%f,%f", &x, &y, &z);

					if (std::string(currentObjectNode->name()) == "camera")
					{
						modelProgram->cameraPosition[0] = x;
						modelProgram->cameraPosition[1] = y;
						modelProgram->cameraPosition[2] = z;
					}
					else if (std::string(currentObjectNode->name()) == "model")
					{
						Model3D model(currentObjectNode->first_attribute("src")->value());
						model.translation.x = x;
						model.translation.y = y;
						model.translation.z = z;

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
		for (int i = 0; i < models.size(); i++)
			modelMap[models[i].first].draw(programMap[models[i].second], window);
	}
private:
	std::map<std::string, int> shaderMap;
	std::vector<std::pair<std::string, std::string>> models;

	void fillShaderMap()
	{
		shaderMap.insert_or_assign("vertex", GL_VERTEX_SHADER);
		shaderMap.insert_or_assign("fragment", GL_FRAGMENT_SHADER);
	}
};