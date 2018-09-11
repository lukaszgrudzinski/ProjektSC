//Event for getting a pacient needed blood and then sending him home 
//powiedzmy
#pragma once
#include "Patient.h"
#include"BloodDonationPoint.h"
#include "BloodBank.h"
#include "Event.h"

class SendPatientHome : public Event
{
	BloodDonationPoint * bloodPoint;
	BloodBank* bloodBank;
public:
	SendPatientHome(BloodDonationPoint* _bloodPoint,BloodBank* _bloodBank);
	~SendPatientHome();
	void execute() override;
	void execute(BloodDonationPoint*abc);
};

