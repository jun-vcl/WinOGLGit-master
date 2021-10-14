#include "stdafx.h"
#include "EventFlag.h"


CEventFlag::CEventFlag()
{
}


CEventFlag::~CEventFlag()
{
}

bool CEventFlag::ReturnCREATEFIGURE()
{
	return CREATEFIGURE;
}

void CEventFlag::ChangeCREATEFIGURE()
{
	if (CREATEFIGURE)
	{
		CREATEFIGURE = FALSE;
	}
	else
	{
		CREATEFIGURE = TRUE;
	}
}

bool CEventFlag::ReturnEDITFIGURE()
{
	return EDITFIGURE;
}

void CEventFlag::ChangeEDITFIGURE()
{
	if (EDITFIGURE)
	{
		EDITFIGURE = FALSE;
	}
	else
	{
		EDITFIGURE = TRUE;
	}
}

bool CEventFlag::ReturnKAKUSHUKU()
{
	return KAKUSHUKU;
}

void CEventFlag::ChangeKAKUSHUKU()
{
	if (KAKUSHUKU)
	{
		KAKUSHUKU = FALSE;
	}
	else
	{
		KAKUSHUKU = TRUE;
	}
}

bool CEventFlag::ReturnKAITEN()
{
	return KAITEN;
}

void CEventFlag::ChangeKAITEN()
{
	if (KAITEN)
	{
		KAITEN = FALSE;
	}
	else
	{
		KAITEN = TRUE;
	}
}

bool CEventFlag::ReturnCREATEMEN()
{
	return CREATEMEN;
}

void CEventFlag::ChangeCREATEMEN()
{
	if (CREATEMEN)
	{
		CREATEMEN = FALSE;
	}
	else
	{
		CREATEMEN = TRUE;
	}
}

bool CEventFlag::ReturnXROTATE()
{
	return XROTATE;
}

void CEventFlag::ChangeXROTATE()
{
	if (XROTATE)
	{
		XROTATE = FALSE;
	}
	else
	{
		XROTATE = TRUE;
	}
}

bool CEventFlag::ReturnYROTATE()
{
	return YROTATE;
}

void CEventFlag::ChangeYROTATE()
{
	if (YROTATE)
	{
		YROTATE = FALSE;
	}
	else
	{
		YROTATE = TRUE;
	}
}

bool CEventFlag::ReturnZROTATE()
{
	return ZROTATE;
}

void CEventFlag::ChangeZROTATE()
{
	if (ZROTATE)
	{
		ZROTATE = FALSE;
	}
	else
	{
		ZROTATE = TRUE;
	}
}

bool CEventFlag::ReturnTHREED()
{
	return THREED;
}

void CEventFlag::ChangeTHREED()
{
	if (THREED)
	{
		THREED = FALSE;
	}
	else
	{
		THREED = TRUE;
	}
}

bool  CEventFlag::ReturnALLDELETE()
{
	return ALLDELETE;
}

void  CEventFlag::ChangeALLDELETE()
{
	if (ALLDELETE)
	{
		ALLDELETE = FALSE;
	}
	else
	{
		ALLDELETE = TRUE;
	}
}
