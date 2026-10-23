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

int database::addReservation(vehicle* v1pnt, int resDay) {
	std::string tempStr1, tempStr2;
	int tempInt1, tempInt2;
	//search for vPnt in inventory
	for (auto& v2ref : inventory) {
		//check propulsion
		v1pnt->GetPropulsion(tempStr1, 0.0, 0.0);
		v2ref->GetPropulsion(tempStr2, 0.0, 0.0);
		if (tempStr1 == tempStr2) {
			//check make
			v1pnt->GetMake(tempStr1);
			v2ref->GetMake(tempStr2);
			if (tempStr1 == tempStr2) {
				//check model
				v1pnt->GetModel(tempStr1);
				v2ref->GetModel(tempStr2);
				if (tempStr1 == tempStr2) {
					//check year
					v1pnt->GetYear(tempInt1);
					v2ref->GetYear(tempInt2);
					if (tempInt1 == tempInt2) {
						//check color
						v1pnt->GetColor(tempStr1);
						v2ref->GetColor(tempStr2);
						if (tempStr1 == tempStr2) {
							//if everything matches
							// add reservation to the vehicle in the inventory
							// return 0 for success
							if (v2ref->AddReservation(resDay, day)) {
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
	for (auto vRef : inventory) {
		if (vRef->CheckReservationNumber() > 0) {
			vRef->PrintVehicleInfo();
		}
	}
}

void database::printUnreservedVehicles(void) {
	std::string vMake, vModel, vColor, vProp;
	int vYear;
	float vEff, vCap;
	//iterate through inventory and print if has reservations
	for (auto vRef : inventory) {
		if (vRef->CheckReservationNumber() == 0) {
			vRef->PrintVehicleInfo();
		}
	}
}

int database::searchMake(std::string make) {
	int count = 0;
	std::string vMake;
	for (auto vRef : inventory) {
		vRef->GetMake(vMake);
		if (vMake == make) {
			count++;
			vRef->PrintVehicleInfo();
		}
	}
	std::cout << "/n/n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchModel(std::string model){
	int count = 0;
	std::string vModel;
	for (auto vRef : inventory) {
		vRef->GetModel(vModel);
		if (vModel == model) {
			count++;
			vRef->PrintVehicleInfo();
		}
	}
	std::cout << "/n/n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchYear(int year){
	int count = 0;
	int vYear;
	for (auto vRef : inventory) {
		vRef->GetYear(vYear);
		if (vYear == year) {
			count++;
			vRef->PrintVehicleInfo();
		}
	}
	std::cout << "/n/n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchPropulsion(std::string propulsion) {
	int count = 0;
	std::string vProp;
	for (auto vRef : inventory) {
		vRef->GetPropulsion(vProp);
		if (vProp == propulsion) {
			count++;
			vRef->PrintVehicleInfo();
		}
	}
	std::cout << "/n/n" << count << " vehicles found." << std::endl;
	return count;
}

int database::searchColor(std::string color) {
	int count = 0;
	std::string vColor;
	for (auto vRef : inventory) {
		vRef->GetColor(vColor);
		if (vColor == color) {
			count++;
			vRef->PrintVehicleInfo();
		}
	}
	std::cout << "/n/n" << count << " vehicles found." << std::endl;
	return count;
}