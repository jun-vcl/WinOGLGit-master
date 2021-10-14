#include "stdafx.h"
#include "pch.h"
#include "Shape.h"
#include "Vertex.h"


CShape::CShape()
{
}


CShape::~CShape()
{
	vertex_head->FreeVertex();
}

//Shape‚Ìíœ
void CShape::FreeShape()
{
	CShape* nowS = this;
	while (nowS != NULL)
	{
		CShape* del_cell = nowS;
		nowS = nowS->GetNextShape();
		delete del_cell;
	}
}

//‘O‚ÌVertex‚ğæ“¾
CShape* CShape::GetPreShape()
{
	return pre_shape;
}

//‘O‚ÌVertex‚ğİ’è
CShape* CShape::SetPreShape(CShape* shape)
{
	return pre_shape = shape;
}

//Ÿ‚ÌVertex‚ğæ“¾
CShape* CShape::GetNextShape()
{
	return next_shape;
}

//Ÿ‚ÌVertex‚ğİ’è
CShape* CShape::SetNextShape(CShape* shape)
{
	return next_shape = shape;
}

CVertex* CShape::AppendVertex(float x, float y)
{
	CVertex* nowV = vertex_head;
	CVertex* newVertex = new CVertex(x, y);

	if (nowV != NULL)
	{
		newVertex->SetPreVertex(vertex_final);
		vertex_final->SetNextVertex(newVertex);
		vertex_final = newVertex;
	}
	else
	{
		vertex_head = newVertex;
		vertex_final = newVertex;
	}
	this->VertexNum++;
	return newVertex;
}

//Å‰‚ÌVertex‚ğæ“¾
CVertex* CShape::GetVertexHead()
{
	return vertex_head;
}

//ÅŒã‚ÌVertex‚ğæ“¾
CVertex* CShape::GetVertexFinal()
{
	return vertex_final;
}
