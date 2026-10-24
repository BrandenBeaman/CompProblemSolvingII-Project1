#include <string>
#include "vehicle.h"

using namespace std;

// Constructor to initialize primitive data members
vehicle::vehicle()
{
	Year = 0;
	NumberOfReservations = 0;

	// Initialize the ReservationDays array to 0
	for (int i = 0; i < 3; i++)
	{
		ReservationDays[i] = 0;
	}
}

// Method to set vehicle information sets user varibles to the Make, Model, Year and Color of the vehicle, returns 0 if successful
int vehicle::SetVehicleInfo(string userMake, string userModel, int userYear, string userColor)
{
	Make = userMake;
	Model = userModel;
	Year = userYear;
	Color = userColor;

	return 0;
}

// Method to check if a vehicle is reserved for a specific day, returns true if date is reserved and false if date is available
bool vehicle::CheckReservationDay(int day)
{
	for (int i = 0; i < NumberOfReservations; i++)
	{
		if (ReservationDays[i] == day)
		{
			return true; // Day is reserved
		}
	}
	return false; // Day is available
}


// Method to check number of resverations for a vehicle, returns number of reservations for the vehicle
int vehicle::CheckReservationNumber()
{
	return NumberOfReservations;
}

// Method to add a reservation for a specific day, only allowed if CheckReservationDay returns false, CheckReservationNumber returns a value less than 3 and Current Day is before Reservation Day, returns true if reservation was added and false if not
bool vehicle::AddReservation(int reservationDay, int currentDay)
{
	if (CheckReservationDay(reservationDay))
	{
		return false; // Day is already reserved
	}
	if (NumberOfReservations >= 3)
	{
		return false; // Maximum reservations reached
	}
	if (currentDay >= reservationDay)
	{
		return false; // Reservation day must be in the future
	}
	// Add the reservation
	ReservationDays[NumberOfReservations] = reservationDay;
	NumberOfReservations++;
	return true; // Reservation added successfully
}

// Method to remove past reservations, any reservation day that is less than the current day will be removed from the reservation days array and the number of reservations will be updated
void vehicle::RemovePastReservations(int currentDay)
{
	for (int i = 0; i < NumberOfReservations; i++)
	{
		if (ReservationDays[i] < currentDay)
		{
			// Shift remaining reservations left by one position to the left by copying the next reservation into the current position
			for (int j = i; j < NumberOfReservations - 1; j++)
			{
				ReservationDays[j] = ReservationDays[j + 1];
			}
			ReservationDays[NumberOfReservations - 1] = 0; // Clear the last reservation, the trailing copy 
			NumberOfReservations--; // number of reservations is reduced by 1
			i--; // Check the new reservation at this index, allows the to clear multiple past reservations in one call
		}
	}
}

// Method to get the reservation days for a vehicle, returns the reservation days in the parameters, if a reservation day is not set, it will return 0 for that day
void vehicle::GetReservationDays(int& userDay1, int& userDay2, int& userDay3)
{
	userDay1 = ReservationDays[0];
	userDay2 = ReservationDays[1];
	userDay3 = ReservationDays[2];
}

// Method to get vehicle information, the parameters are passed by reference and will be set to the vehicle's information
void vehicle::GetMake(string& userMake)
{
	userMake = Make;
}

// Method to get vehicle information, the parameters are passed by reference and will be set to the vehicle's information
void vehicle::GetModel(string& userModel)
{
	userModel = Model;
}

// Method to get vehicle information, the parameters are passed by reference and will be set to the vehicle's information
void vehicle::GetYear(int& userYear)
{
	userYear = Year;
}

// Method to get vehicle information, the parameters are passed by reference and will be set to the vehicle's information
void vehicle::GetColor(string& userColor)
{
	userColor = Color;
}



