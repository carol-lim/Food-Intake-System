#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "DiaryFood.h"
#include "Calculation.h"
#include "FoodManager.h"

DiaryFood::DiaryFood() {
	df_food_id = 0;
	df_kcal = 0.0; df_protein = 0.0;  df_carbs = 0.0; df_fats = 0.0;  portion = 0.0;
	validation = false;
}
DiaryFood::~DiaryFood() {

}

double DiaryFood::enterPortion() {
	validation = false;
	while (true) {
		cout << "Portion (0.1~100.0): ";
		if (!(cin >> portion)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			validation = validateRange(portion, 0.1, 100.0);
			if (validation)break;
			else cout << "Invalid portion. Please enter valid portion." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	system("pause");
	cout << endl;
	return portion;
}

template <class T>
bool DiaryFood::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}

// setters
void DiaryFood::setDfFoodId(int df_food_id) {
	this->df_food_id = df_food_id;
}
void DiaryFood::setPortion(double portion) {
	this->portion = portion;
}
void DiaryFood::setDfKcal(double df_kcal) {
	this->df_kcal = df_kcal;
}
void DiaryFood::setDfProtein(double df_protein) {
	this->df_protein = df_protein;
}
void DiaryFood::setDfCarbs(double df_carbs) {
	this->df_carbs = df_carbs;
}
void DiaryFood::setDfFats(double df_fats) {
	this->df_fats = df_fats;
} 

// getters
int DiaryFood::getDfFoodId() {
	return df_food_id;
}
double DiaryFood::getPortion() {
	return portion;
}
double DiaryFood::getDfKcal() {
	return df_kcal;
}
double DiaryFood::getDfProtein() {
	return df_protein;
}
double DiaryFood::getDfCarbs() {
	return df_carbs;
}
double DiaryFood::getDfFats() {
	return df_fats;
}