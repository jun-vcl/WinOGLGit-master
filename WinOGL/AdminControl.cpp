#include "stdafx.h"
#include "pch.h"
#include "AdminControl.h"


CAdminControl::CAdminControl()
{
	AppendShape();
}

CAdminControl::~CAdminControl()
{
	shape_head->FreeShape();
}

//�`�揈��
void CAdminControl::Draw()
{
	DrawPoints();
	DrawLines();
	DrawShape();
}

//�_�̕`��
void CAdminControl::DrawPoints()
{
	CShape* nowS = shape_head;
	CVertex* nowV = nowS->GetVertexHead();

	while (nowS != NULL)
	{
		nowV = nowS->GetVertexHead();
		while (nowV != NULL)
		{
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(nowV->GetX(), nowV->GetY());
			glEnd();

			nowV = nowV->GetNextVertex();
		}
		nowS = nowS->GetNextShape();
	}
}

//���̕`��
void CAdminControl::DrawLines()
{
	CVertex* nowV = shape_final->GetVertexHead();

	glLineWidth(5);

	glBegin(GL_LINE_STRIP);

	while (nowV != NULL)
	{
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(nowV->GetX(), nowV->GetY());
		nowV = nowV->GetNextVertex();
	}

	glEnd();
}

//�`��̕`��
void CAdminControl::DrawShape()
{
	CShape* nowS = shape_head;
	CVertex* nowV = nowS->GetVertexHead();

	while (nowS != NULL)
	{
		if (nowS->close == true)
		{
			nowV = nowS->GetVertexHead();

			glBegin(GL_LINE_LOOP);
			glColor3f(1.0, 1.0, 1.0);
			while (nowV != NULL)
			{			
				glVertex2f(nowV->GetX(), nowV->GetY());			
				nowV = nowV->GetNextVertex();
			}
			glEnd();
		}
		nowS = nowS->GetNextShape();
	}
}


//���_�C�}�`�̒ǉ�
void CAdminControl::SaveClick(float x, float y)
{
	CVertex* nowV = shape_final->GetVertexHead();

	//�_�̓��O����A�����ʒu�ɓ_��ǉ����Ȃ�����
	if (JudgeNaigai(x, y) == true || JudgeAppendVertex(x,y) == false)
	{
		return;
	}

	if (nowV == NULL)
	{
		shape_final->AppendVertex(x, y);
	}
	else
	{
		if (JudgeJikoKosa(x,y) == false && JudgeTaKosa(x,y) == false)
		{
			if (JudgeCloseShape(x, y) == true && JudgeNaiho() == false)
			{
				shape_final->close = true;
				AppendShape();
			}
			else
			{
				shape_final->AppendVertex(x, y);
			}
		}
	}
	
}

//Shape�̒ǉ�
CShape* CAdminControl::AppendShape()
{
	CShape* nowS = shape_head;
	CShape* newS = new CShape();

	if (nowS != NULL)
	{
		shape_final->SetNextShape(newS);
		newS->SetPreShape(shape_final);
		shape_final = newS;
	}
	else
	{
		shape_head = newS;
		shape_final = newS;
	}

	return newS;
}

//�����ʒu�ɕ����_�����ĂȂ��悤�ɂ��鏈��(���Ă鎞True)
bool CAdminControl::JudgeAppendVertex(float x, float y)
{
	float dis = 0;

	if (shape_final->VertexNum > 0)
	{
		dis = math.CalcDistance(x, y, shape_final->GetVertexFinal()->GetX(), shape_final->GetVertexFinal()->GetY());

		if (dis < 0.03)
		{
			return false;
		}
	}

	return true;
}

//���Ȍ�������(�������Ă���True)
bool CAdminControl::JudgeJikoKosa(float x, float y)
{
	CShape* nowS = shape_final;

	//�ǉ�������Vertex
	CVertex Ae;
	Ae.SetXY(x, y);

	//Shape����Vertex��3�ȏ゠��Ƃ�
	if (nowS->VertexNum > 2)
	{
		//�Ō�ɒǉ������_
		CVertex* As;
		As= nowS->GetVertexFinal();

		//�ǂ�������Vertex
		CVertex* Bs;
		CVertex* Be;

		Be = As->GetPreVertex();
		Bs = Be->GetPreVertex();

		//�x�N�g���v�Z
		CVertex Vector_a;
		Vector_a = math.CalcVector(As, &Ae);

		CVertex Vector_a1;
		Vector_a1 = math.CalcVector(As, Bs);

		CVertex Vector_a2;
		Vector_a1 = math.CalcVector(As, Be);

		CVertex Vector_b;
		Vector_b = math.CalcVector(Bs, Be);

		CVertex Vector_b1;
		Vector_b1 = math.CalcVector(Bs, As);

		CVertex Vector_b2;
		Vector_b1 = math.CalcVector(Bs, &Ae);

		//�O�όv�Z
		double Gaiseki_ca1 = math.CalcGaiseki(Vector_a, Vector_a1);
		double Gaiseki_ca2 = math.CalcGaiseki(Vector_a, Vector_a2);
		double Gaiseki_cb1 = math.CalcGaiseki(Vector_b, Vector_b1);
		double Gaiseki_cb2 = math.CalcGaiseki(Vector_b, Vector_b2);

		while (Bs != NULL)
		{
			Vector_a1 = math.CalcVector(As, Bs);
			Vector_a2 = math.CalcVector(As, Be);
			Vector_b = math.CalcVector(Bs, Be);
			Vector_b1 = math.CalcVector(Bs, As);
			Vector_b2 = math.CalcVector(Bs, &Ae);

			Gaiseki_ca1 = math.CalcGaiseki(Vector_a, Vector_a1);
			Gaiseki_ca2 = math.CalcGaiseki(Vector_a, Vector_a2);
			Gaiseki_cb1 = math.CalcGaiseki(Vector_b, Vector_b1);
			Gaiseki_cb2 = math.CalcGaiseki(Vector_b, Vector_b2);

			float ca1_ca2 = 0;
			float cb1_cb2 = 0;

			ca1_ca2 = Gaiseki_ca1 * Gaiseki_ca2;
			cb1_cb2 = Gaiseki_cb1 * Gaiseki_cb2;

			if (ca1_ca2 <= 0 && cb1_cb2 <= 0)
			{
				return true;
			}

			Be = Bs;
			Bs = Be->GetPreVertex();
		}		
	}
	return false;
}

//����������(�������Ă���True)
bool CAdminControl::JudgeTaKosa(float x, float y)
{
	CShape* nowS_final = shape_final;

	//�ǉ�������Vertex
	CVertex As;
	As.SetXY(x, y);

	CShape* nowS_head = shape_head;

	//�Ō�ɒǉ������_
	CVertex* Ae;
	Ae = nowS_final->GetVertexFinal();

	//�ǂ�������Vertex
	CVertex* Bs;
	CVertex* Be;

	//�x�N�g���v�Z
	CVertex Vector_a;
	CVertex Vector_a1;
	CVertex Vector_a2;
	CVertex Vector_b;
	CVertex Vector_b1;
	CVertex Vector_b2;

	//�O�όv�Z
	double Gaiseki_ca1;
	double Gaiseki_ca2;
	double Gaiseki_cb1;
	double Gaiseki_cb2;

	float ca1_ca2 = 0;
	float cb1_cb2 = 0;

	//Shape��2�ȏ゠��Ƃ��@���@�ŐV��Shape��Vertex����ȏ゠��Ƃ�
	if (nowS_head->GetNextShape() != NULL && Ae != NULL)
	{
		Vector_a = math.CalcVector(&As, Ae);
		while (nowS_head != nowS_final)
		{
			Bs = nowS_head->GetVertexHead();
			Be = Bs->GetNextVertex();

			while (Be != NULL)
			{
				Vector_a1 = math.CalcVector(&As, Bs);
				Vector_a2 = math.CalcVector(&As, Be);
				Vector_b = math.CalcVector(Bs, Be);
				Vector_b1 = math.CalcVector(Bs, &As);
				Vector_b2 = math.CalcVector(Bs, Ae);

				Gaiseki_ca1 = math.CalcGaiseki(Vector_a, Vector_a1);
				Gaiseki_ca2 = math.CalcGaiseki(Vector_a, Vector_a2);
				Gaiseki_cb1 = math.CalcGaiseki(Vector_b, Vector_b1);
				Gaiseki_cb2 = math.CalcGaiseki(Vector_b, Vector_b2);

				ca1_ca2 = Gaiseki_ca1 * Gaiseki_ca2;
				cb1_cb2 = Gaiseki_cb1 * Gaiseki_cb2;

				if (ca1_ca2 <= 0 && cb1_cb2 <= 0)
				{
					return true;
				}

				Bs = Be;
				Be = Be->GetNextVertex();
			}
			nowS_head = nowS_head->GetNextShape();
		}
	}
	return false;
}

//�_�̓��O����(���ɓ����Ă���True)
bool CAdminControl::JudgeNaigai(float x, float y)
{
	CShape* nowS_final = shape_final;

	//�ǉ�������Vertex
	CVertex As;
	As.SetXY(x, y);

	CShape* nowS_head = shape_head;

	//�ǂ�������Vertex
	CVertex* Bs;
	CVertex* Be;

	//�x�N�g���v�Z
	CVertex Vector_a;
	CVertex Vector_b;

	//�O�όv�Z
	float Gaiseki = 0;

	//���όv�Z
	float Naiseki = 0;

	//��
	float theta = 0;

	//�p�x
	float degree = 0;

	//��ڂ�Shape�����Ă��鎞
	if (nowS_head->close == true)
	{
		while (nowS_head != nowS_final)
		{
			Bs = nowS_head->GetVertexHead();
			Be = Bs->GetNextVertex();
			theta = 0;

			while (Be != NULL)
			{
				Vector_a = math.CalcVector(&As, Bs);
				Vector_b = math.CalcVector(&As, Be);
				
				Naiseki = math.CalcNaiseki(Vector_a, Vector_b);
				Gaiseki = math.CalcGaiseki(Vector_a, Vector_b);

				//Gaiseki = sqrt(pow(Gaiseki, 2));

				theta = theta + atan2f(Gaiseki, Naiseki);

				Bs = Be;
				Be = Be->GetNextVertex();
			}

			//�Ō�̒��_�ƍŏ��̒��_�Ōv�Z
			Vector_a = math.CalcVector(&As, Bs);
			Vector_b = math.CalcVector(&As, nowS_head->GetVertexHead());

			Naiseki = math.CalcNaiseki(Vector_a, Vector_b);
			Gaiseki = math.CalcGaiseki(Vector_a, Vector_b);

			//Gaiseki = sqrt(pow(Gaiseki, 2));

			theta = theta + atan2f(Gaiseki, Naiseki);

			theta = sqrt(pow(theta, 2));

			//degree = theta * 180 / PI;

			if (2*PI-theta < 0.01)
			{
				return true;
			}

			nowS_head = nowS_head->GetNextShape();
		}
	}
	return false;
}

//Shape����邩�̔���(���Ă�����True)
bool CAdminControl::JudgeCloseShape(float x, float y)
{
	float dis = math.CalcDistance(x, y, shape_final->GetVertexHead()->GetX(), shape_final->GetVertexHead()->GetY());

	//�N���b�N�����_��Vertex�̍Ō�̓_�̋��������ȉ��̎�
	if (dis < 0.05)
	{
		//���_���T���ȉ��̎�
		if (shape_final->VertexNum < 5)
		{
			return true;
		}

		//�ǉ�������Vertex
		CVertex* As;
		As = shape_final->GetVertexHead();

		//�Ō�ɒǉ������_
		CVertex* Ae;
		Ae = shape_final->GetVertexFinal();

		//�ǂ�������Vertex
		CVertex* Bs;
		CVertex* Be;

		//�x�N�g���v�Z
		CVertex Vector_a;
		CVertex Vector_a1;
		CVertex Vector_a2;
		CVertex Vector_b;
		CVertex Vector_b1;
		CVertex Vector_b2;

		//�O�όv�Z
		double Gaiseki_ca1;
		double Gaiseki_ca2;
		double Gaiseki_cb1;
		double Gaiseki_cb2;

		float ca1_ca2 = 0;
		float cb1_cb2 = 0;

		Bs = shape_final->GetVertexHead()->GetNextVertex();
		Be = Bs->GetNextVertex();

		while (Be->GetNextVertex() != NULL)
		{
			Vector_a = math.CalcVector(As, Ae);
			Vector_a1 = math.CalcVector(As, Bs);
			Vector_a2 = math.CalcVector(As, Be);
			Vector_b = math.CalcVector(Bs, Be);
			Vector_b1 = math.CalcVector(Bs, As);
			Vector_b2 = math.CalcVector(Bs, Ae);

			Gaiseki_ca1 = math.CalcGaiseki(Vector_a, Vector_a1);
			Gaiseki_ca2 = math.CalcGaiseki(Vector_a, Vector_a2);
			Gaiseki_cb1 = math.CalcGaiseki(Vector_b, Vector_b1);
			Gaiseki_cb2 = math.CalcGaiseki(Vector_b, Vector_b2);

			ca1_ca2 = Gaiseki_ca1 * Gaiseki_ca2;
			cb1_cb2 = Gaiseki_cb1 * Gaiseki_cb2;

			if (ca1_ca2 <= 0 && cb1_cb2 <= 0)
			{
				return false;
			}

			Bs = Be;
			Be = Be->GetNextVertex();
		}
		return true;
	}
}

//Shape�̓����(����Ă�Ƃ�True)
bool CAdminControl::JudgeNaiho()
{
	CShape* nowS_head = shape_head;
	CShape* nowS_final = shape_final;

	//���肷��Vertex
	CVertex* A = nowS_head->GetVertexHead();

	//�ǂ�������Vertex
	CVertex* Bs;
	CVertex* Be;

	//�x�N�g���v�Z
	CVertex Vector_a;
	CVertex Vector_b;

	//�O�όv�Z
	float Gaiseki = 0;

	//���όv�Z
	float Naiseki = 0;

	//��
	float theta = 0;

	//��ڂ�Shape�����Ă��鎞
	if (nowS_head->close == true)
	{
		while (nowS_head != nowS_final)
		{
			A = nowS_head->GetVertexHead();
			while (A != NULL)
			{
				Bs = nowS_final->GetVertexHead();
				Be = Bs->GetNextVertex();
				theta = 0;

				while (Be != NULL)
				{
					Vector_a = math.CalcVector(A, Bs);
					Vector_b = math.CalcVector(A, Be);

					Naiseki = math.CalcNaiseki(Vector_a, Vector_b);
					Gaiseki = math.CalcGaiseki(Vector_a, Vector_b);

					theta = theta + atan2f(Gaiseki, Naiseki);

					Bs = Be;
					Be = Be->GetNextVertex();
				}

				//�Ō�̒��_�ƍŏ��̒��_�Ōv�Z
				Vector_a = math.CalcVector(A, Bs);
				Vector_b = math.CalcVector(A, nowS_head->GetVertexHead());

				Naiseki = math.CalcNaiseki(Vector_a, Vector_b);
				Gaiseki = math.CalcGaiseki(Vector_a, Vector_b);

				theta = theta + atan2f(Gaiseki, Naiseki);

				theta = sqrt(pow(theta, 2));

				if (2 * PI - theta < 0.01)
				{
					return true;
				}
				A = A->GetNextVertex();
			}

			nowS_head = nowS_head->GetNextShape();
		}
	}
	return false;
}
