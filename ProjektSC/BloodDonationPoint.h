//Class representing the whole Blood donation point and includes all objects inside
#pragma once
#include <vector>
#include "BloodUnit.h"
#include "Patient.h"
#include "BloodBank.h"

class BloodDonationPoint
{
	std::vector <Patient*> lineOfPatients;	//The line of patients that are waiting to receive blood
	BloodBank* bloodBank;
	int correctionDueToAwarenessCampaign;	//Amount of time by which the interval between new blood donors is reduced
public:
	int getCorrectionDueToAwarenessCampaign();
	void setCorrectionDueToAwarenessCampaign(int x);
	void showPatients();
	void deleteFirstPatient();
	bool canWeSendAPacientHome();
	int getPatientsBloodNeeded();
	bool getPatientsBloodTypeNeeded();
	bool DoWeSendPatientWithBloodTypeA();
	bool DoWeSendPatientWithBloodTypeB();
	bool DoWeCallForAEmergencyBloodOrderA();
	bool DoWeCallForAEmergencyBloodOrderB();
	bool isLineEmpty();
	int eraseFirstPatientWithAType();
	int eraseFirstPatientWithBType();
	void addPatient();
	BloodDonationPoint(BloodBank* _bloodBank);
	~BloodDonationPoint();

};

