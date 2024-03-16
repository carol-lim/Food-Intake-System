#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <conio.h>
#include <ctime>

using namespace std;

#include "User.h"
#include "BodyDetails.h"

User::User() {
	name = ""; gender = ""; password = ""; email = "";
	
	validation = false;
}
User::~User() {

}

void User::enterName() {
	// Name
	string inputName = "";
	cout << "Name: ";
	getline(cin, inputName);
	cout << endl;
	this->name = inputName;
}

void User::enterGender() {
	// Gender
	while (true) {
		cout << "Gender (F/M): ";
		getline(cin, gender);
		cout << endl;

		validation = validateGender(gender);
		if (validation) break;
		else cout << "Invalid gender. Please enter valid gender (F/M)." << endl << endl;
		cin.clear();
		cin.ignore(10, '\n');
	}
	//user->gender = gender;
}

void User::enterYob( BodyDetails* bd) {
	// Gender
	while (true) {
		cout << "Year of birth (yyyy): ";
		if (!(cin >> yob)) {
			cout << "Please enter year in 4 digits only." << endl << endl;
			system("pause");
			cout << endl;
		}

		validation = validateYob(yob);
		if (validation) { 
			time_t t = time(0);
			tm* now = localtime(&t);
			int yearNow = now->tm_year + 1900;
			int x = yearNow - yob;
			bd->setAge(x);
			break;
		}
		else cout << "Invalid year of birth. Please enter valid year of birth." << endl << endl;
		cin.clear();
		cin.ignore(10, '\n');
	}
	//user->yob = yob;
	cout << endl;
}

void User::enterEmail() {
	// Email
	while (true) {
		cin.ignore(1, '\n');

		cout << "Email (example@gmail.com): ";
		getline(cin, email);
		cout << endl;

		validation = validateEmail(email);
		if (validation) break;
		else cout << "Invalid Email. Please enter valid email." << endl << endl;
		cin.clear();
		cin.ignore(10, '\n');
	}
	//user->email = email;
}

void User::enterPassword() {
	// Password
	while (true) {
		string inputPassword = "";
		cout << "Password must at least " <<
			endl << "8 characters," <<
			endl << "1 lower case alphabet," <<
			endl << "1 uppercase alphabet," <<
			endl << "a digit," <<
			endl << "a special character." <<
			endl << "Password: ";
		int ch;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b') {
				// Process a destructive backspace
				if (inputPassword.size() > 0) {
					inputPassword.erase(inputPassword.size() - 1, 1);
					cout << "\b \b";
				}
			}
			else {
				inputPassword.push_back(ch);
				cout << "*";
			}
		}

		//getline(cin, password);
		cout << endl;
		string retypePswd = "";
		// confirm password
		cout << "Re-type Password : ";
		int ch2;
		while ((ch2 = _getch()) != '\r') {
			if (ch2 == '\b') {
				// Process a destructive backspace
				if (retypePswd.size() > 0) {
					retypePswd.erase(retypePswd.size() - 1, 1);
					cout << "\b \b";
				}
			}
			else {
				retypePswd.push_back(ch2);
				cout << "*";
			}
		}

		cout << endl << endl;
		validation = validatePswd(inputPassword);

		if (validation && (retypePswd == inputPassword)) {
			password = inputPassword;
			break;
		}
		else if (retypePswd != inputPassword) cout << "Please enter same password." << endl << endl;
		else if (!validation) cout << "Please enter moderate / strong password." << endl << endl;

	}
	
}


/* Methods for validations of inputs*/

bool User::validateEmail(string input) {
	bool match;
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	match = regex_match(input, pattern);

	return match;
}

bool User::validateGender(string input) {
	bool match;
	if (input == "F" || input == "f" || input == "M" || input == "m") match = true;
	else match = false;

	return match;
}

bool User::validateYob(int input) {
	bool match;
	time_t t = time(0);
	tm* now = localtime(&t);
	int yearNow = now->tm_year + 1900;
	int min = yearNow - 100;
	int max = yearNow - 18;
	if (input >= min && input <= max) match = true;
	else match = false;

	return match;
}

template <class T>
bool User::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}

bool User::validatePswd(string& input) {
	size_t n = input.length();
	// Checking lower alphabet in string
	bool hasLower = false, hasUpper = false;
	bool hasDigit = false, specialChar = false;
	string normalChars = "abcdefghijklmnopqrstu" "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
	for (int i = 0; i < n; i++) {
		if (islower(input[i]))
			hasLower = true;
		if (isupper(input[i]))
			hasUpper = true;
		if (isdigit(input[i]))
			hasDigit = true;
		size_t special = input.find_first_not_of(normalChars);
		if (special != string::npos)
			specialChar = true;
	}
	// Strength of password
	cout << "Strength of password: ";
	if (hasLower && hasUpper && hasDigit && specialChar && (n >= 8)) {
		cout << "Strong" << endl << endl;
		return true;
	}
	else if ((hasLower || hasUpper) && hasDigit && (n >= 6)) {
		cout << "Moderate" << endl << endl;
		return true;
	}
	else {
		cout << "Weak" << endl << endl;
		return false;
	}
}
