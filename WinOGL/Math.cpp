#include "pch.h"
#include "Math.h"

//二点間の距離の計算
float CMath::CalcDistance(CVertex* V1, CVertex* V2)
{
	return sqrt(pow(V1->GetX() - V2->GetX(), 2) + pow(V1->GetY() - V2->GetY(), 2));
}

float CMath::CalcDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//二点間のベクトル計算(始点：V1,終点：V2)
CVertex CMath::CalcVector(CVertex* V1, CVertex* V2)
{
	CVertex vector;

	double x, y;

	x = V2->GetX() - V1->GetX();
	y = V2->GetY() - V1->GetY();

	vector.SetXY(x, y);

	return vector;
}

//三点間の内積計算(V1V2ベクトルとV3V4ベクトル)
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

//三点間の外積計算(V1V2ベクトルとV3V4ベクトル)
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