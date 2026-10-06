#ifndef DATABASE_H
#define DATABASE_H
#include "vehicle.h"
#include "electricVehicle.h"
#include "gasVehicle.h"


class database
{

	/*
1. Search for a specific make, model, propulsion type, car color, or year of the vehicle 
2. Reserve a vehicle for a single day in the future 
a. Maximum of 3 future reservations must be supported 
b. The reservations can be for consecutive days, or the days can be spread out in any 
combination but the total days that can be reserved is 3 
3. Print out the list of vehicles in the inventory 
4. Print out the list of vehicles with reservations in the future 
5. Print out the list of vehicles without any reservations (the cars fully available) 
6. Advance the date by one day
	*/

private:

	vehicle* inventory[100]; // array of pointers to vehicle objects
	int inventorySize; // current size of the inventory
	int day;
	int month;
	int year;

public:

	//empty constructor creates an empty database with no vehicles and sets the date to 1/1/2023
	database(void);

	int setDate(int month, int day, int year);

	void nextDay(void);

	// Adds vehicle to the database 
	int addVehicle(vehicle* vPointer);

	//add reservation, returns 0 if successful
	int addReservation(vehicle* vPointer, int month, int day, int year);

	//prints only vehicles with reservations in the future
	void printReservedVehicles(void);

	//prints only vehicles without reservations in the future
	void printUnreservedVehicles(void);

	//search functions, returns # of vehicles found

	int searchMake(std::string make);

	int searchModel(std::string model);

	int searchYear(int year);

	int searchPropulsion(std::string propulsion);

	int searchColor(std::string color);




};


#endif
