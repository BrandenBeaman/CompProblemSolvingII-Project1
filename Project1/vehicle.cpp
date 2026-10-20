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

int vehicle::SetVehicleInfo(string userMake, string userModel, int userYear, string userColor)
{
	Make = userMake;
	Model = userModel;
	Year = userYear;
	Color = userColor;

	return 0;
}

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

int vehicle::CheckReservationNumber()
{
	return NumberOfReservations;
}

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

void vehicle::GetReservationDays(int& userDay1, int& userDay2, int& userDay3)
{
	userDay1 = ReservationDays[0];
	userDay2 = ReservationDays[1];
	userDay3 = ReservationDays[2];
}

void vehicle::GetVehicleInfo(string& userMake, string& userModel, int& userYear, string& userColor)
{
	userMake = Make;
	userModel = Model;
	userYear = Year;
	userColor = Color;
}


