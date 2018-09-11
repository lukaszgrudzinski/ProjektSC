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
public:
	void showPatients();
	void deleteFirstPatient();
	bool canWeSendAPacientHome();
	int getPatientsBloodNeeded();
	bool getPatientsBloodTypeNeeded();
	bool isLineEmpty();
	void eraseFirstPatient();
	void addPatient();
	BloodDonationPoint(BloodBank* _bloodBank);
	~BloodDonationPoint();

};

