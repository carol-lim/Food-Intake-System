#include <string>
#include <iostream>
using namespace std;

#include "Goal.h"

Goal::Goal()
{
	protein_perc = 20;
	carbs_perc = 50;
	fats_perc = 30;

	goal_id = 0; kcal_goal = 0;
	protein_gram = 0; carbs_gram = 0; fats_gram = 0;
}

Goal::~Goal()
{
}

string Goal::chooseFitGoal(int num)
{
	string fitGoal;

	switch (num)
	{
	case 1: fitGoal = "Gain";
		break;
	case 2: fitGoal = "Cut";
		break;
	case 3: fitGoal = "Maintain";
		break;
	}
	return fitGoal;
}

void Goal::enterFitGoal() {
	// Fitness Goal
	validation = false;
	while (true) {
		cout << "Fitness Goal: " <<
			endl << "1. Gain" <<
			endl << "2. Cut" <<
			endl << "3. Maintain" <<
			endl << "Choose 1/2/3: ";
		if (!(cin >> fitGoalOpt)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(fitGoalOpt, 1, 3);
			if (validation) break;
			else cout << "Invalid option. Please enter valid option." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
	fitness_goal = chooseFitGoal(fitGoalOpt);
}

void Goal::enterKcalGoal(BodyDetails* bd) {
	validation = false;
	while (true) {
		int tdee = bd->getTdee();
		int min = tdee - 1000;
		int max = tdee + 1000;

		cout << "Your TDEE is " << tdee << ", \nplease set your daily calories goal within "
			<< min << "~" << max << endl;
		cout << "Calories Goal: ";
		if (!(cin >> kcal_goal)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(kcal_goal, min, max);
			if (validation) break;
			else cout << "Invalid Calories value. Please enter valid Calories value." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
	//bd->weight = weight;
}

void Goal::enterProteinGoal() {
	validation = false;
	while (true) {
		cout << "Protein Goal (%): ";
		if (!(cin >> protein_perc)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(protein_perc, 1, 100);
			if (validation) break;
			else cout << "Invalid percentage. Please enter valid percentage." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
	//bd->weight = weight;
}

void Goal::enterCarbsGoal() {
	validation = false;
	while (true) {
		cout << "Carbohydrates Goal (%): ";
		if (!(cin >> carbs_perc)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(carbs_perc, 1, 100);
			if (validation) break;
			else cout << "Invalid percentage. Please enter valid percentage." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
	//bd->weight = weight;
}

void Goal::enterFatsGoal() {
	validation = false;
	while (true) {
		cout << "Fats Goal (%): ";
		if (!(cin >> fats_perc)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(fats_perc, 1, 100);
			if (validation) break;
			else cout << "Invalid percentage. Please enter valid percentage." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
	//bd->weight = weight;
}

template <class T>
bool Goal::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}

// setters
void Goal::setGoalId(int goal_id) {
	this->goal_id = goal_id;
}
void Goal::setKcalGoal(int kcal_goal) {
	this->kcal_goal = kcal_goal;
}
void Goal::setProtPerc(int protein_perc) {
	this->protein_perc = protein_perc;
}
void Goal::setCarbsPerc(int carbs_perc) {
	this->carbs_perc = carbs_perc;
}
void Goal::setFatsPerc(int fats_perc) {
	this->fats_perc = fats_perc;
}
void Goal::setProtGram(int protein_gram) {
	this->protein_gram = protein_gram;
}
void Goal::setCarbsGram(int carbs_gram) {
	this->carbs_gram = carbs_gram;
}
void Goal::setFatsGram(int fats_gram) {
	this->fats_gram = fats_gram;
}
void Goal::setFitGoal(string fitness_goal) {
	this->fitness_goal = fitness_goal;
}
void Goal::setDate(string date) {
	this->date = date;
}
// getters
int Goal::getGoalId() {
	return goal_id;
}
int Goal::getKcalGoal() {
	return kcal_goal;
}
int Goal::getProtPerc() {
	return protein_perc;
}
int Goal::getCarbsPerc() {
	return carbs_perc;
}
int Goal::getFatsPerc() {
	return fats_perc;
}
int Goal::getProtGram() {
	return protein_gram;
}
int Goal::getCarbsGram() {
	return carbs_gram;
}
int Goal::getFatsGram() {
	return fats_gram;
}
string Goal::getFitGoal() {
	return fitness_goal;
}
string Goal::getDate() {
	return date;
}