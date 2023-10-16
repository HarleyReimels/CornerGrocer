// ProjectThree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Used for input and output
#include <fstream> // Used for reading files
#include <vector> // Used to create a variable size array
#include "foodAmount.h" // Useless at the moment
#include <map> // Used to map our values
#include <string>

using namespace std; // Used to reduce code


// Menu Option for the user
void menuOptions() {
    cout << "Welcome to the menu! Please enter the number for the option you would like." << endl;
    cout << "1: Enter a product name to search for it" << endl;
    cout << "2: Print all items and the amount for each item." << endl;
    cout << "3: Print all items displayed as a histogram." << endl;
    cout << "4: Exit Program." << endl;
}

// Main Program
int main()
{
    string requestedItem; // Item the user will be searching for
    string foodItem; // The string that is read in from the file
    ifstream dailyFood; // The file we are going to open
    vector<string> allFood; // Vector used to store values
    int i; // Used for incrementation
    int menuChoice; // Used to choose menu options
    map<string, int> foodDictionary; // Map of type string int, to display all relevent information
    ofstream dataFile("frequency.dat"); // Creates and open file

    cout << "Welcome to the Shopping program.\n\n";
    
    // Try to open file
    dailyFood.open("storeFood.txt");
    if (!dailyFood.is_open()) {
        cout << "Could not open storeFood.txt" << endl;
        return 1; // Indicates error
    }

 
    // Loops through the entire program until we reach EOF
    while (dailyFood.good()) {
        dailyFood >> foodItem; // Assign current item to variable FoodItem

        // If item is not currently in vector Allfood, it will be added
        if (find(allFood.begin(), allFood.end(), foodItem) == allFood.end()) {
            // Add food item to Vector
            allFood.push_back(foodItem);

            // Add food item to map, starting with 1
            foodDictionary.insert(pair<string, int>(foodItem, 1));
        }
        // If item is already in vector, we increment the number by 1
        foodDictionary[foodItem]++;
    }

    // Created a label as a jump point for goto
label:
    // Call menu function
    menuOptions();
    cout << "Enter your choice 1,2,3,4: ";
    // Get user input
    cin >> menuChoice;

    // Switch statement
    switch (menuChoice)
    {
        // If option 1 is chosen, we ask for input and perform a search
    case 1:
        cout << "Enter the item you are searching for: ";
        cin >> requestedItem;
        system("CLS");
        cout << "You searched for " << requestedItem << " we have found a total of " << foodDictionary[requestedItem] << ".\n" << endl;
        // Use goto to restart the loop
        goto label;
        break;
    case 2:
        system("CLS");
        // Print items and amount
        // Also writes to frequency.dat
        for (auto pair : foodDictionary) {
            cout << pair.first << ": " << pair.second << endl;
            dataFile << pair.first << " " << pair.second;
        }
        cout << endl;
        // Use goto to restart loop
        goto label;
        break;
    case 3:
        system("CLS");
        // Print item
        for (auto pair : foodDictionary) {
            cout << pair.first << " ";
            // Loops through the amount of item, printing a star each time
            for (i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
        cout << endl;
        // Restart loop
        goto label;
        break;
    case 4:
        // If 4 or anything is entered, program ends
        break;
    default:
        break;
    }
    // Close file
    dailyFood.close();
    dataFile.close();
}

