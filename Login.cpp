#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
using namespace std;

#include "User.h"
#include "Goal.h"
#include "Login.h"
#include "UserManager.h"
#include "BodyDetails.h"
#include "GoalManager.h"
#include "Calculation.h"
#include "LoginManager.h"
#include "BodyDetailsManager.h"

/// <summary>
/// Login module
/// </summary>
/// <param name="user">Object of User</param>
/// <param name="bodyDetails">Object of BodyDetails</param>
/// <param name="goal">Object of Goal</param>
/// <returns>login status</returns>
bool Login::login(User* user, BodyDetails* bodyDetails, Goal* goal) {

	system("CLS");
	cin.ignore(1, '\n');
	
	// Instantiate objects
	Calculation* calc = new Calculation();
	//UserManager* userManager = new UserManager();
	GoalManager* goalManager = new GoalManager();
	LoginManager* loginManager = new LoginManager();
	BodyDetailsManager* bdManager = new BodyDetailsManager();

	// Declare variables
	string passwordLogin ="", emailLogin="";
	int idFailed = 0, pswdFailed = 0;
	bool loginStatus = false, cId = false, cEmail = false, cPswd = false;
	
	cout << "----------------------------------------------" << endl;
	cout << "------------------- Login --------------------" << endl;
	cout << "----------------------------------------------" << endl;

	// Loop - email and password input
	while (true) {

		// Input - email
		while (true) {
			emailLogin = "";
			user->enterEmail();

			// Check email existence 
			cEmail = loginManager->checkEmail(user);
			
			// Email exists
			if (cEmail) break;

			// Email not found
			else {
				cout << "Invalid email. Please try again." << endl;
				system("pause");
				cout << endl;

				// Fail counter
				idFailed++;
			}

			// If more than 3 failures, back to main screen
			if (idFailed >= 3) {
				cout << "You have failed to login for more than 3 times." << endl;
				cout << "Please try again later." << endl;
				system("pause");
				cout << endl;

				return loginStatus = false;
			}
		}

		// Input - password
		while (true) {
			int ch;
			passwordLogin = "";
			cout << "Password: ";
			
			// Instant changing character into *
			while ((ch = _getch()) != '\r') {
				if (ch == '\b') {
					// Process a destructive backspace
					if (passwordLogin.size() > 0) {
						passwordLogin.erase(passwordLogin.size() - 1, 1);
						cout << "\b \b";
					}
				}
				else {
					passwordLogin.push_back(ch);
					cout << "*";
				}
			}
			cout << endl;

			// Check password correctness
			cPswd = loginManager->checkPswd(user, passwordLogin);
			
			// Password correct
			if (cPswd) {
				// Get user's current details
				bdManager->getCurrentBd(user->user_id, bodyDetails);
				goalManager->getCurrentGoal(user->user_id, goal);

				// Current age = current year - YOB
				time_t t = time(0);
				tm* now = localtime(&t);
				int yearNow = now->tm_year + 1900;
				int x = yearNow - (user->yob);

				// Stored age vs Current age. Update age if different
				if (bodyDetails->getAge() != x) {
					// Update age
					bodyDetails->setAge(x);

					// Calculations
					bodyDetails->setTdee(calc->calculateTDEE(user, bodyDetails));
					goal->setKcalGoal(calc->caloriesGoal(goal, bodyDetails));
					calc->macronutrientGoal(goal);

					// Update to DB
					int statusAddBd = bdManager->addBd(bodyDetails, user);
					int statusAddGoal = goalManager->addGoal(goal, user);

					// Display message - success or fail 
					cout << "**********************************************************" << endl;
					cout << "\tNew year, new age (" << x << "), time to update." << endl;
					if (statusAddBd == 1 && statusAddGoal == 1) {
						cout << "\tBody detail(s) updated successfully." << endl;
						cout << "\t(Successfully update body details and goals.)" << endl;
					}
					else if (statusAddBd != 1) {
						cout << "\tFailed to add new body details" << endl;
					}
					else if (statusAddGoal != 1) {
						cout << "\tFailed to add new goals" << endl;
					}
					cout << "**********************************************************" << endl;
					system("pause");
				}

				// Display message - login success
				cout << "Login Success" << endl;
				system("pause"); 

				return loginStatus = true;
			}

			// Password wrong
			else {
				cout << "Invalid Password. Please try again." << endl;
				system("pause"); 
				cout << endl;
				
				// Fail counter
				pswdFailed++;
			}

			// If more than 3 failures, back to main screen
			if (pswdFailed >= 3) {

				cout << "You have failed to login for more than 3 times." << endl;
				cout << "Please try again later." << endl;
				system("pause");
				cout << endl;

				return loginStatus = false;
			}
		}
	}
}