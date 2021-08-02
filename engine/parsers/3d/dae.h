struct DAESource
{
	float* float_array;
	unsigned int count;
	unsigned int stride;
};

void Parser::parseDAE(const char* file, ParsedModel3D* model)
{
	rapidxml::file<> src(file);
	rapidxml::xml_document<> doc;
	doc.parse<0>(src.data());

	rapidxml::xml_node<>* colladaNode = doc.first_node("COLLADA");
	rapidxml::xml_node<>* meshNode = colladaNode->first_node("library_geometries")->first_node("geometry")->first_node("mesh");

	std::map<std::string, DAESource> sourceMap;
	std::map<std::string, std::string> srcRefMap;

	for (rapidxml::xml_node<>* sourceNode = meshNode->first_node(); sourceNode; sourceNode = sourceNode->next_sibling())
		if (std::string(sourceNode->name()) == "source")
		{
			std::string id = sourceNode->first_attribute("id")->value();
			rapidxml::xml_node<>* floatArrNode = sourceNode->first_node("float_array");

			int count = std::stoi(floatArrNode->first_attribute("count")->value());

			float* float_array = new float[count];
			std::string floatArrContent = floatArrNode->value();

			for (int i = 0; i < count; i++)
			{
				int found = floatArrContent.find(' ');
				float num = std::stof(floatArrContent.substr(0, found).c_str());
				floatArrContent = floatArrContent.substr(found + 1);

				float_array[i] = num;
			}

			rapidxml::xml_node<>* accessorNode = sourceNode->first_node("technique_common")->first_node("accessor");
			int stride = std::stoi(accessorNode->first_attribute("stride")->value());

			DAESource source = { float_array, count, stride };
			sourceMap[id] = source;
		}
		else if (std::string(sourceNode->name()) == "vertices")
		{
			std::string nodeId = sourceNode->first_attribute("id")->value();

			for (rapidxml::xml_node<>* inputNode = sourceNode->first_node(); inputNode; inputNode = inputNode->next_sibling())
			{
				std::string sourceId = inputNode->first_attribute("source")->value();

				srcRefMap[nodeId] = std::string(sourceId).substr(1);
			}
		}
		else if (std::string(sourceNode->name()) == "triangles")
		{
			int count = std::stoi(sourceNode->first_attribute("count")->value()) * 3;
			std::map<std::string, std::vector<float>> floatArrs;

			int inputCount = 0;
			for (rapidxml::xml_node<>* inputNode = sourceNode->first_node(); inputNode; inputNode = inputNode->next_sibling())
				if (std::string(inputNode->name()) == "input")
					inputCount++;

			rapidxml::xml_node<>* pNode = sourceNode->first_node("p");
			std::string pNodeContent = pNode->value();

			model->vSize = count * 3 * sizeof(float);
			model->tcSize = count * 2 * sizeof(float);

			model->vertices = new float[model->vSize];
			model->normals = new float[model->vSize];
			model->texCoords = new float[model->tcSize];

			std::map<std::string, float*> floatArrMap;
			floatArrMap["VERTEX"] = &model->vertices[0];
			floatArrMap["NORMAL"] = &model->normals[0];
			floatArrMap["TEXCOORD"] = &model->texCoords[0];

			for (rapidxml::xml_node<>* inputNode = sourceNode->first_node(); inputNode; inputNode = inputNode->next_sibling())
				if (std::string(inputNode->name()) == "input")
				{
					std::string semantic = inputNode->first_attribute("semantic")->value();
					std::string source = std::string(inputNode->first_attribute("source")->value()).substr(1);
					int offset = std::stoi(inputNode->first_attribute("offset")->value());

					std::vector<float> floatArr = std::vector<float>();

					for (int i = offset; i < count * 3; i += inputCount)
					{
						DAESource src = sourceMap.find(source) != sourceMap.end() ? sourceMap[source] : sourceMap[srcRefMap[source]];
						int num = 0;

						for (int j = 0; j < inputCount; j++)
						{
							int found = pNodeContent.find(' ');

							if (j == offset)
								num = std::stoi(pNodeContent.substr(0, found).c_str());

							pNodeContent = pNodeContent.substr(found + 1);
						}

						for (int j = 0; j < src.stride; j++)
							floatArr.push_back(src.float_array[j + num * src.stride]);
					}

					pNodeContent = pNode->value();

					if (floatArr.size() > 0)
						memcpy(floatArrMap[semantic], &floatArr[0], floatArr.size() * sizeof(float));
				}
		}
}