#include "stdafx.h"
#include "NewBloodDonor.h"
#include <ostream>
#include <iostream>
#include <fstream>
using namespace std;




void NewBloodDonor::execute()
{
	if(bloodType)
		bloodBank->add_blood_unitB(new BloodUnit(500));
	else
		bloodBank->add_blood_unit(new BloodUnit(500));
	calendar->addEvent(new NewBloodDonor(bloodBank, calendar));

}

NewBloodDonor::NewBloodDonor(BloodBank * _bloodBank, Calendar * _calendar)
{
	setTimetoExecution(roll_donor());
	calendar = _calendar;
	bloodBank = _bloodBank;
	setType(2);
	bloodType = roll_blood_type();
	//For debugging
	//ofstream myfile;
	//myfile.open("TimesBetweenDonors.txt", ios_base::app);
	//myfile << getTimeToExecution()<<endl;
	//myfile.close();
}




NewBloodDonor::~NewBloodDonor()
{
}

int roll_donor()
{
	static double a = 0.175555987;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return round( -950 * log(a));	//-850
}
bool roll_blood_type()
{
	static double a = 0.175555987;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return a>0.6;	
}