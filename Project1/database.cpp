#include "database.h"
#include "vehicle.h"
#include "electricVehicle.h"
#include "gasVehicle.h"
#include <iostream>
#include <string>

//default constructor creates an empty database with no vehicles and sets the date to day 0
database::database() {
	vehicle* inventory = {};
	invSize = 0;
	day = 0;
}

void database::nextDay(void) {
	day++;
}

int database::getCurrentDay(void) {
	return day;
}

int database::addVehicle(vehicle* vPnt) {
	if (invSize < 100) {
		inventory[invSize] = vPnt;
		invSize++;
		return 0;
	}
	return 1;
}

int database::addReservation(vehicle* v1pnt, int resDay) {
	std::string tempStr1, tempStr2;
	int tempInt1, tempInt2;
	//search for vPnt in inventory
	for (int i = 0; i < invSize; i++) {
		//check propulsion
		v1pnt->GetPropulsion(tempStr1);
		inventory[i]->GetPropulsion(tempStr2);
		if (tempStr1 == tempStr2) {
			//check make
			v1pnt->GetMake(tempStr1);
			inventory[i]->GetMake(tempStr2);
			if (tempStr1 == tempStr2) {
				//check model
				v1pnt->GetModel(tempStr1);
				inventory[i]->GetModel(tempStr2);
				if (tempStr1 == tempStr2) {
					//check year
					v1pnt->GetYear(tempInt1);
					inventory[i]->GetYear(tempInt2);
					if (tempInt1 == tempInt2) {
						//check color
						v1pnt->GetColor(tempStr1);
						inventory[i]->GetColor(tempStr2);
						if (tempStr1 == tempStr2) {
							//if everything matches
							// add reservation to the vehicle in the inventory
							// return 0 for success
							if (inventory[i]->AddReservation(resDay, day)) {
								return 0;
							}
							//return -2 for failed reservation
							else return -2;
						}

					}
				}
			}
		}
	}
	//return -1 for failed search
	return -1;

}

void database::printReservedVehicles(void) {
	std::string vMake, vModel, vColor, vProp;
	int vYear;
	float vEff, vCap;
	//iterate through inventory and print if has reservations
	for (int i = 0; i < invSize; i++) {
		if (inventory[i]->CheckReservationNumber() > 0) {
			inventory[i]->PrintVehicleInfo();
		}
	}
}

void database::printUnreservedVehicles(void) {
	std::string vMake, vModel, vColor, vProp;
	int vYear;
	float vEff, vCap;
	//iterate through inventory and print if has reservations
	for (int i = 0; i < invSize; i++) {
		if (inventory[i]->CheckReservationNumber() == 0) {
			inventory[i]->PrintVehicleInfo();
		}
	}
}

int database::searchMake(std::string make) {
	int count = 0;
	std::string vMake;
	for (int i = 0; i < invSize; i++) {
		inventory[i]->GetMake(vMake);
		if (vMake == make) {
			count++;
			inventory[i]->PrintVehicleInfo();
		}
	}
	std::cout << "\n\n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchModel(std::string model){
	int count = 0;
	std::string vModel;
	for (int i = 0; i < invSize; i++) {
		inventory[i]->GetModel(vModel);
		if (vModel == model) {
			count++;
			inventory[i]->PrintVehicleInfo();
		}
	}
	std::cout << "\n\n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchYear(int year){
	int count = 0;
	int vYear;
	for (int i = 0; i < invSize; i++) {
		inventory[i]->GetYear(vYear);
		if (vYear == year) {
			count++;
			inventory[i]->PrintVehicleInfo();
		}
	}
	std::cout << "\n\n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchPropulsion(std::string propulsion) {
	int count = 0;
	std::string vProp;
	for (int i = 0; i < invSize; i++) {
		inventory[i]->GetPropulsion(vProp);
		if (vProp == propulsion) {
			count++;
			inventory[i]->PrintVehicleInfo();
		}
	}
	std::cout << "\n\n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchColor(std::string color) {
	int count = 0;
	std::string vColor;
	for (int i = 0; i < invSize; i++) {
		inventory[i]->GetColor(vColor);
		if (vColor == color) {
			count++;
			inventory[i]->PrintVehicleInfo();
		}
	}
	std::cout << "\n\n" << count << " vehicles found." << std::endl;
	return count;
}


int database::printAllVehicles(void) {
	//print all vehicles in the inventory then return 1
	for (int i = 0; i < invSize; i++) {
		inventory[i]->PrintVehicleInfo();
	}
	return 1;
}