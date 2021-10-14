#include "stdafx.h"
#include "VertexCopy.h"


CVertexCopy::CVertexCopy()
{
}


CVertexCopy::~CVertexCopy()
{
}

CVertexCopy::CVertexCopy(float x, float y)
{
	SetXY(x, y);
}

//ŽŸ‚ÌƒZƒ‹
void CVertexCopy::SetNextVertexCopy(CVertexCopy *vertex)
{
	next_vertex_copy = vertex;
}

CVertexCopy *CVertexCopy::GetNextVertexCopy()
{
	return next_vertex_copy;
}

void CVertexCopy::SetXY(float x, float y)
{
	this->x = x;
	this->y = y;
}

float CVertexCopy::GetX()
{
	return x;
}

float CVertexCopy::GetY()
{
	return y;
}

void CVertexCopy::FreeVertexCopy()
{
	CVertexCopy* now = this;
	while (now != NULL)
	{
		CVertexCopy* del_cell = now;
		now = now->GetNextVertexCopy();
		delete del_cell;
	}
}