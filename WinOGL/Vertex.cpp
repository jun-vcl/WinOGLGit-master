#include "stdafx.h"
#include "pch.h"
#include "Vertex.h"


CVertex::CVertex()
{
	this->x = 0;
	this->y = 0;
}


CVertex::~CVertex()
{
}

CVertex::CVertex(float x, float y)
{
	SetXY(x, y);
}

void CVertex::SetXY(float x, float y)
{
	this->x = x;
	this->y = y;
}

//次のVertexを取得
CVertex* CVertex::GetNextVertex()
{
	return next_vertex;
}

//次のVertexを設定
CVertex* CVertex::SetNextVertex(CVertex* vertex)
{
	return next_vertex = vertex;
}

void CVertex::FreeVertex()
{
	CVertex* nowV = this;
	while (nowV != NULL)
	{
		CVertex* del_cell = nowV;
		nowV = nowV->GetNextVertex();
		delete del_cell;
	}
}

//前のVertexを取得
CVertex* CVertex::GetPreVertex()
{
	return pre_vertex;
}

//前のVertexを設定
CVertex* CVertex::SetPreVertex(CVertex* vertex)
{
	return pre_vertex = vertex;
}

//Vertexのx座標を取得
float CVertex::GetX()
{
	return this->x;
}
//Vertexのy座標を取得
float CVertex::GetY()
{
	return this->y;
}