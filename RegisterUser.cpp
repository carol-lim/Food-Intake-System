#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <regex>
#include <stdio.h>
#include <conio.h>
#include <ctime>
using namespace std;

#include "User.h"
#include "Goal.h"
#include "Profile.h"
#include "Calculation.h"
#include "GoalManager.h"
#include "UserManager.h"
#include "BodyDetails.h"
#include "RegisterUser.h"
#include "LoginManager.h"
#include "BodyDetailsManager.h"

/// <summary>
/// Register module
/// </summary>
/// <param name="user">Object of User</param>
void RegisterUser::registerUser() {
	cin.ignore(1, '\n');

	// Instantiate objects
	User* user = new User();
	Goal* goal = new Goal();
	Profile* profile = new Profile();
	BodyDetails* bd = new BodyDetails();
	Calculation* calc = new Calculation();
	UserManager* userManager = new UserManager();
	GoalManager* goalManager = new GoalManager();
	LoginManager* loginManager = new LoginManager();
	BodyDetailsManager* bdManager = new BodyDetailsManager();
	
	cout << "----------------------------------------------" << endl;
	cout << "---------------- Registration ----------------" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "Reminder: \nThis system is only suitable for adult\n \t(18 year-old & above)" << endl;
	cout << "----------------------------------------------" << endl;
	
	// User inputs
	user->enterName();
	user->enterGender();
	user->enterYob(bd);
		// Input email
	while (true) {
		user->enterEmail();
		
		// Check email existance
		bool cEmail = loginManager->checkEmail(user);
		
		// Email not found
		if (!cEmail) break;

		// Email exists
		else {
			cout << "Email exist already. Please enter another email." << endl;
			system("pause");
			cout << endl;

		}
	}
	user->enterPassword();
	bd->enterHeight();
	bd->enterWeight();
	bd->enterActLvl();
	goal->enterFitGoal();

	//// Current age = current year - YOB
	//time_t t = time(0);
	//tm* now = localtime(&t);
	//int yearNow = now->tm_year + 1900;
	//int x = yearNow - (user->yob);

	// Calculations
	//bd->setAge(x);
	bd->setTdee(calc->calculateTDEE(user, bd));
	goal->setKcalGoal(calc->caloriesGoal(goal, bd));
	calc->macronutrientGoal(goal);

	// Add new user, body details, goals to DB
	int statusAddUser = userManager->addUser(user);
	int statusAddBd = bdManager->addBd(bd, user);
	int statusAddGoal = goalManager->addGoal(goal,user);
	
	// Display message - success or fail 
	cout << "**********************************************" << endl;
	if (statusAddUser == 1 && statusAddBd == 1 && statusAddGoal == 1) {
		system("CLS");
		cout << "\tRegistered Successfully" << endl;
		cout << "**********************************************" << endl;
		
		// Display all details
		profile->displayUserDetails(user);
		profile->displayCurrentBodyDetails(bd);
		profile->displayCurrentGoals(goal);

	}
	else if (statusAddUser != 1) {
		cout << " Fail to register: Failed to add new user" << endl << endl;
	}
	else if (statusAddBd != 1) {
		cout << " Fail to register: Failed to add new body details" << endl << endl;
	}
	else if (statusAddGoal != 1) {
		cout << " Fail to register: Failed to add new goal" << endl << endl;
	}
	cout << "**********************************************" << endl;

	system("pause");
}