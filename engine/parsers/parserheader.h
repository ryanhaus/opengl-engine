#pragma once

struct Vertex3D
{
	float x, y, z;
};

struct ParsedModel3D
{
	float* vertices;
	float* normals;
	unsigned int vSize;

	float* texCoords;
	unsigned int tcSize;
};

class Parser
{
public:
	static void parseSTL(const char* file, ParsedModel3D* model);
	static void parseOBJ(const char* file, ParsedModel3D* model);
	static int parseShaderFile(const char* file, int type);
};

#include "3d/3dheader.h"
#include "other/otherheader.h"