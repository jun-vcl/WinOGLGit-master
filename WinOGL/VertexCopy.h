#pragma once
class CVertexCopy
{
public:
	CVertexCopy();
	~CVertexCopy();

	CVertexCopy(float x, float y);

private:
	float x;
	float y;
	CVertexCopy* next_vertex_copy = NULL;

public:
	void SetNextVertexCopy(CVertexCopy *vertex);
	CVertexCopy* GetNextVertexCopy();
	void SetXY(float x, float y);
	float GetX();
	float GetY();
	void FreeVertexCopy();
};

