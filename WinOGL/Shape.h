#pragma once
#include "Vertex.h"

class CShape
{
public:
	CShape();
	~CShape();

private:
	CShape* pre_shape;
	CShape* next_shape;

	CVertex* vertex_head;
	CVertex* vertex_final;

public:
	//}Œ`‚ª•Â‚¶‚Ä‚¢‚é‚©
	bool close = false;

	//Vertex‚Ì”
	int VertexNum = 0;

	//‘O‚ÌVertex‚ğæ“¾
	CShape* GetPreShape();
	//‘O‚ÌVertex‚ğİ’è
	CShape* SetPreShape(CShape* shape);
	//Ÿ‚ÌVertex‚ğæ“¾
	CShape* GetNextShape();
	//Ÿ‚ÌVertex‚ğİ’è
	CShape* SetNextShape(CShape* shape);
	//Shape‚Ìíœ
	void FreeShape();


	//Vertex‚Ì’Ç‰Á
	CVertex* AppendVertex(float x, float y);
	//Å‰‚ÌVertex‚ğæ“¾
	CVertex* GetVertexHead();
	//ÅŒã‚ÌVertex‚ğæ“¾
	CVertex* GetVertexFinal();

};