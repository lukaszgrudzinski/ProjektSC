//Wydarzenie warunkowe odsyłające pacjenta do domu w przypadku gdy wystarczy dla niego krwii w banku krwii
//Brany pod uwage jest pierwszyw kolejce pacjent
#include "stdafx.h"
#include "SendPatientHome.h"
#include <vector>
#include <iostream>


SendPatientHome::SendPatientHome(BloodDonationPoint* _bloodPoint,BloodBank* _bloodBank)
{
	setTimetoExecution(0);
	bloodPoint = _bloodPoint;
	bloodBank = _bloodBank;
	setType(10);
}


SendPatientHome::~SendPatientHome()
{
}


void SendPatientHome::execute()
{
	if(bloodPoint->getPatientsBloodTypeNeeded())
		bloodBank->popBloodUnit(bloodPoint->getPatientsBloodNeeded());
	else
		bloodBank->popBloodUnitB(bloodPoint->getPatientsBloodNeeded());
	bloodBank->incBloodUnitsUsed(bloodPoint->getPatientsBloodNeeded());
	bloodPoint->deleteFirstPatient();
	
}

void SendPatientHome::execute(BloodDonationPoint * abc)
{
	;
}

