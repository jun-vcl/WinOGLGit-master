#pragma once
#include "VertexCopy.h"

class CShapeCopy
{
public:
	CShapeCopy();
	~CShapeCopy();

private:
	CShapeCopy* NextShapeCopy;
	CVertexCopy* vertex_head_copy;

public:
	void SetNextShapeCopy(CShapeCopy* shape);
	void FreeShapeCopy();
	CShapeCopy* GetNextShapeCopy();
	CVertexCopy* Getvertex_head_copy();
	int count = 0;
	void AppendVertexCopy(float x, float y);
	void FreeVertexCopy(CShapeCopy *S);
	void DeleteVertexCopy(CVertexCopy *del_cell);
};

