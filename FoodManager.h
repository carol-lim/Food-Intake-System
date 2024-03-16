#pragma once
#include "Food.h"
#include "User.h"
#include <vector>


class FoodManager {
public:
	int addNewFood(Food* food);
	int updateFood(Food* food);
	Food* searchFoodById(int food_id);
	vector<Food*> searchFoodVecById(int food_id);
	vector<Food*> searchFoodByName(string name);
	int checkFoodByName(string name);
	//void getCurrentFoods(int user_id, Food* food);
};
