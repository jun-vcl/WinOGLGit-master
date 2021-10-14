#include "stdafx.h"
#include "ShapeCopy.h"


CShapeCopy::CShapeCopy()
{
	vertex_head_copy = NULL;
}


CShapeCopy::~CShapeCopy()
{
	vertex_head_copy->FreeVertexCopy();
}

void CShapeCopy::FreeShapeCopy()
{
	CShapeCopy *now = this;
	while (now != NULL)
	{
		CShapeCopy* del_cell = now;
		now = now->GetNextShapeCopy();
		delete del_cell;
	}
}

CShapeCopy* CShapeCopy::GetNextShapeCopy()
{
	return NextShapeCopy;
}

void CShapeCopy::SetNextShapeCopy(CShapeCopy* shape)
{
	NextShapeCopy = shape;
}

CVertexCopy *CShapeCopy::Getvertex_head_copy()
{
	CShapeCopy *s = this;

	return vertex_head_copy;
}

void CShapeCopy::AppendVertexCopy(float x, float y)
{
	CVertexCopy *now = vertex_head_copy;

	if (now != NULL)
	{
		while (now->GetNextVertexCopy() != NULL)
		{
			now = now->GetNextVertexCopy();
		}
		CVertexCopy* newVertex = new CVertexCopy(x, y);
		now->SetNextVertexCopy(newVertex);
	}
	else
	{
		CVertexCopy* newVertex = new CVertexCopy(x, y);
		vertex_head_copy = newVertex;
	}


}

void CShapeCopy::FreeVertexCopy(CShapeCopy *S)
{
	CVertexCopy* now = S->Getvertex_head_copy();
	while (now != NULL)
	{
		CVertexCopy* del_cell = now;
		now = now->GetNextVertexCopy();
		delete del_cell;
	}
}

//ˆø”“à‚Ìvertex‚ðíœ‚µŒq‚¬‚È‚¨‚·
void CShapeCopy::DeleteVertexCopy(CVertexCopy *del_cell)
{
	CVertexCopy *nowV = vertex_head_copy;
	if (nowV == del_cell)
	{
		vertex_head_copy = del_cell->GetNextVertexCopy();
		delete del_cell;
	}
	else
	{
		while (nowV != NULL)
		{
			if (nowV->GetNextVertexCopy() == del_cell)
			{
				nowV->SetNextVertexCopy(del_cell->GetNextVertexCopy());
				delete del_cell;
				break;
			}
			nowV = nowV->GetNextVertexCopy();
		}
	}
}


