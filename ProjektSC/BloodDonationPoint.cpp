//Class representing the whole Blood donation point and includes all objects inside

#include "stdafx.h"
#include <iostream>
#include "BloodDonationPoint.h"
#include "Patient.h"
#include <codecvt>
#include <algorithm>
#include <vector>
#include "UtilizeBlood.h"
#include <memory>
#include "Patient.h"



void BloodDonationPoint::showPatients()
{
	std::cout << "Current line of pacients:" << std::endl<<"	";
	if (lineOfPatients.size() == 0)
		std::cout << "Empty" << std::endl;
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		std::cout << "Patient nr " << i << " requires " << lineOfPatients[i]->bloodUnitsNeeded << " Units of blood type ";
		if (lineOfPatients[i]->typeeNeeded)
			std::cout << "B" << std::endl<<"	";
		else 
			std::cout << "A" << std::endl<<"	";
	}
	return;
}

void BloodDonationPoint::deleteFirstPatient()
{
	lineOfPatients.erase(lineOfPatients.begin());
}


bool BloodDonationPoint::canWeSendAPacientHome()
{
	if (isLineEmpty())
		return false;
	if (lineOfPatients[0]->bloodUnitsNeeded <= bloodBank->get_blood_bank_size())
		return true;
	else
		return false;
}

int BloodDonationPoint::getPatientsBloodNeeded()
{
	if (lineOfPatients.size() == 0)
		return 0;
	return lineOfPatients[0]->bloodUnitsNeeded;
}

bool BloodDonationPoint::getPatientsBloodTypeNeeded()
{
	if (lineOfPatients.size() == 0)
		return 0;
	return lineOfPatients[0]->typeeNeeded;
}

bool BloodDonationPoint::isLineEmpty()
{
	if (lineOfPatients.size() == 0)
		return true;
	else
		return false;
}

void BloodDonationPoint::eraseFirstPatient()
{
	
	bloodBank->popBloodUnit(lineOfPatients[0]->bloodUnitsNeeded);
	//bloodBank->bloodUnitsUsed+= lineOfPatients[0]->bloodUnitsNeeded;
	lineOfPatients.erase(lineOfPatients.begin());
}

void BloodDonationPoint::addPatient()
{
	lineOfPatients.push_back(new  Patient(5)); //TODO: replace 5 with rand
}





BloodDonationPoint::BloodDonationPoint(BloodBank* _bloodBank)
{
	bloodBank = _bloodBank;
}


BloodDonationPoint::~BloodDonationPoint()
{
}
