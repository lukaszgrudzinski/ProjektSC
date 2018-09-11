//Event for getting rid of old blood
#ifndef UTILIZEBLOOD_H
#define UTILIZEBLOOD_H


#include "BloodDonationPoint.h"
#include "Event.h"
#include"BloodBank.h"
#pragma once
class UtilizeBlood :public Event
{
	BloodBank* bloodBank;
public:
	UtilizeBlood(int bestBy,BloodBank* _bloodBank);
	~UtilizeBlood();
	void execute  (BloodDonationPoint* bloodPoint);
	void execute() override;
	 
	  

};

#endif