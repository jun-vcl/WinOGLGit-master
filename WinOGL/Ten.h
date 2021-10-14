#pragma once
class CTen
{
public:
	CTen();
	~CTen();
	CTen(float x, float y);

private:
	float x;
	float y;
	CTen *next_ten = NULL;

public:
	void SetNextTen(CTen *CTen);
	CTen *GetNextTen();
	float GetTenX();
	float GetTenY();
	void SetTenXY(float x, float y);
	void FreeTen();
};

