#include <string>
#include <sstream> //  for ostringstream
#include <iomanip> //  for setprecision
#include "electricVehicle.h"
#include <iostream>

using namespace std;

// Constructor to initialize primitive data members
electricVehicle::electricVehicle()
{
	EnergyCapacity = 0.0;
	Efficiency = 0.0;
}

// Method to set electric vehicle information sets user varibles to the energy capacity and efficiency of the vehicle, returns 0 if successful, returns 1 if invalid values are set (negative) and sets data members to 0.0
int electricVehicle::SetElectricVehicleInfo(float userEnergyCap, float userEff)
{

	if (userEnergyCap < 0 || userEff < 0)
	{
		return 1; // Return 1 for setting invalid values (negative)
	}
	else {
		EnergyCapacity = userEnergyCap;
		Efficiency = userEff;
		return 0; // Return 0 for successful setting of valid values
	}
}

// Method to get propulsion type, sets user varible to the propulsion type of the vehicle, "EV" for electric vehicles
void electricVehicle::GetPropulsion(string& userPropulsionType)
{
	userPropulsionType = PropulsionType;
}

// Method to print electric vehicle information
void electricVehicle::PrintVehicleInfo(void)
{
	//get vehicle info from base class
	string vMake, vModel, vColor;
    int vYear = 0;

	GetMake(vMake);
	GetModel(vModel);
	GetYear(vYear);
	GetColor(vColor);
	
	//print all data in a formatted manner
	cout << "Vehicle Info: " << endl;
	cout << "\nMake: " << vMake << endl;
	cout << "Model: " << vModel << endl;
	cout << "Year: " << vYear << endl;
	cout << "Color: " << vColor << endl;
	cout << "Propulsion Type: " << PropulsionType << endl;
	//fixed is a floating point format that uses fixed-point notation
	// setprecision sets the number of digits to display after the decimal point
	cout << fixed << setprecision(2) << "Energy Capacity: " << EnergyCapacity << " kWh" << endl;
	cout << fixed << setprecision(2) << "Efficiency: " << Efficiency << " miles/kWh" << endl;

	//print reservation days if any
	int day1, day2, day3;
	GetReservationDays(day1, day2, day3);
	cout << "Reservations: " << day1 << ", " << day2 << ", " << day3 << endl;
}
