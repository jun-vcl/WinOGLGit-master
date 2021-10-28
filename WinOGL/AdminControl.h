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

	//�ŏ��̐}�`�i�����́j���쐬
	void CreateRect();

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
	//�I���������_�̕`��
	void DrawChooseVertex();
	//�I�������ӂ̕`��
	void DrawChooseLine();
	//�I�������}�`�̕`��
	void DrawChooseShape();

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

	//���_�A�}�`�̑I��
	void ChooseClick(float x, float y);

	//���_�̑I��
	CVertex* ChooseVertex(float x, float y);
	//�I���������_�̏�����
	void FreeChooseVertex();

	//�ӂ̑I��
	void ChooseLine(float x, float y);
	//�I�������ӂ̏�����
	void FreeChooseLine();

	//�}�`�̑I��
	void ChooseShape(float x, float y);
	//�I���������_�̏�����
	void FreeChooseShape();

	//�_�̓��O����(���ɓ����Ă���True)_Shape��ԋp����o�[�W����
	CShape* JudgeNaigai_Shape(float x, float y);

private:
	#define PI 3.14159265359

	//�v�Z�p�̃N���X
	CMath math;

	CShape* shape_head = NULL;
	CShape* shape_final = NULL;

	//�I���������_
	CVertex* ChooseV = NULL;
	//�I�������}�`
	CShape* ChooseS = NULL;
	//�I�������ӂ̎n�_
	CVertex* ChooseL1 = NULL;
	//�I�������ӂ̏I�_
	CVertex* ChooseL2 = NULL;

};
