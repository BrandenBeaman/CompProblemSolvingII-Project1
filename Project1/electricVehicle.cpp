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

void electricVehicle::GetVehicleSpecs(string& userPropulsionType, float& userEfficiency, float& userCapacity))
{
	userPropulsionType = PropulsionType;
	userCapacity = EnergyCapacity;
	userEfficiency = Efficiency;
}
