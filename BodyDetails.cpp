#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "BodyDetails.h"
#include "BodyDetailsManager.h"

BodyDetails::BodyDetails() {
	bd_id = 0;
	tdee = 0;
	actLvlOpt = 0;
	height = 0.0;
	weight = 0.0;
	act_level = "";
	date = "";
	validation = false;
}
BodyDetails::~BodyDetails() {

}

/// <summary>
/// Translate the input from int into string
/// </summary>
/// <param name="num">Selected option</param>
/// <returns>string of activity level</returns>
string BodyDetails::chooseActLvl(int num) {
	string actLevel;

	switch (num) {
	case 1: actLevel = "Sedentary";
		break;
	case 2: actLevel = "Lightly Active";
		break;
	case 3: actLevel = "Moderately Active";
		break;
	case 4: actLevel = "Very Active";
		break;
	case 5: actLevel = "Extremely Active";
		break;
	}

	return actLevel;
}

void BodyDetails::enterHeight() {
	validation = false;
	while (true) {
		cout << "Height in cm (100-200): ";
		if (!(cin >> height)) {
			cout << "Please enter decimal only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(height, 100.0, 200.0);
			if (validation) break;
			else cout << "Invalid height. Please enter valid height." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}

void BodyDetails::enterWeight() {
	validation = false;
	while (true) {
		cout << "Weight in kg (30-200): ";
		if (!(cin >> weight)) {
			cout << "Please enter decimal only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(weight, 30.0, 200.0);
			if (validation) break;
			else { 
				cout << "Invalid height. Please enter valid height." << endl << endl;
				if (weight > 200.0)
					cout << "The weight is not suitable for using this system." << endl;
					cout << "Please consult with your physician if you have health problem." << endl << endl;
			}
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}

void BodyDetails::enterActLvl() {
	validation = false;
	while (true) {
		cout << "Physical Activity Level: " <<
			endl << "1. Sedentary (little to no exercise + work a desk job)" <<
			endl << "2. Lightly Active (light exercise 1-3 days/week)" <<
			endl << "3. Moderately Active (moderate exercise 3-5 days/week)" <<
			endl << "4. Very Active (heavy exercise 6-7 days/week)" <<
			endl << "5. Extremely Active (very heavy exercise, hard labor job, training 2x/day)" <<
			endl << "Choose 1/2/3/4/5: ";
		if (!(cin >> actLvlOpt)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(actLvlOpt, 1, 5);
			if (validation) break;
			else cout << "Invalid option. Please enter valid option." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
	act_level = chooseActLvl(actLvlOpt);
}

/// <summary>
/// Generate weight fluctuation bar graph report
/// y-axis: weights
/// x-axis: dates
/// (Source: http://www.cpp.re/forum/beginner/199986/)
/// </summary>
/// <param name="user_id">User ID</param>
void BodyDetails::weightGraph(int user_id) {
	system("CLS");

	// Get user's recorded weights
	BodyDetailsManager* bdm = new BodyDetailsManager();
	vector<double> vector1 = bdm->getWeightVector(user_id);
	vector<string> vector2 = bdm->getDateVector(user_id);

	// Generate x-axis legend
	string xlegend = "      ";
	for (int i=0; i < vector1.size(); i++) {
		xlegend.append(vector2[i]);
		xlegend.append("  ");
	}

	// Set spaces between bars
	auto max0 = vector1.size() * 12; 
	for (int i = 0; i < max0; i += 2) {
		vector1.insert(vector1.begin() + i, vector1.at(i));
		i += 2;
		vector1.insert(vector1.begin() + i, 2, 0);
		i += 2;
		vector1.insert(vector1.begin() + i, 2, 0);
		i += 2;
		vector1.insert(vector1.begin() + i, 2, 0);
		i += 2;
		vector1.insert(vector1.begin() + i, 2, 0);
		i += 2;
		vector1.insert(vector1.begin() + i, 2, 0);
	}

	// Add space in front of first x-axis value
	vector1.insert(vector1.begin(), 5, 0);

	cout << "----------------------------------------------" << endl;
	cout << "--------- Weight Fluctuation Report ----------" << endl;
	cout << "----------------------------------------------" << endl;
	cout << endl << endl << "  Weight" << endl;
	
	// Finds the largest value in all of the elements within the vector
	int max1 = *max_element(vector1.begin(), vector1.end());
	int max2 = *max_element(vector1.begin(), vector1.end());

	// Loops through the rows and columns, outputs to the console one character at a time.
	// Outer loop resets the line (endl) and de-increments max2.
	// Inner loop outputs the row one character at a time, it does this by using max2 to control
	// which character columns get printed as * and which get printed as spaces.
	// max2 is set to the largest value in the vector, then it's de-incremented each iteration.
	// if vector[j] is larger than max2 it prints an *, otherwise it prints a space.
	for (int i = 0; i < max1; i++) {
		cout << right << setw(5) << max1 - i;
		for (int j = 0; j < vector1.size(); j++) {
			if (vector1.at(j) >= max2) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}
		max2--;
		cout << endl;
		if (max2 == 29) break;
	}

	// Display x-axis legend
	cout << xlegend << "-->Date"<<endl << endl << endl;
	cout << "Back: " << endl;
	system("pause");

}

template <class T>
bool BodyDetails::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}

void BodyDetails::setTdee(int tdee) {
	this->tdee = tdee;
}
void BodyDetails::setAge(int age) {
	this->age = age;
}
void BodyDetails::setHeight(double height) {
	this->height = height;
}
void BodyDetails::setWeight(double weight) {
	this->weight = weight;
}
void BodyDetails::setActLvl(string act_level) {
	this->act_level = act_level;
}
void BodyDetails::setBdId(int bd_id) {
	this->bd_id = bd_id;
}
void BodyDetails::setDate(string date) {
	this->date = date;
}

int BodyDetails::getTdee() {
	return tdee;
}
int BodyDetails::getAge() {
	return age;
}
double BodyDetails::getHeight() {
	return height;
}
double BodyDetails::getWeight() {
	return weight;
}
string BodyDetails::getActLvl() {
	return act_level;
}
string BodyDetails::getDate() {
	return date;
}