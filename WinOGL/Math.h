#pragma once
#include "Vertex.h"
class CMath
{
public:
	//二点間の距離の計算
	float CalcDistance(CVertex* V1, CVertex* V2);
	float CalcDistance(float x1, float y1, float x2, float y2);

	//二点間のベクトル計算
	CVertex CalcVector(CVertex* V1, CVertex* V2);

	//三点間の内積計算(V1V2ベクトルとV3V4ベクトル)
	float CalcNaiseki(CVertex* V1, CVertex* V2, CVertex* V3, CVertex* V4);
	float CalcNaiseki(CVertex Vector1, CVertex Vector2);

	//三点間の外積計算(V1V2ベクトルとV3V4ベクトル)
	float CalcGaiseki(CVertex* V1, CVertex* V2, CVertex* V3, CVertex* V4);
	float CalcGaiseki(CVertex Vector1, CVertex Vector2);

	//点と直線の距離計算(V1とL1L2の距離)
	float CalcDistance_PtoL1(CVertex* V1, CVertex* L1, CVertex* L2);

	//点と線分の距離計算(V1とL1L2の距離)
	float CalcDistance_PtoL2(CVertex* V1, CVertex* L1, CVertex* L2);
};

