#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle()
{
	ten_head = NULL;
}


CTriangle::~CTriangle()
{
	ten_head->FreeTen();
}

void CTriangle::SetNextTriangle(CTriangle* triangle)
{
	NextTriangle = triangle;
}

void CTriangle::FreeTriangle()
{
	CTriangle *now = this;
	while (now != NULL)
	{
		CTriangle* del_cell = now;
		now = now->GetNextTriangle();
		delete del_cell;
	}
}

CTriangle* CTriangle::GetNextTriangle()
{
	return NextTriangle;
}

CTen* CTriangle::Getten_head()
{
	CTriangle *t = this;

	return ten_head;
}

void CTriangle::AppendTen(float x, float y)
{
	CTen *now = ten_head;

	if (now != NULL)
	{
		while (now->GetNextTen() != NULL)
		{
			now = now->GetNextTen();
		}
		CTen* newTen = new CTen(x, y);
		now->SetNextTen(newTen);
	}
	else
	{
		CTen* newTen = new CTen(x, y);
		ten_head = newTen;
	}
}

void CTriangle::FreeTen(CTriangle *T)
{
	CTen* now = T->Getten_head();
	while (now != NULL)
	{
		CTen* del_cell = now;
		now = now->GetNextTen();
		delete del_cell;
	}
}
