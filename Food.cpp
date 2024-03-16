#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "Food.h"
#include "FoodManager.h"

//Food::Food() {
//	food_id = 0; kcal = 0; created_by = 0; last_updated_by = 0;
//	food_name = ""; created_date = ""; last_updated_date = "";
//	serving_size = 0.0;  protein = 0.0;  carbs = 0.0; fats = 0.0;
//	validation = false;
//}
//Food::~Food() {
//
//}

void Food::displayFoodDetails(vector<Food*> food) {

	for (int i = 0; i < food.size(); i++) {
		cout << "#" << food[i]->food_id << endl;
		cout << "Food\t\t: " << food[i]->food_name << endl;
		cout << "Serving Size\t: " << food[i]->serving_size << " g" << endl;
		cout << "Calories\t: " << food[i]->kcal << " kcal" << endl;
		cout << "Protein\t\t: " << food[i]->protein<< " g" << endl;
		cout << "Carbs\t\t: " << food[i]->carbs << " g" << endl;
		cout << "Fats\t\t: " << food[i]->fats << " g" << endl;
		cout << endl;
	}
}

Food* Food::displayFoodById(int foodId) {
	FoodManager* fm = new FoodManager();
	Food* f =fm->searchFoodById(foodId);
	cout << "#" << foodId << endl;
	cout << "Food\t\t: " << f->getFoodName()<< endl;
	cout << "Serving Size\t: " <<f->getServingSize()<< " g" << endl;
	cout << "Calories\t: " << f->getKcal()<< " kcal" << endl;
	cout << "Protein\t\t: " <<f->getProtein()<< " g" << endl;
	cout << "Carbs\t\t: " << f->getCarbs()<< " g" << endl;
	cout << "Fats\t\t: " << f->getFats()<< " g" << endl;
	cout << endl;

	return f;
}

vector<Food*> Food::displayFoodVecById(int foodId) {
	FoodManager* fm = new FoodManager();
	vector<Food*> food = fm->searchFoodVecById(foodId);
	//Food* f = new Food();
	for (int i = 0; i < food.size(); i++) {
		cout << "#" << food[i]->food_id << endl;
		cout << "Food\t\t: " << food[i]->food_name << endl;
		cout << "Serving Size\t: " << food[i]->serving_size << " g" << endl;
		cout << "Calories\t: " << food[i]->kcal << " kcal" << endl;
		cout << "Protein\t\t: " << food[i]->protein << " g" << endl;
		cout << "Carbs\t\t: " << food[i]->carbs << " g" << endl;
		cout << "Fats\t\t: " << food[i]->fats << " g" << endl;
		cout << endl;

		/*f->food_id = food[i]->food_id;
		f->food_name = food[i]->food_name;
		f->serving_size = food[i]->serving_size;
		f->kcal = food[i]->kcal;
		f->protein= food[i]->protein;
		f->carbs = food[i]->carbs;
		f->fats = food[i]->fats;*/
	}
	return food;
}

void Food::enterFoodName() {
	cin.clear();
	cin.ignore(1, '\n');
	cout << "Food Name: ";
	getline(cin, food_name);
	cout << endl;
}

void Food::enterServingSize() {
	validation = false;
	while (true) {
		cout << "Serving Size in gram (0.1g~1000.0g): ";
		if (!(cin >> serving_size)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(serving_size, 0.1, 1000.0);
			if (validation) break;
			else cout << "Invalid serving size. Please enter valid serving size." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}

void Food::enterKcal() {
	validation = false;
	while (true) {
		cout << "Calories per " << serving_size << "g (0~1000kcal): ";
		if (!(cin >> kcal)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(kcal, 0, 1000);
			if (validation) break;
			else cout << "Invalid calories. Please enter valid calories." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}

void Food::enterProtein() {
	validation = false;
	while (true) {
		cout << "Protein per " << serving_size << "g (0.0~1000.0g): ";
		if (!(cin >> protein)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(protein, 0.0, 1000.0);
			if (validation) break;
			else cout << "Invalid protein. Please enter valid protein." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}

void Food::enterCarbs() {
	validation = false;
	while (true) {
		cout << "Carbohydrates per " << serving_size << "g (0.0~1000.0g): ";
		if (!(cin >> carbs)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(carbs, 0.0, 1000.0);
			if (validation) break;
			else cout << "Invalid carbs. Please enter valid carbs." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}


void Food::enterFats() {
	validation = false;
	while (true) {
		cout << "Fats per " << serving_size << "g (0.0~1000.0g): ";
		if (!(cin >> fats)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(fats, 0.0, 1000.0);
			if (validation) break;
			else cout << "Invalid fats. Please enter valid fats." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	cout << endl;
}

template <class T>
bool Food::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}


void Food::setFoodId(int food_id) {
	this->food_id = food_id;
}
void Food::setKcal(int kcal) {
	this->kcal = kcal;
}
void Food::setCreatedBy(int created_by) {
	this->created_by = created_by;
}
void Food::setLastUpdatedBy(int last_updated_by) {
	this->last_updated_by = last_updated_by;
}
void Food::setFoodName(string food_name) {
	this->food_name = food_name;
}
void Food::setCreatedDate(string created_date) {
	this->created_date = created_date;
}
void Food::setLastUpdatedDate(string last_updated_date) {
	this->last_updated_date = last_updated_date;
}
void Food::setServingSize(double serving_size) {
	this->serving_size = serving_size;
}
void Food::setProtein(double protein) {
	this->protein = protein;
}
void Food::setCarbs(double carbs) {
	this->carbs = carbs;
}
void Food::setFats(double fats) {
	this->fats = fats;
}

// getters
int Food::getFoodId() {
	return food_id;
}
int Food::getKcal() {
	return kcal;
}
int Food::getCreatedBy() {
	return created_by;
}
int Food::getLastUpdatedBy() {
	return last_updated_by;
}
string Food::getFoodName() {
	return food_name;
}
string Food::getCreatedDate() {
	return created_date;
}
string Food::getLastUpdatedDate() {
	return last_updated_date;
}
double Food::getServingSize() {
	return serving_size;
}
double Food::getProtein() {
	return protein;
}
double Food::getCarbs() {
	return carbs;
}
double Food::getFats() {
	return fats;
}