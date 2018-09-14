#pragma once
#include "Event.h"
#include"BloodDonationPoint.h"
class EndOfCampaign :
	public Event
{

	Calendar* calendar;
	BloodBank* bloodBank;
	BloodDonationPoint* bloodPoint;
public:
	EndOfCampaign(BloodBank* _bloodBank, Calendar* _calendar, BloodDonationPoint* _bloodPoint);
	void execute() override;
	~EndOfCampaign();
};

