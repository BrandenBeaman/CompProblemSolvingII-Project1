#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "database.h"

using namespace std;

// This function displays whether a test passed or failed.
// testName describes what we are testing.
// passed is true if the expected result was received, and false otherwise.
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
    cout << "===== Database Unit Tests =====" << endl;

    // ==================================================
    // TEST 1: Create a database and add vehicles
    // ==================================================

    // Create a database object that will store our test vehicles.
    database testDatabase;

    // Create a vector to hold the vehicles used in our tests.
    // We reserve space for 101 vehicles so their addresses remain
    // stable when we pass pointers to the database.
    vector<gasVehicle> testVehicles;
    testVehicles.reserve(101);

    cout << endl << "--- Adding Vehicles ---" << endl;

    // Add 100 vehicles to test whether the database accepts vehicles
    // when there is still space available in its inventory.
    for (int i = 0; i < 100; i++)
    {
        // Create a new gas vehicle.
        testVehicles.emplace_back();

        // Give the first vehicle unique information.
        // We will use these values later when testing the search functions.
        if (i == 0)
        {
            testVehicles[i].SetVehicleInfo(
                "TestMake", "TestModel", 2020, "Blue");
        }
        else
        {
            // Give the remaining vehicles different information
            // so the search tests can distinguish the first vehicle.
            testVehicles[i].SetVehicleInfo(
                "OtherMake", "OtherModel", 2021, "Red");
        }

        // Set the gas vehicle's fuel capacity and efficiency.
        testVehicles[i].SetGasVehicleInfo(15.0, 30.0);

        // Add the vehicle to the database.
        // The address operator (&) passes a pointer to the vehicle.
        int result = testDatabase.addVehicle(&testVehicles[i]);

        // According to database.cpp, adding a vehicle should return 0
        // when successful.
        CheckTest(
            "Add vehicle " + to_string(i + 1),
            result == 0);
    }

    // ==================================================
    // TEST 2: Check the maximum inventory capacity
    // ==================================================

    cout << endl << "--- Inventory Limit Tests ---" << endl;

    // Create one additional vehicle after adding 100 vehicles.
    gasVehicle extraVehicle;

    extraVehicle.SetVehicleInfo(
        "ExtraMake", "ExtraModel", 2022, "White");

    extraVehicle.SetGasVehicleInfo(12.0, 25.0);

    // Attempt to add a vehicle when the database should be full.
    int extraResult = testDatabase.addVehicle(&extraVehicle);

    // The current implementation returns 1 when the inventory is full.
    // This test checks that the database rejects the extra vehicle.
    CheckTest(
        "Adding vehicle when inventory is full",
        extraResult == 1);

    // ==================================================
    // TEST 3: Search for vehicles by their information
    // ==================================================

    cout << endl << "--- Search Tests ---" << endl;

    // Search functions print information about matching vehicles.
    // Redirect cout into a string stream so that the vehicle information
    // does not clutter the test results.
    ostringstream searchOutput;
    streambuf* originalCout = cout.rdbuf(searchOutput.rdbuf());

    // Search for a vehicle by make.
    int makeCount = testDatabase.searchMake("TestMake");

    // Restore normal console output.
    cout.rdbuf(originalCout);

    // Only the first vehicle should have this make.
    CheckTest(
        "Search by make test",
        makeCount == 1);

    // Clear the captured output before the next search.
    searchOutput.str("");
    searchOutput.clear();

    // Redirect cout again while searching by model.
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int modelCount = testDatabase.searchModel("TestModel");

    cout.rdbuf(originalCout);

    // Only the first vehicle should have this model.
    CheckTest(
        "Search by model test",
        modelCount == 1);

    // Clear the captured output before the next search.
    searchOutput.str("");
    searchOutput.clear();

    // Search for a vehicle by its model year.
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int yearCount = testDatabase.searchYear(2020);

    cout.rdbuf(originalCout);

    // Only the first vehicle should have the year 2020.
    CheckTest(
        "Search by year test",
        yearCount == 1);

    // Clear the captured output before the next search.
    searchOutput.str("");
    searchOutput.clear();

    // Search for a vehicle by its color.
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int colorCount = testDatabase.searchColor("Blue");

    cout.rdbuf(originalCout);

    // Only the first vehicle should be blue.
    CheckTest(
        "Search by color test",
        colorCount == 1);

    // Clear the captured output before the next search.
    searchOutput.str("");
    searchOutput.clear();

    // Search for vehicles by propulsion type.
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int propulsionCount = testDatabase.searchPropulsion("ICE");

    cout.rdbuf(originalCout);

    // All 100 vehicles are gas vehicles, so the expected count is 100.
    // This assumes the gas vehicle class reports its propulsion as "ICE".
    CheckTest(
        "Search by propulsion test",
        propulsionCount == 100);

    // ==================================================
    // TEST 4: Print reserved and unreserved vehicles
    // ==================================================

    cout << endl << "--- Print Tests ---" << endl;

    // Capture the output of the reserved-vehicle printing function.
    ostringstream printOutput;
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printReservedVehicles();

    // Restore normal console output after the function finishes.
    cout.rdbuf(originalCout);

    // No reservations have been made yet.
    // Therefore, no vehicle information should be printed.
    CheckTest(
        "Print reserved vehicles when none are reserved",
        printOutput.str().empty());

    // Clear the captured output before testing unreserved vehicles.
    printOutput.str("");
    printOutput.clear();

    // Capture the output of the unreserved-vehicle printing function.
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printUnreservedVehicles();

    cout.rdbuf(originalCout);

    // All vehicles should be unreserved at this point.
    // Check that the function prints vehicle information.
    CheckTest(
        "Print unreserved vehicles test",
        printOutput.str().find("Vehicle Info:") != string::npos);

    // ==================================================
    // TEST 5: Test reservation behavior
    // ==================================================

    cout << endl << "--- Reservation Tests ---" << endl;

    // Test a reservation for day 1.
    // The assignment specifies that the database starts on day 1,
    // so a reservation for the current day should be rejected.
    int currentDayResult = testDatabase.addReservation(
        &testVehicles[0], 1);

    // A reservation failure should return -2.
    CheckTest(
        "Reservation for current day is rejected",
        currentDayResult == -2);

    // Test a reservation for day 2.
    // If the database starts on day 1, day 2 is a future day.
    int futureDayResult = testDatabase.addReservation(
        &testVehicles[0], 2);

    // A successful reservation should return 0.
    CheckTest(
        "Valid future reservation test",
        futureDayResult == 0);

    // Try to reserve the same vehicle for day 2 again.
    // The database should reject duplicate reservations.
    int duplicateResult = testDatabase.addReservation(
        &testVehicles[0], 2);

    // A duplicate reservation should return -2.
    CheckTest(
        "Duplicate reservation test",
        duplicateResult == -2);

    // Create a vehicle that has not been added to the database.
    gasVehicle missingVehicle;

    missingVehicle.SetVehicleInfo(
        "MissingMake", "MissingModel", 2019, "Black");

    missingVehicle.SetGasVehicleInfo(10.0, 20.0);

    // Attempt to reserve the vehicle even though it is not in the database.
    int missingResult = testDatabase.addReservation(
        &missingVehicle, 2);

    // The database should return -1 when it cannot find a matching vehicle.
    CheckTest(
        "Reservation for vehicle not in database test",
        missingResult == -1);

    // ==================================================
    // TEST 6: Check printing after making a reservation
    // ==================================================

    cout << endl << "--- Updated Print Tests ---" << endl;

    // Clear the previous captured output.
    printOutput.str("");
    printOutput.clear();

    // Capture the output after the reservation has been made.
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printReservedVehicles();

    cout.rdbuf(originalCout);

    // At least one vehicle should now be reserved,
    // so vehicle information should be printed.
    CheckTest(
        "Print reserved vehicles after reservation",
        printOutput.str().find("Vehicle Info:") != string::npos);

    // Clear the captured output before testing unreserved vehicles.
    printOutput.str("");
    printOutput.clear();

    // Capture the output of the unreserved-vehicle function again.
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printUnreservedVehicles();

    cout.rdbuf(originalCout);

    // Other vehicles remain unreserved.
    // Check that the function still prints vehicle information.
    CheckTest(
        "Print unreserved vehicles after reservation",
        printOutput.str().find("Vehicle Info:") != string::npos);

    // ==================================================
    // END OF TESTS
    // ==================================================

    cout << endl << "===== Testing Complete =====" << endl;

    return 0;
}
