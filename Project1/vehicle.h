/* Header declration for the vehicle class, which is the base class for all types of vehicles
   The derived classes will inherit from this class and implement the pure virtual method GetVehicleSpecs() to provide specific information about the vehicle type
 
 This class contains..
 The common data members shared by all type of vehicles:
   Make
   Model
   Year
   Color
 The common methods shared by all types of vehicles:

   int SetVehicleInfo(string userMake, string userModel, string userYear)
   int SetVehicleReservation(int day)
   int CheckReservationNumber()

   bool CheckReservationDay(int day)
   bool AddReservation(int day)

   void GetVehicleInfo(string& userMake, string& userModel, string& userYear)
   virtual string GetVehicleSpecs(void) = 0

How to use:
   1. Create an object of the derived class ElectricVehicle or GasVehicle
   2. Use the SetVehicleInfo() method to set basic vehicle info: Make, Model, Year, Color
  
  To add a reservation for a Vehicle:
    1. Database class should call CheckReservationDay() using a pointer to a vehicle object to check to see if that vehicle is available for a specific day
	2. Database class then should call CheckReservationNumber() using the same pointer to check to see if that vehicle has less than 3 reservations
	3. If both checks pass, Database class should call AddReservation() using the same pointer to add the reservation for the specific day
	(AddReservation() will check reservation critira internally as well as insuring the day of the reservation is after the current day and returns true if the reservation was added and false if not)


*/
#ifndef _VEHICLE_
#define _VEHICLE_

#include <string>


using namespace std;

class vehicle
{

	//private data memebers about each vehicle
private:
	string Make;
	string Model;
	string Color;
	int Year;

	int ReservationDays[3];//array to hold the days that the vehicle is reserved for, max 3 reservations
	int NumerOfReservations;//number of reservations for the vehicle

public:

	vehicle(); // explcit constructor to initalize primative data memebrs

	int  SetVehicleInfo(string userMake, string userModel, int userYear, string userColor); //method to set vehicle information

	bool CheckReservationDay(int day); //method to check if a vehicle is reserved for a specific day, returns true if date is reserved and false if date is available 
	int  CheckReservationNumber(); //method to check if a vehicle has less than 3 reservations, returns number of reservations for the vehicle
	bool AddReservation(int reservationDay, int currentDay); //method to add a reservation for a specific day, only allowed if CheckReservationDay returns false, CheckReservationNumber returns a value less than 3 and Current Day is before Reservation Day, returns true if reservation was added and false if not

	void GetReservationDays(int& userDay1, int& userDay2, int& userDay3); //method to get the reservation days for a vehicle, returns the reservation days in the parameters, if a reservation day is not set, it will return 0 for that day 
	void GetVehicleInfo(string& userMake, string& userModel, int& userYear, string& userColor); // method to get vehicle information

	virtual string GetVehicleSpecs(void) = 0; // pure virtual method for getting the specs of a specific type of vehicle, implemented in dervided classes
};

#endif //_VEHICLE_
