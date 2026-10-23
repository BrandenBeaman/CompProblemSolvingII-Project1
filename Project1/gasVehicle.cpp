#include <string>
#include <sstream> //  for ostringstream
#include <iomanip> //  for setprecision
#include "gasVehicle.h"
#include <iostream>

using namespace std;

gasVehicle::gasVehicle()
{
	FuelCapacity = 0.0;
	Efficiency = 0.0;
}

int gasVehicle::SetGasVehicleInfo(float userFuelCap, float userEff)
{
	FuelCapacity = userFuelCap;
	Efficiency = userEff;
	return 0;
}

void gasVehicle::GetPropulsion(string& userPropulsionType)
{
	userPropulsionType = PropulsionType;
}

void gasVehicle::PrintVehicleInfo(void)
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
	cout << fixed << setprecision(2) << "Fuel Capacity: " << FuelCapacity << " gallons" << endl;
	cout << fixed << setprecision(2) << "Efficiency: " << Efficiency << " miles/gallon" << endl;
}