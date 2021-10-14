#include "stdafx.h"
#include "Ten.h"


CTen::CTen()
{
}


CTen::~CTen()
{
}

CTen::CTen(float x, float y)
{
	SetTenXY(x, y);
}

void CTen::SetTenXY(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CTen::SetNextTen(CTen *ten)
{
	next_ten = ten;
}

CTen *CTen::GetNextTen()
{
	return next_ten;
}

float CTen::GetTenX()
{
	return x;
}

float CTen::GetTenY()
{
	return y;
}

void CTen::FreeTen()
{
	CTen* now = this;
	while (now != NULL)
	{
		CTen* del_cell = now;
		now = now->GetNextTen();
		delete del_cell;
	}
}

