#include <string>
#include <sstream> //  for ostringstream
#include <iomanip> //  for setprecision
#include "electricVehicle.h"

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

string electricVehicle::GetVehicleSpecs()
{
	string Make, Model, Color;
	int Year = 0;

	GetVehicleInfo(Make, Model, Year, Color);

	string propulsionType = "EV";
	ostringstream specs;

	specs << Make << " "
		<< Model << " "
		<< Year << " "
		<< Color << " "
		<< propulsionType << " "
		<< fixed << setprecision(1) << EnergyCapacity << " "
		<< fixed << setprecision(1) << Efficiency;
	return specs.str();
}
