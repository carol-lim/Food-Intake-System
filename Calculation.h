#pragma once
#include <string>
#include "User.h"
#include "Goal.h"
#include "Food.h"
#include "DiaryFood.h"
#include "BodyDetails.h"
using namespace std;

class Calculation {
public:
	int calculateTDEE(User* user, BodyDetails* bd);
	int caloriesGoal(Goal* goal, BodyDetails* bd);
	void macronutrientGoal(Goal* goal);
	DiaryFood* calculateDiaryFood(DiaryFood* df, Food* food);
};

