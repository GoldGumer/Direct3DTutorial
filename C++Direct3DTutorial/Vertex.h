#pragma once
class Vertex
{
public:
	Vertex(float x, float y, float z);
	float* GetPos();
	void SetPos(float x, float y, float z);
private:
	float pos[3];
};

