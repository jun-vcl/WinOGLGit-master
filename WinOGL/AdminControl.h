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

	//�����ʒu�ɕ����_�����ĂȂ��悤�ɂ��鏈��(���Ă鎞True)
	bool JudgeAppendVertex(float x, float y);

	//���Ȍ�������(�������Ă���True)
	bool JudgeJikoKosa(float x, float y);

	//����������(�������Ă���True)
	bool JudgeTaKosa(float x, float y);

	//�_�̓��O����(���ɓ����Ă���True)
	bool JudgeNaigai(float x, float y);

	//Shape����邩�̔���(���Ă�����True)
	bool JudgeCloseShape(float x, float y);

	//Shape�̓����(����Ă�Ƃ�True)
	bool JudgeNaiho();

private:
	#define PI 3.14159265359

	//�v�Z�p�̃N���X
	CMath math;

	CShape* shape_head = NULL;
	CShape* shape_final = NULL;

};
