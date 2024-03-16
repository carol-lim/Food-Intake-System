#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
using namespace std;

#include "User.h"
#include "Goal.h"
#include "Profile.h"
#include "UserManager.h"
#include "BodyDetails.h"
#include "GoalManager.h"
#include "Calculation.h"
#include "RegisterUser.h"
#include "BodyDetailsManager.h"

/// <summary>
/// Profile module
/// </summary>
/// <param name="user">Object of User</param>
/// <param name="bd">Object of BodyDetails</param>
/// <param name="goal">Object of Goal</param>
void Profile::profile(User* user, BodyDetails* bd, Goal* goal) {
	while (true) {
		while (true) {
			system("CLS");
			end = false;
			cout << "----------------------------------------------" << endl;
			cout << "\t" << user->name << "'s Profile" << endl ;
			cout << "----------------------------------------------" << endl;
			
			// Display all details
			displayUserDetails(user);
			displayCurrentBodyDetails(bd);
			displayCurrentGoals(goal);
		
			cout << "----------------------------------------------" << endl;
			cout << "---------------- Manage profile --------------" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "1. Change Password" << endl;
			cout << "2. Update Body Details" << endl;
			cout << "3. Update Fitnes & Daily Intake Goal" << endl;
			cout << "4. View Report" << endl;
			cout << "0. Back" << endl;
			cout << endl;

			cout << "Please enter your choice: " ;
			// User input and validate input
			if (!(cin >> menuOpt)) {
				cout << "Please enter number only." << endl << endl;
				system("pause");
				cout << endl;
			}
			else {
				// Validate input range
				validation = validateRange(menuOpt, 0, 4);
				if (validation) break;
				else cout << "Invalid option. Please enter valid option." << endl << endl;
			}
			cin.clear();
			cin.ignore(10, '\n');
		}

		// Invoke module correspond to option
		switch (menuOpt) {
			case 1:
				changePswd(user);
				end = false;
				break;

			case 2:
				updateBodyDetails(user, bd, goal);
				end = false;
				break;

			case 3:
				updateFitnessGoal(user, goal, bd);
				end = false;
				break;

			case 4:
				bd->weightGraph(user->user_id);
				end = false;
				break;

			case 0:
				end = true;
				break;
		}
		if (end) break;
	}
	return;
}

/// <summary>
/// Display User's Details
/// </summary>
/// <param name="user">Object of User</param>
void Profile::displayUserDetails(User* user) {
	cout << "------ User Details ------" << endl;
	cout << "User ID\t\t\t: " << user->user_id << endl;
	cout << "Name\t\t\t: " << user->name << endl;
	cout << "Gender\t\t\t: " << user->gender << endl;
	cout << "Year of Birth\t\t: " << user->yob << endl;
	cout << "Email\t\t\t: " << user->email << endl;
	cout << endl;
}

/// <summary>
/// Display user's current body details
/// </summary>
/// <param name="bd">Object of BodyDetails</param>
void Profile::displayCurrentBodyDetails(BodyDetails* bd) {
	cout << "------ Current Body Details ------" << endl;
	cout << "Age\t\t\t: " << bd->getAge() << endl;
	cout << "Height\t\t\t: " << bd->getHeight() << endl;
	cout << "Weight\t\t\t: " << bd->getWeight() << endl;
	cout << "Physical Activity Level : " << bd->getActLvl() << endl;
	cout << "TDEE\t\t\t: " << bd->getTdee() << endl;
	cout << endl;
	cout << "(Last Update: " << bd->getDate()<<")" << endl;
	cout << endl;
}

/// <summary>
/// Display user's current goals
/// </summary>
/// <param name="goal">Object of Goal</param>
void Profile::displayCurrentGoals(Goal* goal) {
	cout << "------ Current Daily Goals ------" << endl;
	cout << "Fitness Goal\t\t: " << goal->getFitGoal() << endl;
	cout << "Calories Goal\t\t: " << goal->getKcalGoal() << endl;
	cout << "Protein goal\t\t: " << goal->getProtGram() << "g" << " (" << goal->getProtPerc() << "%)" << endl;
	cout << "Carbohydrates goal\t: " << goal->getCarbsGram() << "g" << " (" << goal->getCarbsPerc() << "%)" << endl;
	cout << "Fats goal\t\t: " << goal->getFatsGram() << "g" << " (" << goal->getFatsPerc() << "%)" << endl;
	cout << endl;
	cout << "(Last Update: " << goal->getDate() << ")" << endl;
	cout << endl;
}

/// <summary>
/// Change Password
/// 1. User input old password
/// 2. User input new password
/// </summary>
/// <param name="user">Object of User</param>
void Profile::changePswd(User* user) {
	system("CLS");
	UserManager* userMng = new UserManager();
	
	bool validation, end = false;
	string oldPswd, newPswd;
	int failure = 0;

	cout << "----------------------------------------------" << endl;
	cout << "--------------- Change Password --------------" << endl;
	cout << "----------------------------------------------" << endl;

	// Enter old pswd
	while (true) {
		cout << "Old Password: ";
		int ch;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b') {
				// Process a destructive backspace
				if (oldPswd.size() > 0) {
					oldPswd.erase(oldPswd.size() - 1, 1);
					cout << "\b \b";
				}
			}

			else {
				oldPswd.push_back(ch);
				cout << "*";
			}
		}
		
		cout << endl;
		// Check password correctness
		if (oldPswd.compare(user->password) == 0) break;
		else cout << "Wrong password." << endl ;
		
		// Fail counter
		failure++;

		// If more than 3 failures, back 
		if (failure >= 3) {

			cout << "You have failed to enter old password for more than 3 times." << endl;
			cout << "Please try again later." << endl;
			system("pause");
			cout << endl;
			end = true;
			break;
		}
	}
	if (!end) {
		// Enter new password
		user->enterPassword();

		// Update new password to DB
		int status = userMng->updatePswd(user);
		
		// Display message - success or fail 
		cout << "**********************************************" << endl;
		if (status == 1) cout << "Password changed successfully." << endl;
		else cout << "Failed to change password." << endl;
		cout << "**********************************************" << endl;
		system("pause");
	}
}

/// <summary>
/// Update Body Details
/// Any update will affect the data of daily intake goals (calories, protein, carbs, fats)
/// Therefore, calculation is needed at the end after updates
/// </summary>
/// <param name="user">Object of User</param>
/// <param name="bd">Object of BodyDetails</param>
/// <param name="goal">Object of Goal</param>
void Profile::updateBodyDetails(User* user, BodyDetails* bd, Goal* goal) {
	system("CLS");
	Calculation* calc = new Calculation();
	GoalManager* goalManager = new GoalManager();
	BodyDetailsManager* bdManager = new BodyDetailsManager();
	
	while (true) {
		system("CLS");
		while (true) {
			end = false;

			// Display Current Body Details
			displayCurrentBodyDetails(bd);
			
			cout << "----------------------------------------------" << endl;
			cout << "------------ Update Body Details -------------" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "1. Year of Birth (Age)" << endl;
			cout << "2. Height" << endl;
			cout << "3. Weight" << endl;
			cout << "4. Physical Activity Level" << endl;
			cout << "5. Update All" << endl;
			cout << "0. Back" << endl;
			cout << endl;
			cout << "Please enter your choice: ";
			
			// User input and validate input
			if (!(cin >> menuOpt)) {
				cout << "Please enter number only." << endl << endl;
				system("pause");
				cout << endl;
			}
			else {
				// Validate input range
				validation = validateRange(menuOpt, 0, 5);
				if (validation) break;
				else cout << "Invalid option. Please enter valid option." << endl << endl;
			}
			cin.clear();
			cin.ignore(10, '\n');
		}

		// Invoke module correspond to option
		switch (menuOpt) {
		case 1:
			user->enterYob(bd);
			end = false;
			break;

		case 2:
			bd->enterHeight();
			end = false;
			break;

		case 3:
			bd->enterWeight();
			end = false;
			break;

		case 4:
			bd->enterActLvl();
			end = false;
			break;

		case 5:
			user->enterYob(bd);
			bd->enterHeight();
			bd->enterWeight();
			bd->enterActLvl();
			end = false;
			break;

		case 0:
			end = true;
			break;
		}

		if (!end) {
			// Current age = current year - YOB
			time_t t = time(0);
			tm* now = localtime(&t);
			int yearNow = now->tm_year + 1900;
			int x = yearNow - (user->yob);

			// Calculations
			bd->setAge(x);
			bd->setTdee(calc->calculateTDEE(user, bd));
			goal->setKcalGoal(calc->caloriesGoal(goal, bd));
			calc->macronutrientGoal(goal);

			// Add new body details, goals to DB
			int statusAddBd = bdManager->addBd(bd, user);
			int statusAddGoal = goalManager->addGoal(goal, user);

			// Display message - success or fail 
			cout << "**********************************************" << endl;
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
			cout << "**********************************************" << endl;
			system("pause");
		}
		else break;
	}
}

/// <summary>
/// Update Fitness Goal
/// 
/// Any update will affect the data of daily macronutrient intake goals (protein, carbs, fats)
/// Therefore, calculation is needed at the end after updates
/// 
/// The total percentage of macronutrient intake (protein, carbs, fats) should be 100%
/// Therefore, any update of macronutrient would affect another one
/// The input prompt will be loop until the total is 100%
/// </summary>
/// <param name="user">Object of User</param>
/// <param name="goal">Object of Goal</param>
/// <param name="bd">Object of BodyDetails</param>
void Profile::updateFitnessGoal(User* user, Goal* goal, BodyDetails* bd) {
	system("CLS");
	Calculation* calc = new Calculation();
	GoalManager* goalManager = new GoalManager();
	BodyDetailsManager* bdManager = new BodyDetailsManager();

	while (true) {
		system("CLS");
		while (true) {
			end = false;
			displayCurrentGoals(goal);
			cout << "----------------------------------------------" << endl;
			cout << "-------- Update Fitness/Intake Goals ---------" << endl;
			cout << "----------------------------------------------" << endl;
			cout << "1. Fitness Goal" << endl;
			cout << "2. Daily Calories Goal" << endl;
			cout << "3. Daily Macronutrient Goal" << endl;
			cout << "4. Update All" << endl;
			cout << "0. Back" << endl;
			cout << endl;
			cout << "Please enter your choice: ";

			// User input and validate input
			if (!(cin >> menuOpt)) {
				cout << "Please enter number only." << endl << endl;
				system("pause");
				cout << endl;
			}
			else {
				// Validate input range
				validation = validateRange(menuOpt, 0, 4);
				if (validation) break;
				else cout << "Invalid option. Please enter valid option." << endl << endl;
			}
			cin.clear();
			cin.ignore(10, '\n');
		}

		// Invoke module correspond to option
		switch (menuOpt) {
		case 1:
			goal->enterFitGoal();
			goal->setKcalGoal(calc->caloriesGoal(goal, bd));
			end = false;
			break;

		case 2:
			goal->enterKcalGoal(bd);
			end = false;
			break;
			
		case 3:
			while (true) {
				goal->enterProteinGoal();
				goal->enterCarbsGoal();
				goal->enterFatsGoal();
				int totalP = goal->getProtPerc() + goal->getCarbsPerc() + goal->getFatsPerc();
				if (totalP != 100) cout << "(The total percentage is " << totalP << "%, \n please make it 100% for a better measurement)" << endl;
				else break;
			}
			end = false;
			break;

		case 4:
			goal->enterFitGoal();
			goal->setKcalGoal(calc->caloriesGoal(goal, bd));
			goal->enterKcalGoal(bd);
			while (true) {
				goal->enterProteinGoal();
				goal->enterCarbsGoal();
				goal->enterFatsGoal();
				int totalP = goal->getProtPerc() + goal->getCarbsPerc() + goal->getFatsPerc();
				if (totalP != 100) cout << "(The total percentage is " << totalP << "%, \n please make it 100% for a better measurement)" << endl;
				else break;
			}
			end = false;
			break;

		case 0:
			end = true;
			break;
		}

		if (!end) {
			// Calculation
			calc->macronutrientGoal(goal);

			// Add new goal to DB
			int statusAddGoal = goalManager->addGoal(goal, user);

			// Display message - success or fail 
			cout << "**********************************************" << endl;
			if (statusAddGoal == 1) {
				cout << "\tGoal(s) updated successfully." << endl;
			}
			else cout << "\tFailed to add new goals" << endl;
			cout << "**********************************************" << endl;
			system("pause");
		}
		else break;
	}
}

/// <summary>
/// Validate range of input
/// Reusable for option menu validation or data input to customized its maximum and minimum value 
/// </summary>
/// <typeparam name="T">Identifier for general type</typeparam>
/// <param name="input">>User's input</param>
/// <param name="min">Minimum value</param>
/// <param name="max">Maximum value</param>
/// <returns></returns>
template <class T>
bool Profile::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}