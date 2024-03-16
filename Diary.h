#pragma once

#include <ctime>
#include <string>
using namespace std;

#include "Goal.h"

class Diary {
private:

	int diary_id, total_kcal;
	double total_protein, total_carbs, total_fats;
	string date;

public:
	Diary();
	void displayProgress(Goal* goal);
	bool displayDiaryFood();

	// setters
	void setDiaryId(int diary_id);
	void setTotalKcal(int total_kcal);
	void setDate(string date);
	void setTotalProtein(double total_protein);
	void setTotalCarbs(double total_carbs);
	void setTotalFats(double total_fats);

	// getters
	int getDiaryId();
	int getTotalKcal();
	string getDate();
	double getTotalProtein();
	double getTotalCarbs();
	double getTotalFats();
};