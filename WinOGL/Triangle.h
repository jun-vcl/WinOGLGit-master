#pragma once
#include "Ten.h"
class CTriangle
{
public:
	CTriangle();
	~CTriangle();

private:
	CTen *ten_head;
	CTriangle *NextTriangle;

public:
	void SetNextTriangle(CTriangle* triangle);
	void FreeTriangle();
	CTriangle* GetNextTriangle();
	CTen* Getten_head();
	void AppendTen(float x, float y);
	void FreeTen(CTriangle *T);

};

