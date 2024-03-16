#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "Goal.h"
#include "User.h"
#include "Login.h"
#include "Profile.h"
#include "UseDiary.h"
#include "BodyDetails.h"
#include "RegisterUser.h"

/// <summary>
/// Validate range of input
/// Reusable for option menu validation or data input to customized its maximum and minimum value 
/// </summary>
/// <typeparam name="T">Identifier for general type</typeparam>
/// <param name="input">User's input</param>
/// <param name="min">Minimum value</param>
/// <param name="max">Maximum value</param>
/// <returns></returns>
template <class T>
bool validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}

/// <summary>
/// System starts here
/// 3 options: Login, Register or Exit
/// If login success, the user main menu will be displayed
/// If login failed, back to main page
/// </summary>
/// <returns>0</returns>
int main() {
	
	// Declare variables
	int optMain;
	bool validation, end = false;

	// Display main page
	do {
		system("CLS");

		cout << "----------------------------------------------" << endl;
		cout << "------- Welcome to Food Intake System --------" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Reminder: \nThis system is for normal diet reference only."<< endl;
		cout << "Please consult with your physician if you \nencounter health problem." << endl << endl;
		cout << "----------------------------------------------" << endl;
		cout << endl;
		cout << "1. Login" << endl;
		cout << "2. Register" << endl;
		cout << "0. Exit" << endl;
		cout << endl;

		while (true) {
			cout << "Please enter your choice:";
			// User input and validate input
			if (!(cin >> optMain)) {
				cout << "Please enter number only." << endl << endl;
				system("pause");
				cout << endl;
			}
			else {
				// Validate input range
				validation = validateRange(optMain, 0,2);
				if (validation) break;
				else cout << "Invalid option. Please enter valid option." << endl << endl;
			}
			cin.clear();
			cin.ignore(10, '\n');
		}

		// Chosen menu option - Login
		if (optMain == 1) {

			system("CLS");

			// Instantiate objects
			User* user = new User();
			Goal* goal = new Goal();
			Login* login = new Login();
			UseDiary* ud = new UseDiary();
			Profile* profile = new Profile();
			BodyDetails* bd = new BodyDetails();

			// Invoke login module. Display main menu if login success
			if (login->login(user, bd, goal)) {
				while (true) {
					int menuOpt;
					while (true) {
						system("CLS");

						cout << "-------------------------------------------------------" << endl;
						cout << "\tWelcome back, " << user->name << endl;
						cout << "-------------------------------------------------------" << endl;
						cout << "1. Profile" << endl;
						cout << "2. Diary" << endl;
						cout << "0. Log Out" << endl;

						cout << "Please enter your choice: ";
						// User input and validate input
						if (!(cin >> menuOpt)) {
							cout << "Please enter number only." << endl << endl;
							system("pause");
							cout << endl;
						}
						else {
							// Validate input range
							validation = validateRange(optMain, 0, 2);
							if (validation) break;
							else cout << "Invalid option. Please enter valid option." << endl << endl;
						}
						cin.clear();
						cin.ignore(10, '\n');
					}

					// Invoke module correspond to option
					switch (menuOpt) {
					case 1:
						profile->profile(user, bd, goal);
						end = false;
						break;

					case 2:
						ud->useDiary(user, goal);
						end = false;
						break;

					case 0: 
						end = true;
						break;
					}
					if (end) break;
				}
			}
		}

		// Chosen menu option - Register
		else if (optMain == 2) {
			system("CLS");
			// Instantiate objects
			RegisterUser* registerUser = new RegisterUser();

			registerUser->registerUser();
		}

	} while (optMain != 0);
}