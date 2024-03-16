#pragma once

#include <ctime>
#include <string>
#include <vector>
using namespace std;

class Food {
private:

	int food_id, kcal, created_by, last_updated_by;
	string food_name, created_date, last_updated_date;
	double serving_size, protein, carbs, fats;
	bool validation;

public:
	/*Food();
	~Food();*/

	vector<Food*> displayFoodVecById(int foodId);
	Food* displayFoodById(int foodId);
	void displayFoodDetails(vector<Food*> food);

	// add or update food
	void enterFoodName();
	void enterServingSize();
	void enterKcal();
	void enterProtein();
	void enterCarbs();
	void enterFats();


	template <class T>
	bool validateRange(T input, T min, T max);

	// setters
	void setFoodId(int food_id);
	void setKcal(int kcal);
	void setCreatedBy(int created_by);
	void setLastUpdatedBy(int last_updated_by);
	void setFoodName(string food_name);
	void setCreatedDate(string created_date);
	void setLastUpdatedDate(string last_updated_date);
	void setServingSize(double serving_size);
	void setProtein(double protein);
	void setCarbs(double carbs);
	void setFats(double fats);

	// getters
	int getFoodId();
	int getKcal();
	int getCreatedBy();
	int getLastUpdatedBy();
	string getFoodName();
	string getCreatedDate();
	string getLastUpdatedDate();
	double getServingSize();
	double getProtein();
	double getCarbs();
	double getFats();
};