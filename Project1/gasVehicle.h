/* Header declration for the gasVehicle class, which is a derived class from the vehicle class
 This class contains data members and methods specific to gas vehicles..

 Data members:
	FuelCapacity
	Efficiency
Methods:
	int SetGasVehicleInfo(float userFuelCap, float userEff)
	string GetVehicleSpecs(void)

how to use:
   1. Create an object of the gasVehicle class
   2. Use the SetVehicleInfo() method inherited from the vehicle class to set basic vehicle info: Make, Model, Year, Color
   3. Use the SetGasVehicleInfo() method to set gas vehicle specific info: FuelCapacity, Efficiency, both arguments must be positive values, otherwise set will be ignored and the method will return 1
   4. Use the GetVehicleSpecs() method to get a string with the propulsion type, fuel capacity and efficiency

-reservation methods are inherited from the vehicle class and can be used to check and add reservations for gasVehicle objects
 */
#ifndef _GASVEHICLE_H
#define _GASVEHICLE_H

#include <string>
#include "vehicle.h"

using namespace std;

class gasVehicle : public vehicle
{
private:
	float  FuelCapacity; //gallons
	float  Efficiency;   //miles/gallon
	string PropulsionType = "ICE"; //internal combustion engine

public:
	gasVehicle();// explcit constructor to initalize data memebrs 
	int SetGasVehicleInfo(float userFuelCap, float userEff);//method to set gas vehicle information

	void GetPropulsion(string& userPropulsionType); // virtual method to get propulsion type
	void PrintVehicleInfo(void); //method to print gas vehicle information, implemented in dervided classes
};

#endif
