#include "pch.h"
#include "Math.h"

//��_�Ԃ̋����̌v�Z
float CMath::CalcDistance(CVertex* V1, CVertex* V2)
{
	return sqrt(pow(V1->GetX() - V2->GetX(), 2) + pow(V1->GetY() - V2->GetY(), 2));
}

float CMath::CalcDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//��_�Ԃ̃x�N�g���v�Z(�n�_�FV1,�I�_�FV2)
CVertex CMath::CalcVector(CVertex* V1, CVertex* V2)
{
	CVertex vector;

	double x, y;

	x = V2->GetX() - V1->GetX();
	y = V2->GetY() - V1->GetY();

	vector.SetXY(x, y);

	return vector;
}

//�O�_�Ԃ̓��όv�Z(V1V2�x�N�g����V3V4�x�N�g��)
float CMath::CalcNaiseki(CVertex* V1, CVertex* V2, CVertex* V3, CVertex* V4)
{
	CVertex Vector1, Vector2;

	Vector1 = CalcVector(V2, V1);
	Vector2 = CalcVector(V4, V3);

	float Naiseki = 0;

	Naiseki = (Vector1.GetX() * Vector2.GetX()) + (Vector1.GetY() * Vector2.GetY());

	return Naiseki;
}

float CMath::CalcNaiseki(CVertex Vector1, CVertex Vector2)
{
	float Naiseki = 0;

	Naiseki = (Vector1.GetX() * Vector2.GetX()) + (Vector1.GetY() * Vector2.GetY());

	return Naiseki;
}

//�O�_�Ԃ̊O�όv�Z(V1V2�x�N�g����V3V4�x�N�g��)
float CMath::CalcGaiseki(CVertex* V1, CVertex* V2, CVertex* V3, CVertex* V4)
{
	CVertex Vector1, Vector2;

	Vector1 = CalcVector(V2, V1);
	Vector2 = CalcVector(V4, V3);

	float Gaiseki = 0;

	Gaiseki = (Vector1.GetX() * Vector2.GetY()) - (Vector1.GetY() * Vector2.GetX());

	return Gaiseki;
}

float CMath::CalcGaiseki(CVertex Vector1, CVertex Vector2)
{
	float Gaiseki = 0;

	Gaiseki = (Vector1.GetX() * Vector2.GetY()) - (Vector1.GetY() * Vector2.GetX());

	return Gaiseki;
}