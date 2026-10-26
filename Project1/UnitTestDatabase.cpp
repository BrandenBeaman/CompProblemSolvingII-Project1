#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "database.h"
#include "gasVehicle.h"
#include "electricVehicle.h"
#include "vehicle.h"

using namespace std;

// Prints whether an individual test passed or failed
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

    // --------------------------------------------------
    // 1. Create a database and fill its inventory
    // --------------------------------------------------

    database testDatabase;

    // Reserve enough space so pointers to our vehicles remain valid.
    vector<gasVehicle> testVehicles;
    testVehicles.reserve(101);

    cout << endl << "--- Adding Vehicles ---" << endl;

    for (int i = 0; i < 100; i++)
    {
        testVehicles.emplace_back();

        // Give the first vehicle unique information so we can search for it.
        if (i == 0)
        {
            testVehicles[i].SetVehicleInfo("TestMake", "TestModel", 2020, "Blue");
        }
        else
        {
            testVehicles[i].SetVehicleInfo("OtherMake", "OtherModel", 2021, "Red");
        }

        testVehicles[i].SetGasVehicleInfo(15.0, 30.0);

        int result = testDatabase.addVehicle(&testVehicles[i]);

        CheckTest("Add vehicle " + to_string(i + 1), result == 0);
    }

    // --------------------------------------------------
    // 2. Test the database inventory limit
    // --------------------------------------------------

    cout << endl << "--- Inventory Limit Tests ---" << endl;

    gasVehicle extraVehicle;

    extraVehicle.SetVehicleInfo("ExtraMake", "ExtraModel", 2022, "White");

    extraVehicle.SetGasVehicleInfo(12.0, 25.0);

    int extraResult = testDatabase.addVehicle(&extraVehicle);

    CheckTest("Adding vehicle when inventory is full", extraResult == 1);

    // --------------------------------------------------
    // 3. Test searching by vehicle information
    // --------------------------------------------------

    cout << endl << "--- Search Tests ---" << endl;

    // Capture printed search results so the console only shows test results.
    ostringstream searchOutput;
    streambuf* originalCout = cout.rdbuf(searchOutput.rdbuf());

    int makeCount = testDatabase.searchMake("TestMake");

    cout.rdbuf(originalCout);

    CheckTest("Search by make test", makeCount == 1);

    searchOutput.str("");
    searchOutput.clear();
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int modelCount = testDatabase.searchModel("TestModel");

    cout.rdbuf(originalCout);

    CheckTest("Search by model test", modelCount == 1);

    searchOutput.str("");
    searchOutput.clear();
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int yearCount = testDatabase.searchYear(2020);

    cout.rdbuf(originalCout);

    CheckTest("Search by year test", yearCount == 1);

    searchOutput.str("");
    searchOutput.clear();
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int colorCount = testDatabase.searchColor("Blue");

    cout.rdbuf(originalCout);

    CheckTest("Search by color test", colorCount == 1);

    searchOutput.str("");
    searchOutput.clear();
    originalCout = cout.rdbuf(searchOutput.rdbuf());

    int propulsionCount = testDatabase.searchPropulsion("ICE");

    cout.rdbuf(originalCout);

    CheckTest("Search by propulsion test", propulsionCount == 100);

    // --------------------------------------------------
    // 4. Test printing reserved and unreserved vehicles
    // --------------------------------------------------

    cout << endl << "--- Print Tests ---" << endl;

    ostringstream printOutput;
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printReservedVehicles();

    cout.rdbuf(originalCout);

    CheckTest("Print reserved vehicles when none are reserved", printOutput.str().empty());

    printOutput.str("");
    printOutput.clear();
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printUnreservedVehicles();

    cout.rdbuf(originalCout);

    CheckTest("Print unreserved vehicles test", printOutput.str().find("Vehicle Info:") != string::npos);

    // --------------------------------------------------
    // 5. Test adding reservations
    // --------------------------------------------------

    cout << endl << "--- Reservation Tests ---" << endl;

    // A reservation for the current day should be rejected.
    // The assignment specifies that the database starts on day 1.
    int currentDayResult = testDatabase.addReservation(
        &testVehicles[0], 1);

    CheckTest("Reservation for current day is rejected", currentDayResult == -2);

    // A reservation for a future day should succeed.
    int futureDayResult = testDatabase.addReservation(
        &testVehicles[0], 2);

    CheckTest("Valid future reservation test", futureDayResult == 0);

    // Adding the same reservation again should fail.
    int duplicateResult = testDatabase.addReservation(
        &testVehicles[0], 2);

    CheckTest("Duplicate reservation test", duplicateResult == -2);

    // A vehicle that is not in the database should not be reservable.
    gasVehicle missingVehicle;

    missingVehicle.SetVehicleInfo("MissingMake", "MissingModel", 2019, "Black");

    missingVehicle.SetGasVehicleInfo(10.0, 20.0);

    int missingResult = testDatabase.addReservation(&missingVehicle, 2);

    CheckTest("Reservation for vehicle not in database test", missingResult == -1);

    // --------------------------------------------------
    // 6. Check printing after a reservation
    // --------------------------------------------------

    cout << endl << "--- Updated Print Tests ---" << endl;

    printOutput.str("");
    printOutput.clear();
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printReservedVehicles();

    cout.rdbuf(originalCout);

    CheckTest("Print reserved vehicles after reservation", printOutput.str().find("Vehicle Info:") != string::npos);

    printOutput.str("");
    printOutput.clear();
    originalCout = cout.rdbuf(printOutput.rdbuf());

    testDatabase.printUnreservedVehicles();

    cout.rdbuf(originalCout);

    CheckTest("Print unreserved vehicles after reservation", printOutput.str().find("Vehicle Info:") != string::npos);

    // --------------------------------------------------
    // End of tests
    // --------------------------------------------------

    cout << endl << "===== Testing Complete =====" << endl;

    return 0;
}