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

	//最初の図形（立方体）を作成
	void CreateRect();

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
	//選択した頂点の描画
	void DrawChooseVertex();
	//選択した辺の描画
	void DrawChooseLine();
	//選択した図形の描画
	void DrawChooseShape();

	//Shapeの追加
	CShape* AppendShape();

	//同じ位置に複数個点がうてないようにする処理(うてる時True)
	bool JudgeAppendVertex(float x, float y);

	//自己交差判定(交差してたらTrue)
	bool JudgeJikoKosa(float x, float y);

	//他交差判定(交差してたらTrue)
	bool JudgeTaKosa(float x, float y);

	//点の内外判定(中に入ってたらTrue)
	bool JudgeNaigai(float x, float y);

	//Shapeを閉じるかの判定(閉じていい時True)
	bool JudgeCloseShape(float x, float y);

	//Shapeの内包判定(内包してるときTrue)
	bool JudgeNaiho();

	//頂点、図形の選択
	void ChooseClick(float x, float y);

	//頂点の選択
	CVertex* ChooseVertex(float x, float y);
	//選択した頂点の初期化
	void FreeChooseVertex();

	//辺の選択
	void ChooseLine(float x, float y);
	//選択した辺の初期化
	void FreeChooseLine();

	//図形の選択
	void ChooseShape(float x, float y);
	//選択した頂点の初期化
	void FreeChooseShape();

	//点の内外判定(中に入ってたらTrue)_Shapeを返却するバージョン
	CShape* JudgeNaigai_Shape(float x, float y);

private:
	#define PI 3.14159265359

	//計算用のクラス
	CMath math;

	CShape* shape_head = NULL;
	CShape* shape_final = NULL;

	//選択した頂点
	CVertex* ChooseV = NULL;
	//選択した図形
	CShape* ChooseS = NULL;
	//選択した辺の始点
	CVertex* ChooseL1 = NULL;
	//選択した辺の終点
	CVertex* ChooseL2 = NULL;

};
