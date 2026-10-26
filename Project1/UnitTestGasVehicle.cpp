#include <iostream>
#include <string>
#include <sstream>
#include "gasVehicle.h"

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
    cout << "===== Gas Vehicle Unit Tests =====" << endl << endl;

    // Create a new gas vehicle.
    gasVehicle car;

    // Test constructor values.
    int year = -1;

    car.GetYear(year);

    CheckTest("Initial year test", year == 0);

    CheckTest("Initial reservation count test", car.CheckReservationNumber() == 0);

    cout << endl;

    // Set the basic vehicle information.
    car.SetVehicleInfo("Toyota", "Camry", 2024, "Blue");

    // Retrieve the stored information.
    string make;
    string model;
    string color;
    int storedYear = -1;

    car.GetMake(make);
    car.GetModel(model);
    car.GetColor(color);
    car.GetYear(storedYear);

    // Test the stored information.
    CheckTest("Make test", make == "Toyota");
    CheckTest("Model test", model == "Camry");
    CheckTest("Year test", storedYear == 2024);
    CheckTest("Color test", color == "Blue");

    cout << endl;

    // Test the propulsion type.
    string propulsion;

    car.GetPropulsion(propulsion);

    CheckTest("Propulsion type test", propulsion == "ICE");

    // Set the gas vehicle information for 15 gal and 30 mpg
    car.SetGasVehicleInfo(15.0f, 30.0f);

    // Capture the printed output
    ostringstream output;
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());
    car.PrintVehicleInfo();
    cout.rdbuf(originalOutput);

    // Retrieve the captured text
    string printedInfo = output.str();

    // Test fuel capacity and efficiency
    CheckTest("Fuel capacity test", printedInfo.find("15.00") != string::npos);
    CheckTest("Fuel efficiency test", printedInfo.find("30.00") != string::npos);

    cout << endl;

    // Second test for gas vehicle info, 20 gal and 25 mpg
    car.SetGasVehicleInfo(20.0f, 25.0f);

    ostringstream updatedOutput;
    streambuf* newOutput = cout.rdbuf(updatedOutput.rdbuf());
    car.PrintVehicleInfo();
    cout.rdbuf(newOutput);

    string updatedInfo = updatedOutput.str();

    CheckTest("Updated fuel capacity test", updatedInfo.find("20.00") != string::npos);

    CheckTest("Updated fuel efficiency test", updatedInfo.find("25.00") != string::npos);

    cout << endl;

    int result2 = car.SetGasVehicleInfo(20.0f, 25.0f);
    CheckTest("SetGasVehicleInfo return value test", result2 == 0);
    //returns 0 for success

    int result3 = car.SetGasVehicleInfo(-10.0f, 25.0f);
    CheckTest("Negative fuel capacity test", result3 == 0);

    int result4 = car.SetGasVehicleInfo(20.0f, -5.0f);
    CheckTest("Negative fuel efficiency test", result4 == 0);

    cout << endl;

    // Third test for gas info, -10 gal and -25 mpg
    car.SetGasVehicleInfo(-10.0f, -25.0f);

    ostringstream secondUpdatedOutput;
    streambuf* secondNewOutput = cout.rdbuf(secondUpdatedOutput.rdbuf());
    car.PrintVehicleInfo();
    cout.rdbuf(secondNewOutput);

    string secondUpdatedInfo = secondUpdatedOutput.str();

    CheckTest("Second Updated fuel capacity test", secondUpdatedInfo.find("-10.00") != string::npos);

    CheckTest("Second Updated fuel efficiency test", secondUpdatedInfo.find("-25.00") != string::npos);

    cout << endl;

    // Test the printed basic vehicle information.
    CheckTest("Printed make test", printedInfo.find("Toyota") != string::npos);

    CheckTest("Printed model test", printedInfo.find("Camry") != string::npos);

    CheckTest("Printed year test", printedInfo.find("2024") != string::npos);

    CheckTest("Printed color test", printedInfo.find("Blue") != string::npos);

    cout << endl;

    // Test adding a valid reservation.
    bool result = car.AddReservation(3, 1);

    CheckTest("Valid reservation test", result == true);
    CheckTest("Reservation count after adding", car.CheckReservationNumber() == 1);

    // Test attempting to reserve the same day twice.
    bool duplicateResult = car.AddReservation(3, 1);

    CheckTest("Duplicate reservation test", duplicateResult == false);
    CheckTest("Count unchaged after duplicate", car.CheckReservationNumber() == 1);

    bool todayResult = car.AddReservation(5, 5);
    CheckTest("Current day reservation test", todayResult == false);

    bool pastResult = car.AddReservation(4, 5);
    CheckTest("Past day reservation test", pastResult == false);
    CheckTest("Count unchanged after invalid dates", car.CheckReservationNumber() == 1);

    // Create a separate vehicle for the reservation limit tests
    gasVehicle limitTestCar;

    bool firstResult = limitTestCar.AddReservation(3, 1);
    bool secondResult = limitTestCar.AddReservation(4, 1);
    bool thirdResult = limitTestCar.AddReservation(5, 1);
    CheckTest("First reservation test", firstResult);
    CheckTest("Second reservation test", secondResult);
    CheckTest("Third reservation test", thirdResult);

    bool fourthResult = limitTestCar.AddReservation(6, 1);

    CheckTest("Fourth reservation rejected test", fourthResult == false);
    CheckTest("Maximum reservation count test", limitTestCar.CheckReservationNumber() == 3);

    int day1 = 0;
    int day2 = 0;
    int day3 = 0;

    limitTestCar.GetReservationDays(day1, day2, day3);
    CheckTest("First reservation day test", day1 == 3);
    CheckTest("Second reservation day test", day2 == 4);
    CheckTest("Third reservation day test", day3 == 5);

    cout << endl;

    // Test another car with just one reservation date
    gasVehicle availableTestCar;
    availableTestCar.AddReservation(3, 1);

    availableTestCar.GetReservationDays(day1, day2, day3);
    CheckTest("First reservation day test", day1 == 3);
    CheckTest("Second reservation day test", day2 == 0);
    CheckTest("Third reservation day test", day3 == 0);


    cout << endl << "===== Testing Complete =====" << endl;

    return 0;
}