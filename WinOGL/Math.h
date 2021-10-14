#pragma once
#include "Vertex.h"
class CMath
{
public:
	//��_�Ԃ̋����̌v�Z
	float CalcDistance(CVertex* V1, CVertex* V2);
	float CalcDistance(float x1, float y1, float x2, float y2);

	//��_�Ԃ̃x�N�g���v�Z
	CVertex CalcVector(CVertex* V1, CVertex* V2);

	//�O�_�Ԃ̓��όv�Z(V1V2�x�N�g����V3V4�x�N�g��)
	float CalcNaiseki(CVertex* V1, CVertex* V2, CVertex* V3, CVertex* V4);
	float CalcNaiseki(CVertex Vector1, CVertex Vector2);

	//�O�_�Ԃ̊O�όv�Z(V1V2�x�N�g����V3V4�x�N�g��)
	float CalcGaiseki(CVertex* V1, CVertex* V2, CVertex* V3, CVertex* V4);
	float CalcGaiseki(CVertex Vector1, CVertex Vector2);
};

