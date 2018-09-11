#include "stdafx.h"
#include "Patient.h"
#include <fstream>
using namespace std;

Patient::Patient(int b)
{
	bloodUnitsNeeded = roll_units();
	typeeNeeded = roll_type_needed();
	//For debugging
	//ofstream myfile;
	//myfile.open("BloodunitsNeeded.txt", ios_base::app);
	//myfile << bloodUnitsNeeded << endl;
	//myfile.close();
}


Patient::~Patient()
{
}

int roll_units()
{
	static double a= 0.175555987;	//This is the seed
	int y = 0;
	do
	{
		a = a * 79 - (int)(a * 79);
		y++;
	} while (a > 0.2);
	return y;
}
bool roll_type_needed()
{
	static double a = 0.123578;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return a > 0.6;
}