#include <string>
#include <sstream> //  for ostringstream
#include <iomanip> //  for setprecision
#include "electricVehicle.h"
#include <iostream>

using namespace std;

electricVehicle::electricVehicle()
{
	EnergyCapacity = 0.0;
	Efficiency = 0.0;
}

int electricVehicle::SetElectricVehicleInfo(float userEnergyCap, float userEff)
{
	EnergyCapacity = userEnergyCap;
	Efficiency = userEff;
	return 0;
}

void electricVehicle::GetPropulsion(string& userPropulsionType)
{
	userPropulsionType = PropulsionType;
}

void electricVehicle::PrintVehicleInfo(void)
{
	//get vehicle info from base class
	string vMake, vModel, vColor;
	int vYear = 0;
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
}
