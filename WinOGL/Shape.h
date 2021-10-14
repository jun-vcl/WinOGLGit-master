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
	//�}�`�����Ă��邩
	bool close = false;

	//Vertex�̐�
	int VertexNum = 0;

	//�O��Vertex���擾
	CShape* GetPreShape();
	//�O��Vertex��ݒ�
	CShape* SetPreShape(CShape* shape);
	//����Vertex���擾
	CShape* GetNextShape();
	//����Vertex��ݒ�
	CShape* SetNextShape(CShape* shape);
	//Shape�̍폜
	void FreeShape();


	//Vertex�̒ǉ�
	CVertex* AppendVertex(float x, float y);
	//�ŏ���Vertex���擾
	CVertex* GetVertexHead();
	//�Ō��Vertex���擾
	CVertex* GetVertexFinal();

};