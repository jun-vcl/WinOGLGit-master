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

//点と直線の距離計算(V1とL1L2の距離)
float CMath::CalcDistance_PtoL1(CVertex* V1, CVertex* L1, CVertex* L2)
{
	//L1とV1のベクトル
	CVertex vector_a;
	//L1とL2のベクトル
	CVertex vector_b;

	vector_a = CalcVector(L1, V1);
	vector_b = CalcVector(L1, L2);

	float sin = 0;
	float _a = 0, _b = 0;
	
	_a = sqrt(pow(vector_a.GetX(), 2)) + sqrt(pow(vector_a.GetY(), 2));
	_b = sqrt(pow(vector_b.GetX(), 2)) + sqrt(pow(vector_b.GetY(), 2));
	sin = sqrt(pow(CalcGaiseki(vector_a, vector_b), 2)) / (_a * _b);

	float d = 0;

	d = _b * sin;

	return d;
}

//点と線分の距離計算(V1とL1L2の距離)
float CMath::CalcDistance_PtoL2(CVertex* V1, CVertex* L1, CVertex* L2)
{
	//参考文献
	//https://qiita.com/kkdd/items/b3c5e06798e59fe2768e

	float _s, _t;
	float _sa, _sb, _ta, _tb;

	_sa = CalcDistance(V1, L2) * CalcDistance(L1, L2);
	_sb = CalcDistance(L1, L2) * CalcDistance(L1, L2);
	_ta = CalcDistance(L1, V1) * CalcDistance(L1, L2);
	_tb = CalcDistance(L1, L2) * CalcDistance(L1, L2);

	_s = _sa / _sb;
	_t = _ta / _tb;

	float x, y;

	x = _s * L1->GetX() + _t * L2->GetX();
	y = _s * L1->GetY() + _t * L2->GetY();

	float dis = 0;

	dis = CalcDistance(V1->GetX(), V1->GetY(), x, y);

	if (0 < _s && _s < 1)
	{
		return dis;
	}

	dis = CalcDistance(V1, L1);

	if (dis > CalcDistance(V1, L2))
	{
		dis = CalcDistance(V1, L2);
	}

	return dis;
}