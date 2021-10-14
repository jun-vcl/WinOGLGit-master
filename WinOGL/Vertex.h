#pragma once
class CVertex
{
public:
	CVertex();
	~CVertex();
	CVertex(float x, float y);

private:
	float x;
	float y;
	CVertex* pre_vertex = NULL;
	CVertex* next_vertex = NULL;

public:
	//Vertexにx,yを格納
	void SetXY(float x, float y);	

	//Vertexのx座標を取得
	float GetX();
	//Vertexのy座標を取得
	float GetY();

	//前のVertexを取得
	CVertex* GetPreVertex();
	//前のVertexを設定
	CVertex* SetPreVertex(CVertex* vertex);

	//次のVertexを取得
	CVertex* GetNextVertex();
	//次のVertexを設定
	CVertex* SetNextVertex(CVertex* vertex);

	//Vertexの削除
	void FreeVertex();
};

