//Klasa reprezentująca pojedyńczego pacjenta
#pragma once
int roll_units();
bool roll_type_needed();
class Patient
{
	
public:
	Patient(int b=5);
	~Patient();
	int bloodUnitsNeeded;
	bool typeeNeeded;
};

