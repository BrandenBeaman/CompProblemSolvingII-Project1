#include <string>
#include <sstream> //  for ostringstream
#include <iomanip> //  for setprecision
#include "gasVehicle.h"
#include <iostream>

using namespace std;

// Constructor to initialize primitive data members
gasVehicle::gasVehicle()
{
	FuelCapacity = 0.0;
	Efficiency = 0.0;
}
// Method to set gas vehicle information sets user varibles to the Fuel capacity and efficiency of the vehicle, returns 0 if successful
int gasVehicle::SetGasVehicleInfo(float userFuelCap, float userEff)
{
	FuelCapacity = userFuelCap;
	Efficiency = userEff;
	return 0;
}

// Method to get propulsion type, sets user varible to the propulsion type of the vehicle, "ICE" for gas vehicles
void gasVehicle::GetPropulsion(string& userPropulsionType)
{
	userPropulsionType = PropulsionType;
}

// Method to print gas vehicle information
void gasVehicle::PrintVehicleInfo(void)
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
	cout << fixed << setprecision(2) << "Fuel Capacity: " << FuelCapacity << " gallons" << endl;
	cout << fixed << setprecision(2) << "Efficiency: " << Efficiency << " miles/gallon" << endl;

	//print reservation days if any
	int day1, day2, day3;
	GetReservationDays(day1, day2, day3);
	cout << "Reservations: " << day1 << ", " << day2 << ", " << day3 << endl;
}