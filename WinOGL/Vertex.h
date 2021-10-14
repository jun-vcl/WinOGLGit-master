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
	//Vertex��x,y���i�[
	void SetXY(float x, float y);	

	//Vertex��x���W���擾
	float GetX();
	//Vertex��y���W���擾
	float GetY();

	//�O��Vertex���擾
	CVertex* GetPreVertex();
	//�O��Vertex��ݒ�
	CVertex* SetPreVertex(CVertex* vertex);

	//����Vertex���擾
	CVertex* GetNextVertex();
	//����Vertex��ݒ�
	CVertex* SetNextVertex(CVertex* vertex);

	//Vertex�̍폜
	void FreeVertex();
};

