#pragma once
class CEventFlag
{
public:
	CEventFlag();
	~CEventFlag();

private:
	bool CREATEFIGURE = FALSE;
	bool EDITFIGURE = FALSE;
	bool KAKUSHUKU = FALSE;
	bool KAITEN = FALSE;
	bool CREATEMEN = FALSE;
	bool XROTATE = FALSE;
	bool YROTATE = FALSE;
	bool ZROTATE = FALSE;
	bool THREED = FALSE;
	bool ALLDELETE = FALSE;

public:
	bool ReturnCREATEFIGURE();
	void ChangeCREATEFIGURE();

	bool ReturnEDITFIGURE();
	void ChangeEDITFIGURE();

	bool ReturnKAKUSHUKU();
	void ChangeKAKUSHUKU();

	bool ReturnKAITEN();
	void ChangeKAITEN();

	bool ReturnCREATEMEN();
	void ChangeCREATEMEN();

	bool ReturnXROTATE();
	void ChangeXROTATE();

	bool ReturnYROTATE();
	void ChangeYROTATE();

	bool ReturnZROTATE();
	void ChangeZROTATE();

	bool ReturnTHREED();
	void ChangeTHREED();

	bool ReturnALLDELETE();
	void ChangeALLDELETE();

};