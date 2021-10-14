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

//����Vertex���擾
CVertex* CVertex::GetNextVertex()
{
	return next_vertex;
}

//����Vertex��ݒ�
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

//�O��Vertex���擾
CVertex* CVertex::GetPreVertex()
{
	return pre_vertex;
}

//�O��Vertex��ݒ�
CVertex* CVertex::SetPreVertex(CVertex* vertex)
{
	return pre_vertex = vertex;
}

//Vertex��x���W���擾
float CVertex::GetX()
{
	return this->x;
}
//Vertex��y���W���擾
float CVertex::GetY()
{
	return this->y;
}