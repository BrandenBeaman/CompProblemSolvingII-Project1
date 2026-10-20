#include <string>
#include <sstream> //  for ostringstream
#include <iomanip> //  for setprecision
#include "gasVehicle.h"

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

string gasVehicle::GetVehicleSpecs()
{
	string Make, Model, Color;
	int Year = 0;

	GetVehicleInfo(Make, Model, Year, Color);

	string propulsionType = "ICE";
	ostringstream specs;

	specs << Make << " " 
		<< Model << " " 
		<< Year << " " 
		<< Color << " "
		<< propulsionType << " "
		<< fixed << setprecision(1) << FuelCapacity << " "
		<< fixed << setprecision(1) << Efficiency;
	return specs.str();
}