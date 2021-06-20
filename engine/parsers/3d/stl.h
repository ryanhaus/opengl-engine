#pragma once
#pragma warning (disable : 4996)

struct STLHeader
{
	uint8_t header[80];
	uint32_t triangle_count;
};

#pragma pack(1)
struct STLTriangle
{
	Vertex3D normal;
	Vertex3D points[3];
	uint16_t attr_count;
};

void Parser::parseSTL(const char* file, ParsedModel3D* model)
{
	FILE* f = fopen(file, "rb");

	STLHeader header;
	fread(&header, sizeof(STLHeader), 1, f);

	STLTriangle* triangles = new STLTriangle[header.triangle_count];
	fread(triangles, sizeof(STLTriangle), header.triangle_count, f);

	fclose(f);

	model->vertices = new float[header.triangle_count * 9];
	model->vSize = header.triangle_count * 9 * sizeof(float);
	model->normals = new float[header.triangle_count * 9];
	model->nSize = header.triangle_count * 9 * sizeof(float);

	for (unsigned int i = 0; i < header.triangle_count; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			model->vertices[i * 9 + j * 3 + 0] = triangles[i].points[j].x;
			model->vertices[i * 9 + j * 3 + 1] = triangles[i].points[j].y;
			model->vertices[i * 9 + j * 3 + 2] = triangles[i].points[j].z;

			model->normals[i * 9 + j * 3 + 0] = triangles[i].normal.x;
			model->normals[i * 9 + j * 3 + 1] = triangles[i].normal.y;
			model->normals[i * 9 + j * 3 + 2] = triangles[i].normal.z;
		}
	}

	delete[] triangles;
}