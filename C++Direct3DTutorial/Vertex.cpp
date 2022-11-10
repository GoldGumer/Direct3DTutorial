#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

float* Vertex::GetPos()
{
	return pos;
}

void Vertex::SetPos(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}
