#include <iostream>
#include <string>
#include <sstream>
#include "electricVehicle.h"

using namespace std;

void CheckTest(string testName, bool passed)
{
    cout << testName << ": ";

    if (passed)
    {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }
}

int main()
{
    cout << "===== Electric Vehicle Unit Tests =====" << endl << endl;

    // Create a new electric vehicle.
    electricVehicle car;

    // Test constructor values.
    int year = -1;

    car.GetYear(year);

    CheckTest("Initial year test", year == 0);
    CheckTest("Initial reservation count test",
        car.CheckReservationNumber() == 0);

    // Test the initial electric vehicle values.
    ostringstream initialOutput;
    streambuf* originalOutput = cout.rdbuf(initialOutput.rdbuf());

    car.PrintVehicleInfo();

    cout.rdbuf(originalOutput);

    string initialInfo = initialOutput.str();

    CheckTest("Initial energy capacity test", initialInfo.find("Energy Capacity: 0.00") != string::npos);

    CheckTest("Initial efficiency test", initialInfo.find("Efficiency: 0.00") != string::npos);

    cout << endl;

    // Set the basic vehicle information.
    car.SetVehicleInfo("Tesla", "Model 3", 2025, "White");

    // Retrieve the stored information.
    string make;
    string model;
    string color;
    int storedYear = -1;

    car.GetMake(make);
    car.GetModel(model);
    car.GetColor(color);
    car.GetYear(storedYear);

    // Test the stored basic vehicle information.
    CheckTest("Make test", make == "Tesla");
    CheckTest("Model test", model == "Model 3");
    CheckTest("Year test", storedYear == 2025);
    CheckTest("Color test", color == "White");

    cout << endl;

    // Test the propulsion type.
    string propulsion;

    car.GetPropulsion(propulsion);

    CheckTest("Propulsion type test", propulsion == "EV");

    cout << endl;

    // Set the electric vehicle information.
    car.SetElectricVehicleInfo(75.0f, 4.0f);

    // Capture the printed vehicle information.
    ostringstream output;
    streambuf* savedOutput = cout.rdbuf(output.rdbuf());

    car.PrintVehicleInfo();

    cout.rdbuf(savedOutput);

    // Retrieve the captured text.
    string printedInfo = output.str();

    // Test energy capacity and efficiency.
    CheckTest("Energy capacity test", printedInfo.find("75.00") != string::npos);

    CheckTest("Efficiency test", printedInfo.find("4.00") != string::npos);

    // Test the printed basic vehicle information.
    CheckTest("Printed make test", printedInfo.find("Tesla") != string::npos);
    CheckTest("Printed model test", printedInfo.find("Model 3") != string::npos);
    CheckTest("Printed year test", printedInfo.find("2025") != string::npos);
    CheckTest("Printed color test", printedInfo.find("White") != string::npos);

    CheckTest("Printed propulsion type test", printedInfo.find("EV") != string::npos);

    cout << endl;

    // Update the electric vehicle information.
    car.SetElectricVehicleInfo(100.0f, 3.5f);

    ostringstream updatedOutput;
    streambuf* savedUpdatedOutput = cout.rdbuf(updatedOutput.rdbuf());

    car.PrintVehicleInfo();

    cout.rdbuf(savedUpdatedOutput);

    string updatedInfo = updatedOutput.str();

    CheckTest("Updated energy capacity test", updatedInfo.find("100.00") != string::npos);

    CheckTest("Updated efficiency test", updatedInfo.find("3.50") != string::npos);

    cout << endl;

    // Test the SetElectricVehicleInfo return value.
    int result1 = car.SetElectricVehicleInfo(75.0f, 4.0f);
    CheckTest("SetElectricVehicleInfo return value test", result1 == 0);

    // Test negative energy capacity.
    int result2 = car.SetElectricVehicleInfo(-10.0f, 4.0f);
    CheckTest("Negative energy capacity test", result2 == 0);

    // Test negative efficiency.
    int result3 = car.SetElectricVehicleInfo(75.0f, -5.0f);
    CheckTest("Negative efficiency test", result3 == 0);

    cout << endl;

    // Verify that negative values are stored and printed.
    car.SetElectricVehicleInfo(-10.0f, -25.0f);

    ostringstream negativeOutput;
    streambuf* savedNegativeOutput = cout.rdbuf(negativeOutput.rdbuf());
    car.PrintVehicleInfo();
    cout.rdbuf(savedNegativeOutput);

    string negativeInfo = negativeOutput.str();

    CheckTest("Negative energy capacity stored test", negativeInfo.find("-10.00") != string::npos);

    CheckTest("Negative efficiency stored test", negativeInfo.find("-25.00") != string::npos);

    cout << endl;

    // Test adding a valid reservation.
    bool result = car.AddReservation(3, 1);

    CheckTest("Valid reservation test", result == true);
    CheckTest("Reservation count after adding", car.CheckReservationNumber() == 1);

    // Test attempting to reserve the same day twice.
    bool duplicateResult = car.AddReservation(3, 1);

    CheckTest("Duplicate reservation test", duplicateResult == false);
    CheckTest("Count unchanged after duplicate", car.CheckReservationNumber() == 1);

    // Test reservations for the current day and a past day.
    bool todayResult = car.AddReservation(5, 5);
    CheckTest("Current day reservation test", todayResult == false);

    bool pastResult = car.AddReservation(4, 5);
    CheckTest("Past day reservation test", pastResult == false);

    CheckTest("Count unchanged after invalid dates", car.CheckReservationNumber() == 1);

    cout << endl;

    // Test the maximum of three reservations.
    electricVehicle limitTestCar;

    bool firstResult = limitTestCar.AddReservation(3, 1);
    bool secondResult = limitTestCar.AddReservation(4, 1);
    bool thirdResult = limitTestCar.AddReservation(5, 1);

    CheckTest("First reservation test", firstResult);
    CheckTest("Second reservation test", secondResult);
    CheckTest("Third reservation test", thirdResult);

    bool fourthResult = limitTestCar.AddReservation(6, 1);

    CheckTest("Fourth reservation rejected test", fourthResult == false);

    CheckTest("Maximum reservation count test", limitTestCar.CheckReservationNumber() == 3);

    // Check the stored reservation dates.
    int day1 = 0;
    int day2 = 0;
    int day3 = 0;

    limitTestCar.GetReservationDays(day1, day2, day3);

    CheckTest("First reservation day test", day1 == 3);
    CheckTest("Second reservation day test", day2 == 4);
    CheckTest("Third reservation day test", day3 == 5);

    cout << endl;

    // Test a vehicle with only one reservation.
    electricVehicle availableTestCar;

    availableTestCar.AddReservation(3, 1);

    availableTestCar.GetReservationDays(day1, day2, day3);

    CheckTest("Single reservation day test", day1 == 3);
    CheckTest("Unused second reservation slot test", day2 == 0);
    CheckTest("Unused third reservation slot test", day3 == 0);

    CheckTest("Reserved day detection test", car.CheckReservationDay(3) == true);

    CheckTest("Available day detection test", car.CheckReservationDay(4) == false);

    cout << endl;

    electricVehicle capacityTestCar;

    capacityTestCar.SetElectricVehicleInfo(75.0f, 4.0f);

    CheckTest("Zero energy capacity test", capacityTestCar.SetElectricVehicleInfo(0.0f, 0.0f) == 0);

    cout << endl << "===== Testing Complete =====" << endl;

    return 0;
}