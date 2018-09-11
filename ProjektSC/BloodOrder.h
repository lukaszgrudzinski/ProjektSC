#pragma once
#include "Event.h"
#include "BloodBank.h"
int roll_time();

class BloodOrder : public Event
{
	BloodBank* bloodBank;
	Calendar* calendar;
	BloodDonationPoint* bloodPoint;
	bool type;

public:
	char getBloodType() ;
	void execute() override;
	BloodOrder(BloodBank* _bloodBank,bool _type,Calendar * _calendar,BloodDonationPoint* _bloodPoint);
	~BloodOrder();
};

