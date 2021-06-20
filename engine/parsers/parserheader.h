#pragma once

struct Vertex3D
{
	float x, y, z;
};

struct ParsedModel3D
{
	float* vertices;
	unsigned int vSize;
	float* normals;
	unsigned int nSize;
};

class Parser
{
public:
	static void parseSTL(const char* file, ParsedModel3D* model);
	static int parseShaderFile(const char* file, int type);
};

#include "3d/3dheader.h"
#include "other/otherheader.h"