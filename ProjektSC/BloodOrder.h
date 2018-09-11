#pragma once
#include "Event.h"
#include "BloodBank.h"
int roll_time();

class BloodOrder : public Event
{
	BloodBank* bloodBank;
	bool type;

public:
	char getBloodType() ;
	void execute() override;
	BloodOrder(BloodBank* _bloodBank,bool _type);
	~BloodOrder();
};

