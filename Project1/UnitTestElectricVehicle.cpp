#include <iostream>
#include <string>
#include <sstream>

#include "electricVehicle.h"

using namespace std;

// This function prints whether a test passed or failed.
// testName describes the test being performed.
// passed is true if the actual result matches the expected result.
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
    cout << "===== Electric Vehicle Unit Tests =====" << endl;

    // ==================================================
    // TEST 1: Constructor and default values
    // ==================================================

    // Create an electric vehicle using its default constructor.
    electricVehicle car;

    // Retrieve the vehicle's default make, model, year, and color.
    string make, model, color;
    int year = -1;

    car.GetMake(make);
    car.GetModel(model);
    car.GetYear(year);
    car.GetColor(color);

    // The base vehicle constructor should initialize the year to 0.
    CheckTest(
        "Default year test",
        year == 0);

    // The default strings should be empty.
    CheckTest(
        "Default make test",
        make.empty());

    CheckTest(
        "Default model test",
        model.empty());

    CheckTest(
        "Default color test",
        color.empty());

    // ==================================================
    // TEST 2: Set and retrieve inherited vehicle information
    // ==================================================

    // Set the common vehicle information inherited from vehicle.
    car.SetVehicleInfo("Tesla", "Model 3", 2024, "White");

    // Retrieve the information after setting it.
    car.GetMake(make);
    car.GetModel(model);
    car.GetYear(year);
    car.GetColor(color);

    // Check that each getter returns the information we assigned.
    CheckTest(
        "Set and get make test",
        make == "Tesla");

    CheckTest(
        "Set and get model test",
        model == "Model 3");

    CheckTest(
        "Set and get year test",
        year == 2024);

    CheckTest(
        "Set and get color test",
        color == "White");

    // ==================================================
    // TEST 3: Electric propulsion type
    // ==================================================

    // Retrieve the propulsion type reported by the electric vehicle.
    string propulsion;

    car.GetPropulsion(propulsion);

    // The electric vehicle class initializes PropulsionType to "EV".
    CheckTest(
        "Electric propulsion type test",
        propulsion == "EV");

    // ==================================================
    // TEST 4: Electric vehicle information and printed output
    // ==================================================

    // Set the electric vehicle's energy capacity and efficiency.
    car.SetElectricVehicleInfo(75.0, 4.0);

    // Capture the printed output so we can examine it without
    // displaying the entire vehicle report in the console.
    ostringstream capturedOutput;
    streambuf* originalCout = cout.rdbuf(capturedOutput.rdbuf());

    // Print the vehicle's information.
    car.PrintVehicleInfo();

    // Restore normal console output.
    cout.rdbuf(originalCout);

    // Store the captured output in a string for testing.
    string output = capturedOutput.str();

    // Check that the printed report includes the vehicle's make.
    CheckTest(
        "Print make test",
        output.find("Tesla") != string::npos);

    // Check that the printed report includes the model.
    CheckTest(
        "Print model test",
        output.find("Model 3") != string::npos);

    // Check that the printed report includes the year.
    CheckTest(
        "Print year test",
        output.find("2024") != string::npos);

    // Check that the printed report includes the color.
    CheckTest(
        "Print color test",
        output.find("White") != string::npos);

    // Check that the printed report identifies the vehicle as an EV.
    CheckTest(
        "Print propulsion test",
        output.find("EV") != string::npos);

    // Check that the printed report includes the energy capacity.
    CheckTest(
        "Print energy capacity test",
        output.find("75.00") != string::npos);

    // Check that the printed report includes the electric efficiency.
    CheckTest(
        "Print efficiency test",
        output.find("4.00") != string::npos);

    // ==================================================
    // TEST 5: Set electric vehicle information
    // ==================================================

    cout << endl << "--- Electric Vehicle Information Tests ---" << endl;

    // Change the energy capacity and efficiency to new values.
    int setResult = car.SetElectricVehicleInfo(90.0, 5.0);

    // The current implementation returns 0 from SetElectricVehicleInfo.
    CheckTest(
        "Set electric vehicle information return value test",
        setResult == 0);

    // Capture the printed report after changing the electric information.
    capturedOutput.str("");
    capturedOutput.clear();

    originalCout = cout.rdbuf(capturedOutput.rdbuf());

    car.PrintVehicleInfo();

    cout.rdbuf(originalCout);

    output = capturedOutput.str();

    // Check that the updated energy capacity appears in the report.
    CheckTest(
        "Updated energy capacity test",
        output.find("90.00") != string::npos);

    // Check that the updated efficiency appears in the report.
    CheckTest(
        "Updated efficiency test",
        output.find("5.00") != string::npos);

    // ==================================================
    // TEST 6: Negative electric vehicle values
    // ==================================================

    // Test how the current implementation handles negative values.
    // The implementation shown in electricVehicle.cpp accepts them
    // without validation, so these tests reflect that behavior.
    int negativeResult = car.SetElectricVehicleInfo(-10.0, -2.0);

    // The setter currently returns 0 even when the values are negative.
    CheckTest(
        "Negative electric values return value test",
        negativeResult == 0);

    // Capture the report to verify that the negative values were stored.
    capturedOutput.str("");
    capturedOutput.clear();

    originalCout = cout.rdbuf(capturedOutput.rdbuf());

    car.PrintVehicleInfo();

    cout.rdbuf(originalCout);

    output = capturedOutput.str();

    // These checks document the current implementation's behavior.
    // They do not mean negative capacity or efficiency is desirable.
    CheckTest(
        "Negative energy capacity storage test",
        output.find("-10.00") != string::npos);

    CheckTest(
        "Negative efficiency storage test",
        output.find("-2.00") != string::npos);

    // ==================================================
    // TEST 7: Reservation behavior inherited from vehicle
    // ==================================================

    cout << endl << "--- Reservation Tests ---" << endl;

    // Create a separate vehicle so reservation tests do not interfere
    // with the electric information tests above.
    electricVehicle limitTestCar;

    // A newly constructed vehicle should have no reservations.
    CheckTest(
        "Initial reservation count test",
        limitTestCar.CheckReservationNumber() == 0);

    // The first reservation is for a future day.
    bool firstReservation = limitTestCar.AddReservation(5, 1);

    CheckTest(
        "Add first reservation test",
        firstReservation == true);

    // A reservation for the same day should be rejected.
    bool duplicateReservation = limitTestCar.AddReservation(5, 1);

    CheckTest(
        "Duplicate reservation test",
        duplicateReservation == false);

    // A reservation for the current day should be rejected.
    bool currentDayReservation = limitTestCar.AddReservation(1, 1);

    CheckTest(
        "Current day reservation test",
        currentDayReservation == false);

    // Add two more reservations to reach the maximum of three.
    bool secondReservation = limitTestCar.AddReservation(6, 1);
    bool thirdReservation = limitTestCar.AddReservation(7, 1);

    CheckTest(
        "Second reservation test",
        secondReservation == true);

    CheckTest(
        "Third reservation test",
        thirdReservation == true);

    // A fourth reservation should be rejected because the vehicle
    // is already holding the maximum of three reservations.
    bool fourthReservation = limitTestCar.AddReservation(8, 1);

    CheckTest(
        "Maximum reservation limit test",
        fourthReservation == false);

    // Confirm that the vehicle has exactly three reservations.
    CheckTest(
        "Final reservation count test",
        limitTestCar.CheckReservationNumber() == 3);

    // ==================================================
    // TEST 8: Retrieve reservation days
    // ==================================================

    // Retrieve all three reservation days.
    int day1 = 0;
    int day2 = 0;
    int day3 = 0;

    limitTestCar.GetReservationDays(day1, day2, day3);

    // Check that the stored reservation days match what we added.
    CheckTest(
        "First reservation day test",
        day1 == 5);

    CheckTest(
        "Second reservation day test",
        day2 == 6);

    CheckTest(
        "Third reservation day test",
        day3 == 7);

    // ==================================================
    // TEST 9: A separate vehicle starts with no reservations
    // ==================================================

    // Create another vehicle to confirm that reservations made to one
    // vehicle do not affect a different vehicle.
    electricVehicle availableTestCar;

    CheckTest(
        "Separate vehicle reservation count test",
        availableTestCar.CheckReservationNumber() == 0);

    // ==================================================
    // END OF TESTS
    // ==================================================

    cout << endl << "===== Testing Complete =====" << endl;

    return 0;
}
