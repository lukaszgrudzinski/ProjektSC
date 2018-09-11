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
	Calendar* calendar;
	BloodDonationPoint * bloodPoint;
public:
	UtilizeBlood(int bestBy,BloodBank* _bloodBank,Calendar* _calendar,BloodDonationPoint * _bloodPoint);
	~UtilizeBlood();
	void execute  (BloodDonationPoint* bloodPoint);
	void execute() override;
	 
	  

};

#endif