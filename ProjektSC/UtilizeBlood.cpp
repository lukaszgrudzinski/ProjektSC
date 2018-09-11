//Event for getting rid of old blood
#include "stdafx.h"
#include "UtilizeBlood.h"
#include <vector>


UtilizeBlood::UtilizeBlood(int bestBy, BloodBank* _bloodBank)
{
	setTimetoExecution(bestBy);
	setType(4);
	bloodBank = _bloodBank;
	
}


UtilizeBlood::~UtilizeBlood()
{
}


void UtilizeBlood::execute()
{
	bloodBank->utilizeOldBlood();
}

