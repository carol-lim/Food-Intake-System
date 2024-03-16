#pragma once
//#ifndef GOAL_H
//#define GOAL_H

#include <ctime>
#include <string>
using namespace std;
#include "BodyDetails.h"

class Goal {
private:
	int goal_id, kcal_goal, protein_perc, carbs_perc, fats_perc, protein_gram, carbs_gram, fats_gram;
	string fitness_goal, date;
	int  fitGoalOpt;
	bool validation ;
public:
	
	Goal();
	~Goal();
	string chooseFitGoal(int num);

	template <class T>
	bool validateRange(T input, T min, T max);

	void enterFitGoal();
	void enterKcalGoal(BodyDetails* bd);
	void enterProteinGoal();
	void enterCarbsGoal();
	void enterFatsGoal();

	// setters
	void setGoalId(int goal_id);
	void setKcalGoal(int kcal_goal);
	void setProtPerc(int protein_perc);
	void setCarbsPerc(int carbs_perc);
	void setFatsPerc(int fats_perc);
	void setProtGram(int protein_gram);
	void setCarbsGram(int carbs_gram);
	void setFatsGram(int fats_gram);
	void setFitGoal(string fitness_goal);
	void setDate(string date);
	
	// getters
	int getGoalId();
	int getKcalGoal();
	int getProtPerc();
	int getCarbsPerc();
	int getFatsPerc();
	int getProtGram();
	int getCarbsGram();
	int getFatsGram();
	string getFitGoal();
	string getDate();
};

//#endif // USER_H