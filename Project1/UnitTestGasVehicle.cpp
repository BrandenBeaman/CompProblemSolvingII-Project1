#include <iostream>
#include <string>
#include <sstream>

#include "gasVehicle.h"

using namespace std;

// This function displays whether a test passed or failed.
// testName describes what the test is checking.
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
    cout << "===== Gas Vehicle Unit Tests =====" << endl << endl;

    // ==================================================
    // TEST 1: Constructor and default values
    // ==================================================

    // Create a new gas vehicle using its default constructor.
    gasVehicle car;

    // Retrieve the vehicle's default year.
    int year = -1;

    car.GetYear(year);

    // The vehicle constructor should initialize the year to 0.
    CheckTest("Initial year test", year == 0);

    // A newly created vehicle should have no reservations.
    CheckTest(
        "Initial reservation count test",
        car.CheckReservationNumber() == 0);

    cout << endl;

    // ==================================================
    // TEST 2: Set and retrieve basic vehicle information
    // ==================================================

    // Set the basic information inherited from the vehicle class.
    car.SetVehicleInfo("Toyota", "Camry", 2024, "Blue");

    // Create variables to store the information retrieved by the getters.
    string make;
    string model;
    string color;
    int storedYear = -1;

    // Retrieve the information stored in the vehicle object.
    car.GetMake(make);
    car.GetModel(model);
    car.GetColor(color);
    car.GetYear(storedYear);

    // Check that each getter returns the correct information.
    CheckTest("Make test", make == "Toyota");
    CheckTest("Model test", model == "Camry");
    CheckTest("Year test", storedYear == 2024);
    CheckTest("Color test", color == "Blue");

    cout << endl;

    // ==================================================
    // TEST 3: Check the vehicle's propulsion type
    // ==================================================

    // Retrieve the propulsion type reported by the gas vehicle.
    string propulsion;

    car.GetPropulsion(propulsion);

    // Gas vehicles are expected to report "ICE"
    // (internal combustion engine).
    CheckTest("Propulsion type test", propulsion == "ICE");

    // ==================================================
    // TEST 4: Set and print fuel capacity and efficiency
    // ==================================================

    // Set the fuel capacity to 15 gallons and fuel efficiency to 30 mpg.
    car.SetGasVehicleInfo(15.0f, 30.0f);

    // Capture the printed output so we can test its contents
    // without displaying the entire vehicle report in the console.
    ostringstream output;
    streambuf* originalOutput = cout.rdbuf(output.rdbuf());

    // Print the vehicle information.
    car.PrintVehicleInfo();

    // Restore normal console output.
    cout.rdbuf(originalOutput);

    // Convert the captured output into a string.
    string printedInfo = output.str();

    // Check that the printed report includes the correct fuel capacity
    // and fuel efficiency.
    CheckTest(
        "Fuel capacity test",
        printedInfo.find("15.00") != string::npos);

    CheckTest(
        "Fuel efficiency test",
        printedInfo.find("30.00") != string::npos);

    cout << endl;

    // ==================================================
    // TEST 5: Update fuel capacity and efficiency
    // ==================================================

    // Change the fuel capacity to 20 gallons and efficiency to 25 mpg.
    car.SetGasVehicleInfo(20.0f, 25.0f);

    // Capture the output again to check whether the updated values
    // are displayed by PrintVehicleInfo().
    ostringstream updatedOutput;
    streambuf* newOutput = cout.rdbuf(updatedOutput.rdbuf());

    car.PrintVehicleInfo();

    // Restore normal console output.
    cout.rdbuf(newOutput);

    // Store the updated report in a string.
    string updatedInfo = updatedOutput.str();

    // Check that the new fuel capacity and efficiency appear in the report.
    CheckTest(
        "Updated fuel capacity test",
        updatedInfo.find("20.00") != string::npos);

    CheckTest(
        "Updated fuel efficiency test",
        updatedInfo.find("25.00") != string::npos);

    cout << endl;

    // ==================================================
    // TEST 6: Check setter return values and negative inputs
    // ==================================================

    // Set valid fuel capacity and efficiency values again.
    // This test checks the return value of SetGasVehicleInfo().
    int result2 = car.SetGasVehicleInfo(20.0f, 25.0f);

    // The current implementation returns 1 for valid values.
    CheckTest(
        "SetGasVehicleInfo return value test",
        result2 == 1);

    // Try setting a negative fuel capacity.
    int result3 = car.SetGasVehicleInfo(-10.0f, 25.0f);

    // The current implementation returns 0 for a negative capacity.
    CheckTest(
        "Negative fuel capacity test",
        result3 == 0);

    // Try setting a negative fuel efficiency.
    int result4 = car.SetGasVehicleInfo(20.0f, -5.0f);

    // The current implementation returns 0 for negative efficiency.
    CheckTest(
        "Negative fuel efficiency test",
        result4 == 0);

    cout << endl;

    // ==================================================
    // TEST 7: Check whether negative values are stored and printed
    // ==================================================

    // Set both fuel capacity and efficiency to negative values.
    // This checks the actual behavior of the current implementation.
    car.SetGasVehicleInfo(-10.0f, -25.0f);

    // Capture the vehicle report so we can check the displayed values.
    ostringstream secondUpdatedOutput;
    streambuf* secondNewOutput = cout.rdbuf(secondUpdatedOutput.rdbuf());

    car.PrintVehicleInfo();

    // Restore normal console output.
    cout.rdbuf(secondNewOutput);

    // Store the captured report.
    string secondUpdatedInfo = secondUpdatedOutput.str();

    // Check whether the negative fuel capacity is displayed.
    // This documents the current implementation's behavior.
    CheckTest(
        "Second Updated fuel capacity test",
        secondUpdatedInfo.find("-10.00") != string::npos);

    // Check whether the negative fuel efficiency is displayed.
    CheckTest(
        "Second Updated fuel efficiency test",
        secondUpdatedInfo.find("-25.00") != string::npos);

    cout << endl;

    // ==================================================
    // TEST 8: Check basic vehicle information in printed output
    // ==================================================

    // The first captured report was generated when the vehicle's
    // basic information was Toyota, Camry, 2024, and Blue.
    // Check that all four pieces of information appeared in that report.
    CheckTest(
        "Printed make test",
        printedInfo.find("Toyota") != string::npos);

    CheckTest(
        "Printed model test",
        printedInfo.find("Camry") != string::npos);

    CheckTest(
        "Printed year test",
        printedInfo.find("2024") != string::npos);

    CheckTest(
        "Printed color test",
        printedInfo.find("Blue") != string::npos);

    cout << endl;

    // ==================================================
    // TEST 9: Add valid reservations and reject duplicates
    // ==================================================

    // Add a reservation for day 3 when the current day is day 1.
    bool result = car.AddReservation(3, 1);

    // A future reservation should be accepted.
    CheckTest("Valid reservation test", result == true);

    // Check that the reservation count increased to one.
    CheckTest(
        "Reservation count after adding",
        car.CheckReservationNumber() == 1);

    // Attempt to reserve day 3 again.
    bool duplicateResult = car.AddReservation(3, 1);

    // The same day should not be reserved twice for one vehicle.
    CheckTest("Duplicate reservation test", duplicateResult == false);

    // A failed duplicate reservation should not change the count.
    CheckTest(
        "Count unchanged after duplicate",
        car.CheckReservationNumber() == 1);

    // ==================================================
    // TEST 10: Reject reservations for the current and past days
    // ==================================================

    // Attempt to reserve day 5 when the current day is also day 5.
    bool todayResult = car.AddReservation(5, 5);

    // A reservation for the current day should be rejected.
    CheckTest("Current day reservation test", todayResult == false);

    // Attempt to reserve day 4 when the current day is day 5.
    bool pastResult = car.AddReservation(4, 5);

    // A reservation for a past day should be rejected.
    CheckTest("Past day reservation test", pastResult == false);

    // Neither invalid reservation should change the existing count.
    CheckTest(
        "Count unchanged after invalid dates",
        car.CheckReservationNumber() == 1);

    // ==================================================
    // TEST 11: Check the maximum number of reservations
    // ==================================================

    // Create a separate vehicle so these tests start with zero reservations.
    gasVehicle limitTestCar;

    // Add three different future reservations.
    bool firstResult = limitTestCar.AddReservation(3, 1);
    bool secondResult = limitTestCar.AddReservation(4, 1);
    bool thirdResult = limitTestCar.AddReservation(5, 1);

    // Each of the first three reservations should succeed.
    CheckTest("First reservation test", firstResult);
    CheckTest("Second reservation test", secondResult);
    CheckTest("Third reservation test", thirdResult);

    // Try to add a fourth reservation.
    bool fourthResult = limitTestCar.AddReservation(6, 1);

    // The vehicle should reject a fourth reservation because
    // the maximum allowed number is three.
    CheckTest("Fourth reservation rejected test", fourthResult == false);

    // Confirm that the vehicle still has exactly three reservations.
    CheckTest(
        "Maximum reservation count test",
        limitTestCar.CheckReservationNumber() == 3);

    // ==================================================
    // TEST 12: Retrieve all three reservation days
    // ==================================================

    // Create variables that will receive the stored reservation days.
    int day1 = 0;
    int day2 = 0;
    int day3 = 0;

    // Retrieve all three reservation dates from the vehicle.
    limitTestCar.GetReservationDays(day1, day2, day3);

    // Check that the dates match the three reservations we added.
    CheckTest("First reservation day test", day1 == 3);
    CheckTest("Second reservation day test", day2 == 4);
    CheckTest("Third reservation day test", day3 == 5);

    cout << endl;

    // ==================================================
    // TEST 13: Check unused reservation slots
    // ==================================================

    // Create another vehicle for a separate reservation test.
    gasVehicle availableTestCar;

    // Give this vehicle only one reservation.
    availableTestCar.AddReservation(3, 1);

    // Retrieve all three reservation slots.
    availableTestCar.GetReservationDays(day1, day2, day3);

    // The first slot should contain day 3.
    CheckTest("First reservation day test", day1 == 3);

    // The other two slots should remain at their default value of 0
    // because no reservations have been added to those slots.
    CheckTest("Second reservation day test", day2 == 0);
    CheckTest("Third reservation day test", day3 == 0);

    cout << endl << "===== Testing Complete =====" << endl;

    return 0;
}
