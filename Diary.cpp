#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

#include "Diary.h"
#include "DiaryFood.h"
#include "FoodManager.h"
#include "DiaryFoodManager.h"

Diary::Diary() {
	total_kcal = 0;
	total_protein = 0;
	total_carbs = 0;
	total_fats = 0;
}

void Diary::displayProgress(Goal* goal) {
	cout << "------ Intake Progress ------" << endl;
	cout << endl;
	cout <<	setw(20) << " [Goal]" << setw(10) << "[Taken]" << setw(10) << " [Left]" << endl;
	cout << setw(10)<< "Calories" << setw(10) << goal->getKcalGoal() << setw(10) << total_kcal << setw(10) << goal->getKcalGoal() - total_kcal << endl;
	cout << setw(10)<< "Protein" << setw(10) << goal->getProtGram() << setw(10) << total_protein << setw(10) << goal->getProtGram()- total_protein << endl;
	cout << setw(10)<< "Carbs" << setw(10) << goal->getCarbsGram() << setw(10) << total_carbs << setw(10) << goal->getCarbsGram() - total_carbs << endl;
	cout << setw(10)<< "Fats" << setw(10) << goal->getFatsGram() << setw(10) << total_fats << setw(10) << goal->getFatsGram()- total_fats << endl;
	cout << endl;
}

/// <summary>
/// Display all the diary food if any
/// </summary>
/// <returns>Existence of diary food</returns>
bool Diary::displayDiaryFood() {
	cout << "------ Intake Record ------" << endl;
	DiaryFoodManager* dfm = new DiaryFoodManager();
	FoodManager* fm = new FoodManager();
	
	// Get the number of rows of current diary food based on diary ID
	int row = dfm->countDiaryFoodByDiaryId(diary_id);

	// Diary has food
	if (row != 0) {

		// Get and display all the current diary food details 
		vector<DiaryFood*> dfv = dfm->getCurrentDiaryFood(diary_id);
		for (int i = 0; i < dfv.size(); i++) {
			cout << "#" << dfv[i]->getDfFoodId() << endl;
			Food* food = fm->searchFoodById(dfv[i]->getDfFoodId());
			cout << "Food\t:" << food->getFoodName() << endl;
			cout << "Portion\t:" << dfv[i]->getPortion() << endl;
			cout << "Calories:" << dfv[i]->getDfKcal() << " kcal" << endl;
			cout << "Protein\t:" << dfv[i]->getDfProtein() << " g" << endl;
			cout << "Carbs\t:" << dfv[i]->getDfCarbs() << " g" << endl;
			cout << "Fats\t:" << dfv[i]->getDfFats() << " g" << endl;
			cout << endl;
		}
		return true;
	}
	// Diary has no food
	else {
		cout << "No food added today." << endl;
		cout << endl;
		return false;
	}
}

// setters
void Diary::setDiaryId(int diary_id) {
	this->diary_id = diary_id;
}
void Diary::setTotalKcal(int total_kcal) {
	this->total_kcal = total_kcal;
}
void Diary::setDate(string date) {
	this->date = date;
}
void Diary::setTotalProtein(double total_protein) {
	this->total_protein = total_protein;
}
void Diary::setTotalCarbs(double total_carbs) {
	this->total_carbs = total_carbs;
}
void Diary::setTotalFats(double total_fats) {
	this->total_fats = total_fats;
}

// getters
int Diary::getDiaryId() {
	return diary_id;
}
int Diary::getTotalKcal() {
	return total_kcal;
}
string Diary::getDate() {
	return date;
}
double Diary::getTotalProtein() {
	return total_protein;
}
double Diary::getTotalCarbs() {
	return total_carbs;
}
double Diary::getTotalFats() {
	return total_fats;
}