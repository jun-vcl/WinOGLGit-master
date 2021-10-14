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

	//頂点，図形の追加
	void SaveClick(float x, float y);

	//描画処理
	void Draw();	
	//点の描画
	void DrawPoints();
	//線の描画
	void DrawLines();
	//形状の描画
	void DrawShape();

	//Shapeの追加
	CShape* AppendShape();

	//自己交差判定(交差してたらTrue)
	bool JudgeJikoKosa(float x, float y);

	//他交差判定(交差してたらTrue)
	bool JudgeTaKosa(float x, float y);

private:
	//計算用のクラス
	CMath math;

	CShape* shape_head = NULL;
	CShape* shape_final = NULL;

};
