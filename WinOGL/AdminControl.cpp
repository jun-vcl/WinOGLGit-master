#include "stdafx.h"
#include "pch.h"
#include "AdminControl.h"


CAdminControl::CAdminControl()
{
	AppendShape();
	CreateRect();
	shape_final->close = true;
	AppendShape();
}

CAdminControl::~CAdminControl()
{
	shape_head->FreeShape();
}

//描画処理
void CAdminControl::Draw()
{
	DrawLines();
	DrawShape();
	DrawPoints();
	DrawChooseVertex();
	DrawChooseLine();
	DrawChooseShape();
}

//点の描画
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

//線の描画
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

//形状の描画
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

//選択した頂点の描画
void CAdminControl::DrawChooseVertex()
{
	//頂点を選択しているとき
	if (ChooseV != NULL)
	{
		glPointSize(13);
		glBegin(GL_POINTS);
		glColor3f(1.0, 0, 0);
		glVertex2f(ChooseV->GetX(), ChooseV->GetY());
		glEnd();
	}
}

//選択した辺の描画
void CAdminControl::DrawChooseLine()
{
	//辺を選択しているとき
	if (ChooseL1 != NULL && ChooseL2 != NULL)
	{
		glLineWidth(7);
		glBegin(GL_LINES);
		glColor3f(1.0, 0, 0);
		glVertex2f(ChooseL1->GetX(), ChooseL1->GetY());
		glVertex2f(ChooseL2->GetX(), ChooseL2->GetY());
		glEnd();
	}
}

//選択した図形の描画
void CAdminControl::DrawChooseShape()
{
	CVertex* nowV = NULL;

	if (ChooseS != NULL && ChooseS->close == true)
	{
		nowV = ChooseS->GetVertexHead();

		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0, 0);
		while (nowV != NULL)
		{
			glVertex2f(nowV->GetX(), nowV->GetY());
			nowV = nowV->GetNextVertex();
		}
		glEnd();

		nowV = ChooseS->GetVertexHead();
		glBegin(GL_POINTS);
		glColor3f(1.0, 0, 0);
		while (nowV != NULL)
		{
			glVertex2f(nowV->GetX(), nowV->GetY());
			nowV = nowV->GetNextVertex();
		}
		glEnd();
	}
}

//最初の図形（立方体）を作成
void CAdminControl::CreateRect()
{
	shape_final->AppendVertex(0.2, 0.2);
	shape_final->AppendVertex(-0.2, 0.2);
	shape_final->AppendVertex(-0.2, -0.2);
	shape_final->AppendVertex(0.2, -0.2);
}

//頂点，図形の追加
void CAdminControl::SaveClick(float x, float y)
{
	CVertex* nowV = shape_final->GetVertexHead();

	//点の内外判定、同じ位置に点を追加しない判定
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

//Shapeの追加
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

//同じ位置に複数個点がうてないようにする処理(うてる時True)
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

//自己交差判定(交差してたらTrue)
bool CAdminControl::JudgeJikoKosa(float x, float y)
{
	CShape* nowS = shape_final;

	//追加したいVertex
	CVertex Ae;
	Ae.SetXY(x, y);

	//Shape内のVertexが3つ以上あるとき
	if (nowS->VertexNum > 2)
	{
		//最後に追加した点
		CVertex* As;
		As= nowS->GetVertexFinal();

		//追いかけるVertex
		CVertex* Bs;
		CVertex* Be;

		Be = As->GetPreVertex();
		Bs = Be->GetPreVertex();

		//ベクトル計算
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

		//外積計算
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

//他交差判定(交差してたらTrue)
bool CAdminControl::JudgeTaKosa(float x, float y)
{
	CShape* nowS_final = shape_final;

	//追加したいVertex
	CVertex As;
	As.SetXY(x, y);

	CShape* nowS_head = shape_head;

	//最後に追加した点
	CVertex* Ae;
	Ae = nowS_final->GetVertexFinal();

	//追いかけるVertex
	CVertex* Bs;
	CVertex* Be;

	//ベクトル計算
	CVertex Vector_a;
	CVertex Vector_a1;
	CVertex Vector_a2;
	CVertex Vector_b;
	CVertex Vector_b1;
	CVertex Vector_b2;

	//外積計算
	double Gaiseki_ca1;
	double Gaiseki_ca2;
	double Gaiseki_cb1;
	double Gaiseki_cb2;

	float ca1_ca2 = 0;
	float cb1_cb2 = 0;

	//Shapeが2つ以上あるとき　かつ　最新のShapeにVertexが二つ以上あるとき
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

//点の内外判定(中に入ってたらTrue)
bool CAdminControl::JudgeNaigai(float x, float y)
{
	CShape* nowS_final = shape_final;

	//追加したいVertex
	CVertex As;
	As.SetXY(x, y);

	CShape* nowS_head = shape_head;

	//追いかけるVertex
	CVertex* Bs;
	CVertex* Be;

	//ベクトル計算
	CVertex Vector_a;
	CVertex Vector_b;

	//外積計算
	float Gaiseki = 0;

	//内積計算
	float Naiseki = 0;

	//θ
	float theta = 0;

	//角度
	float degree = 0;

	//一つ目のShapeが閉じている時
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

			//最後の頂点と最初の頂点で計算
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

//Shapeを閉じるかの判定(閉じていい時True)
bool CAdminControl::JudgeCloseShape(float x, float y)
{
	float dis = math.CalcDistance(x, y, shape_final->GetVertexHead()->GetX(), shape_final->GetVertexHead()->GetY());

	//クリックした点とVertexの最後の点の距離が一定以下の時
	if (dis < 0.05)
	{
		//頂点が５こ以下の時
		if (shape_final->VertexNum < 5)
		{
			return true;
		}

		//追加したいVertex
		CVertex* As;
		As = shape_final->GetVertexHead();

		//最後に追加した点
		CVertex* Ae;
		Ae = shape_final->GetVertexFinal();

		//追いかけるVertex
		CVertex* Bs;
		CVertex* Be;

		//ベクトル計算
		CVertex Vector_a;
		CVertex Vector_a1;
		CVertex Vector_a2;
		CVertex Vector_b;
		CVertex Vector_b1;
		CVertex Vector_b2;

		//外積計算
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

//Shapeの内包判定(内包してるときTrue)
bool CAdminControl::JudgeNaiho()
{
	CShape* nowS_head = shape_head;
	CShape* nowS_final = shape_final;

	//判定するVertex
	CVertex* A = nowS_head->GetVertexHead();

	//追いかけるVertex
	CVertex* Bs;
	CVertex* Be;

	//ベクトル計算
	CVertex Vector_a;
	CVertex Vector_b;

	//外積計算
	float Gaiseki = 0;

	//内積計算
	float Naiseki = 0;

	//θ
	float theta = 0;

	//一つ目のShapeが閉じている時
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

				//最後の頂点と最初の頂点で計算
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


//頂点、図形の選択
void CAdminControl::ChooseClick(float x, float y)
{
	//選択した頂点を取得
	ChooseV = ChooseVertex(x, y);
	
	//頂点を選択していた時
	if (ChooseV != NULL)
	{
		FreeChooseLine();
	}
}

//頂点の選択
CVertex* CAdminControl::ChooseVertex(float x, float y)
{
	CShape* nowS_head = shape_head;
	CVertex* nowV_head = nowS_head->GetVertexHead();

	while (nowS_head != NULL)
	{
		nowV_head = nowS_head->GetVertexHead();
		while (nowV_head != NULL)
		{
			if (math.CalcDistance(nowV_head->GetX(), nowV_head->GetY(), x, y) < 0.05)
			{
				return nowV_head;
			}

			nowV_head = nowV_head->GetNextVertex();
		}
		nowS_head = nowS_head->GetNextShape();
	}

	return NULL;
}
//選択した頂点の初期化
void CAdminControl::FreeChooseVertex()
{
	ChooseV = NULL;
}

//辺の選択
void CAdminControl::ChooseLine(float x, float y)
{
	CShape* nowS_head = shape_head;
	float dis = 0;

	//クリックした点
	CVertex ClickV;
	ClickV.SetXY(x, y);

	while (nowS_head != NULL)
	{
		CVertex* nowV = nowS_head->GetVertexHead();

		if (nowV == NULL)
		{
			break;
		}

		while (nowV->GetNextVertex() != NULL)
		{
			dis = math.CalcDistance_PtoL2(&ClickV, nowV, nowV->GetNextVertex());

			if (dis < 0.1)
			{
				ChooseL1 = nowV;
				ChooseL2 = nowV->GetNextVertex();
				return;
			}

			nowV = nowV->GetNextVertex();
		}

		dis = math.CalcDistance_PtoL2(&ClickV, nowS_head->GetVertexFinal(), nowS_head->GetVertexHead());

		if (dis < 0.1)
		{
			ChooseL1 = nowV;
			ChooseL2 = nowS_head->GetVertexHead();
			return;
		}

		nowS_head = nowS_head->GetNextShape();
	}

	ChooseL1 = NULL;
	ChooseL2 = NULL;
}
//選択した辺の初期化
void CAdminControl::FreeChooseLine()
{
	ChooseL1 = NULL;
	ChooseL2 = NULL;
}

//図形の選択
void CAdminControl::ChooseShape(float x, float y)
{
	ChooseS = JudgeNaigai_Shape(x, y);
}
//選択した頂点の初期化
void CAdminControl::FreeChooseShape()
{
	ChooseS = NULL;
}
//点の内外判定(中に入ってたらTrue)_Shapeを返却するバージョン
CShape* CAdminControl::JudgeNaigai_Shape(float x, float y)
{
	CShape* nowS_final = shape_final;

	//追加したいVertex
	CVertex As;
	As.SetXY(x, y);

	CShape* nowS_head = shape_head;

	//追いかけるVertex
	CVertex* Bs;
	CVertex* Be;

	//ベクトル計算
	CVertex Vector_a;
	CVertex Vector_b;

	//外積計算
	float Gaiseki = 0;

	//内積計算
	float Naiseki = 0;

	//θ
	float theta = 0;

	//角度
	float degree = 0;

	//一つ目のShapeが閉じている時
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

			//最後の頂点と最初の頂点で計算
			Vector_a = math.CalcVector(&As, Bs);
			Vector_b = math.CalcVector(&As, nowS_head->GetVertexHead());

			Naiseki = math.CalcNaiseki(Vector_a, Vector_b);
			Gaiseki = math.CalcGaiseki(Vector_a, Vector_b);

			//Gaiseki = sqrt(pow(Gaiseki, 2));

			theta = theta + atan2f(Gaiseki, Naiseki);

			theta = sqrt(pow(theta, 2));

			//degree = theta * 180 / PI;

			if (2 * PI - theta < 0.01)
			{
				return nowS_head;
			}

			nowS_head = nowS_head->GetNextShape();
		}
	}
	return NULL;
}