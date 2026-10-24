////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main.cpp
// CPET-321 Project 1 - Car Reservation System
//
// This program implements a car reservation system for a car rental counter. It reads a text file (Inventory.txt) that contains the list of 
// cars available to reserve. Each line of the file represents a single vehicle with seven fields: Make, Model, Year, Color, 
// Engine Type (ICE or EV), Fuel/Energy Capacity, and Efficiency.
// 
// The user can search the inventory, reserve a car for a single day in the future, print the inventory, print the cars w/ & w/o reservations,
// and advance the "date" one day at a time. The date starts @ Day 1.
//
// Based on the partial_main.cpp from Lab 5 
// 
// By: Aaron Kenneally
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "database.h"

using namespace std;

int main(int argc, char* argv[])
{
	// The inventory file
	ifstream InFile;
	// String for each line of inv. file
	string Line;
	// max # of vehicles in inventory
	#define DATABASE_SIZE (50)
	// Database that holds every vehicle & current date
	database TheDatabase;

	// Open the inventory file
	InFile.open("Inventory.txt");
	if (!InFile.is_open())
	{
		cout << "Error opening Inventory.txt" << endl;
		return -1;
	} // end if()

	// Read contents of file line by line
	// stop reading when databse full
	int NumVehicles = 0;
	while ((NumVehicles < DATABASE_SIZE) && getline(InFile, Line))
	{
		// String stream for parsing words
		istringstream Record(Line);
		// String to hold parsed thing
		string Field;
		// Strings to hold indiv. fields
		string Make, Model, Year, Color, EngineType, Capacity, Efficiency;

		// Get strings from line
		int FieldCount = 0;
		while (Record >> Field)
		{
			FieldCount++;
			switch (FieldCount)
			{
				case 1: { Make = Field; break; }
				case 2: { Model = Field; break; }
				case 3: { Year = Field; break; }
				case 4: { Color = Field; break; }
				case 5: { EngineType = Field; break; }
				case 6: { Capacity = Field; break; }
				case 7: { Efficiency = Field; break; }
			} // switch()
		} // end while()
		if (FieldCount != 7)
		{
			cout << "Error: Invalid record in Inventory.txt" << endl;
			cout << Line << endl;
			return -2;
		} // end if()

		// Year, Capacity, & Efficiency were read as strings, convert them to numbers using string streams
		// so they can be stored in the int and float data members of the vehicle objects
		int YearValue;
		float CapacityValue, EfficiencyValue;
		istringstream YearStream(Year);
		istringstream CapacityStream(Capacity);
		istringstream EfficiencyStream(Efficiency);
		YearStream >> YearValue;
		CapacityStream >> CapacityValue;
		EfficiencyStream >> EfficiencyValue;

		// Depending on the propulsion type, instantiate a gasVehicle or an electricVehicle object,
		// populate the fields, and add it to the database
		if (EngineType == "ICE")
		{
			// Instantiate a gas propulsion vehicle
			gasVehicle* NewGasVehicle = new gasVehicle;

			// Set the fields (setvehicleinfo is inherited)
			NewGasVehicle->SetVehicleInfo(Make, Model, YearValue, Color);
			NewGasVehicle->SetGasVehicleInfo(CapacityValue, EfficiencyValue);

			// Add the gas vehicle to the database (allowed because a gasVehicle "is" a vehicle)
			TheDatabase.addVehicle(NewGasVehicle);
		} // end if()
		else if (EngineType == "EV")
		{
			// Instantiate an electric propulsion vehicle 
			electricVehicle* NewElectricVehicle = new electricVehicle;

			// Set the fields (setvehicleinfo is inherited)
			NewElectricVehicle->SetVehicleInfo(Make, Model, YearValue, Color);
			NewElectricVehicle->SetElectricVehicleInfo(CapacityValue, EfficiencyValue);

			// Add the electric vehicle to database ( is relationship) 
			TheDatabase.addVehicle(NewElectricVehicle);
		} // end if() ... else if()
		else
		{
			cout << "Error! Unrecognized propulsion type." << endl;
			cout << Line << endl;
			return -3;
		} // end if()... else()

		// Increment the counter of the vehicles in the inventory
		NumVehicles++;
	} // end while()

	// Done w/ inventory file, close it
	InFile.close();
	cout << NumVehicles << " vehicles loaded from Inventory.txt" << endl;

	bool ExitRequested = false;
	do
	{
		char Command;
		// Prompt the user for the program option, showing current date
		cout << endl << "[Day " << TheDatabase.getCurrentDay() << "] Enter Command (? for help) >";
		cin >> Command;

		// Process the command
		switch (Command)
		{
			case '?': // Help Screen
			{
				cout << " ? = Display Help" << endl;
				cout << " A = Search by Make" << endl;
				cout << " O = Search by Model" << endl;
				cout << " Y = Search by Year" << endl;
				cout << " P = Search by Propulsion Type (ICE or EV)" << endl;
				cout << " C = Search by Color" << endl;
				cout << " R = Reserve a vehicle" << endl;
				cout << " I = Print the inventory (all vehicles)" << endl;
				cout << " F = Print vehicles with future reservations" << endl;
				cout << " U = Print vehicles without reservations (fully available)" << endl;
				cout << " N = Advance to the next day" << endl;
				cout << " Q = Quit / Exit the program" << endl;
				break;
			}
			case 'a': case 'A': // Search by Make
			{
				// Prompt the user for the search criteria
				string DesiredMake;
				cout << "Enter Make > ";
				cin >> DesiredMake;

				// Search database (print matches & # found)
				TheDatabase.searchMake(DesiredMake);
				break;
			} // end case 'a' or 'A'
			case 'o': case 'O': // Search by Model
			{
				// Prompt user for search criteria
				string DesiredModel;
				cout << "Enter Model > ";
				cin >> DesiredModel;

				// Search database (print matches & # found)
				TheDatabase.searchModel(DesiredModel);
				break;
			} // end case 'o' or 'O'
			case 'y': case 'Y': // Search by Year
			{
				// Prompt user for search criteria
				int DesiredYear;
				cout << "Enter Year > ";
				cin >> DesiredYear;

				// Search database (print matches & # found)
				TheDatabase.searchYear(DesiredYear);
				break;
			} // end case 'y' or 'Y'
			case 'p': case 'P': // Search by Propulsion Type
			{
				// Prompt user for search criteria
				string DesiredPropulsion;
				cout << "Enter Propulsion Type (ICE or EV) > ";
				cin >> DesiredPropulsion;

				// Search database (print matches & # found)
				TheDatabase.searchPropulsion(DesiredPropulsion);
				break;
			} // end case 'p' or 'P'
			case 'c': case 'C': // Search by Color
			{
				// Prompt user for search criteria
				string DesiredColor;
				cout << "Enter Color > ";
				cin >> DesiredColor;

				// Search database (print matches & # found)
				TheDatabase.searchColor(DesiredColor);
				break;
			} // end case 'c' or 'C'
			case 'r': case 'R': // Reserve a vehicle
			{
				// Prompt user for the vehicle # and day
				int VehicleNumber, ReserveDay;
				cout << "Enter vehicle number (shown by I or a search) > ";
				cin >> VehicleNumber;
				cout << "Today is day " << TheDatabase.getCurrentDay()
					<< ". Enter day to reserve > ";
				cin >> ReserveDay;

				// Ask database to make reservation, tell
				// user what happened based on return code
				int Result = TheDatabase.addReservation(VehicleNumber, ReserveDay);
				if (Result == 0)
				{
					cout << "Vehicle #" << VehicleNumber << " reserved for day "
						<< ReserveDay << "." << endl;
				} // end if()
				else if (Result == -1)
				{
					cout << "Error! There is no vehicle #" << VehicleNumber << "." << endl;
				} // end if...else if()
				else
				{
					cout << "Error! Reservation not allowed. The day must be after today,"
						<< endl << "the vehicle can't already be reserved that day, and a"
						<< endl << "vehicle can have at most 3 future reservations." << endl;
				} // end if...else()
				break;
			} // end case 'r' or 'R'
			case 'i': case 'I': // Print the inventory
			{
				TheDatabase.printAllVehicles();
				break;
			} // end case 'i' or 'I'
			case 'f': case 'F': // Print vehicles w/ future reservations
			{
				TheDatabase.printReservedVehicles();
				break;
			} // end case 'f' or 'F'
			case 'u': case 'U': // Print vehicles w/o reservations
			{
				TheDatabase.printUnreservedVehicles();
				break;
			} // end case 'u' or 'U'
			case 'n': case 'N': // Advance next day
			{
				TheDatabase.nextDay();
				cout << "The date is now day " << TheDatabase.getCurrentDay() << "." << endl;
				break;
			} // end case 'n' or 'N'
			case 'q': case 'Q': // Exit program
			{
				ExitRequested = true;
				break;
			} // end case 'q' or 'Q'
		} // end switch()
	} 
	// end do...while()
	while (!ExitRequested); 

	// No error possible
	return 0;
} // end main()
