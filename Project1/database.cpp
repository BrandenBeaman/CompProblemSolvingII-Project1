#include "database.h"
#include "vehicle.h"
#include "electricVehicle.h"
#include "gasVehicle.h"
#include <iostream>
#include <string>

database::database() {
	vehicle* inventory = {};
	invSize = 0;
	day = 0;
}

void database::nextDay(void) {
	day++;
}

int database::addVehicle(vehicle* vPnt) {
	if (invSize < 100) {
		inventory[invSize] = vPnt;
		invSize++;
		return 0;
	}
	return 1;
}

int database::addReservation(vehicle* vPnt, int resDay) {

	//search for vPnt in inventory
	for (int i = 0; i < invSize; i++) {
		if (inventory[i]->GetVehicleSpecs() == vPnt->GetVehicleSpecs()) {
			if (vPnt->AddReservation(resDay, day)) {
				return 0;
			}
			else return -2;
		}
	}

	//return -1 if vehicle not found in inventory
	return -1;

}

void database::printReservedVehicles(void) {
	for (int i = 0; i < invSize; i++) {
		if (inventory[i]->CheckReservationNumber() > 0) {
			std::cout << inventory[i]->GetVehicleSpecs() << std::endl;
		}
	}
}

int database::searchMake(std::string make) {
	int count = 0;
	for (int i = 0; i < invSize; i++) {
		//some getters pls
		//if(inventory->[i].getter
	}
	return count;
}