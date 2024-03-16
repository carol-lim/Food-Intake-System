#pragma once

#include <ctime>
#include <string>
using namespace std;

class DiaryFood {
private:
	int df_food_id;
	double df_kcal, df_protein, df_carbs, df_fats, portion;
	bool validation;

public:
	DiaryFood();
	~DiaryFood();

	double enterPortion();

	template <class T>
	bool validateRange(T input, T min, T max);
	
	// setters
	void setDfFoodId(int df_food_id);
	void setPortion(double portion);
	void setDfKcal(double df_kcal);
	void setDfProtein(double df_protein);
	void setDfCarbs(double df_carbs);
	void setDfFats(double df_fats);

	// getters
	int getDfFoodId();
	double getPortion();
	double getDfKcal();
	double getDfProtein();
	double getDfCarbs();
	double getDfFats();
};