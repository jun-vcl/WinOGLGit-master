#pragma once
#include <gl/GL.h>
#include "pch.h"
#include "Shape.h"
#include "Math.h"


class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();

	//���_�C�}�`�̒ǉ�
	void SaveClick(float x, float y);

	//�`�揈��
	void Draw();	
	//�_�̕`��
	void DrawPoints();
	//���̕`��
	void DrawLines();
	//�`��̕`��
	void DrawShape();

	//Shape�̒ǉ�
	CShape* AppendShape();

	//���Ȍ�������(�������Ă���True)
	bool JudgeJikoKosa(float x, float y);

	//����������(�������Ă���True)
	bool JudgeTaKosa(float x, float y);

private:
	//�v�Z�p�̃N���X
	CMath math;

	CShape* shape_head = NULL;
	CShape* shape_final = NULL;

};
