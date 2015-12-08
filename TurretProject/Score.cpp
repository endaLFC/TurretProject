#include "stdafx.h"
#include "Score.h"


bool Score::instanceFlag = false;
Score* Score::instance = NULL;

Score* Score::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Score;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}