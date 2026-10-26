/* Header declaration for the electricVehicle class, which is a derived class from the vehicle class
 This class contains data members and methods specific to electric vehicles..

 Data members:
	EnergyCapacity
	Efficiency
Methods:
	int SetElectricVehicleInfo(float userEnergyCap, float userEff)
	string GetVehicleSpecs(void)

how to use:
   1. Create an object of the electricVehicle class
   2. Use the SetVehicleInfo() method inherited from the vehicle class to set basic vehicle info: Make, Model, Year, Color
   3. Use the SetElectricVehicleInfo() method to set electric vehicle specific info: EnergyCapacity, Efficiency, both arguments must be positive values, otherwise set will be ignored and the method will return 1
   4. Use the GetVehicleSpecs() method to get a string with the propulsion type, energy capacity and efficiency

-reservation methods are inherited from the vehicle class and can be used to check and add reservations for electricVehicle objects
 */
#ifndef _ELECTRICVEHICLE_H
#define _ELECTRICVEHICLE_H

#include <string>
#include "vehicle.h"

using namespace std;

class electricVehicle : public vehicle
{
private:
	float  EnergyCapacity; //killowatt-hours
	float  Efficiency;   //miles/kwH
	string PropulsionType = "EV"; //electric vehicle

public:
	electricVehicle();// explcit constructor to initalize data memebrs 
	int SetElectricVehicleInfo(float userEnergyCap, float userEff);// method to set electric vehicle information
	void GetPropulsion(string& userPropulsionType); // virtual method to get propulsion type

	void PrintVehicleInfo(void); //method to print electric vehicle information, implemented in dervided classes

};


#endif
