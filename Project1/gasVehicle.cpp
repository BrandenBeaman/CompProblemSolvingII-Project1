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

void gasVehicle::GetVehicleSpecs(string& userPropulsionType, float& userEfficiency, float& userCapacity)
{
	userPropulsionType = PropulsionType;
	userCapacity = FuelCapacity;
	userEfficiency = Efficiency;
}