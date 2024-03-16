#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "User.h"
#include "Goal.h"
#include "Diary.h"
#include "Calculation.h"
#include "BodyDetails.h"


/// <summary>
/// Calculate Total Daily Energy Expenditure (TDEE)
///
/// (MIFFLIN-ST JEOR FORMULA) 
/// BMR =
/// Male: (10 × weight in kg) + (6.25 × height in cm) - (5 × age in years) + 5
/// Female: (10 × weight in kg) + (6.25 × height in cm) - (5 × age in years) - 161
/// source: https://www.omnicalculator.com/health/tdee#tdee-formula
/// 
/// TDEE = BMR × phisical activity level
/// </summary>
/// <param name="user">Object of User</param>
/// <param name="bd">Object of BodyDetails</param>
/// <returns>Rounded TDEE</returns>
int Calculation::calculateTDEE(User* user, BodyDetails* bd) {
	double x = (10 * (bd->getWeight())) + (6.25 * (bd->getHeight())) - (5.0 * (bd->getAge()));
	double bmr = 0;
	double tdee = 0;
	
	if (user->gender == "F"|| user->gender == "f") {
		bmr = x - 161;
	}
	else if (user->gender == "M"|| user->gender == "m") {
		bmr = x - 5;
	}

	if (bd->getActLvl() == "Sedentary") {
		tdee = bmr * 1.2;
	}
	else if (bd->getActLvl() == "Lightly Active") {
		tdee = bmr * 1.375;
	}
	else if (bd->getActLvl() == "Moderately Active") {
		tdee = bmr * 1.55;
	}
	else if (bd->getActLvl() == "Very Active") {
		tdee = bmr * 1.725;
	}
	else if (bd->getActLvl() == "Extremely Active") {
		tdee = bmr * 1.9;
	}

	bd->setTdee((int)round(tdee));
	return (int)round(tdee);
}

/// <summary>
/// Calculate daily calories goal
/// weight loss is 75% of TDEE (25% below TDEE)
/// lean muscle gain is about 110 % of TDEE(10 % above TDEE)
/// source: https://legionathletics.com/tools/tdee-calculator/#:~:text=How%20much%20above%3F,gaining%20very%20little%20body%20fat.
/// </summary>
/// <param name="goal"></param>
/// <param name="bd"></param>
/// <returns></returns>
int Calculation::caloriesGoal(Goal* goal, BodyDetails* bd) {
	int tdee = bd->getTdee();
	int kcalGoal = 0;
	if (goal->getFitGoal() == "Gain") {
		kcalGoal = tdee * 110/100;
	}
	else if (goal->getFitGoal() == "Cut") {
		kcalGoal = tdee * 75/100;
	}
	else if (goal->getFitGoal() == "Maintain") {
		kcalGoal = tdee ;
	}
	goal->setKcalGoal(kcalGoal);
	
	return kcalGoal;
}

/// <summary>
/// Calculate daily macronutrient goal
/// Default percentage:
/// Protein = 20%
/// carbs = 50%;
/// fats = 30%;
/// 
/// The sources of energy is carbohydrates, fat and protein 
/// with physiological fuel values of 4, 9, 4 kcal/g respectively
/// 
/// Source: http://nutrition.moh.gov.my/wp-content/uploads/2017/05/FA-Buku-RNI.pdf
/// 
/// </summary>
/// <param name="goal">Object of Goal</param>
void Calculation::macronutrientGoal(Goal* goal) {
	
	int kcalGoal = goal->getKcalGoal();
	double pp = goal->getProtPerc() / 100.0;
	double cp = goal->getCarbsPerc() / 100.0;
	double fp = goal->getFatsPerc() / 100.0;

	goal->setProtGram(kcalGoal * (pp / 4));
	goal->setCarbsGram(kcalGoal * (cp / 4));
	goal->setFatsGram(kcalGoal * (fp / 9));
}

/// <summary>
/// Calculate 
/// portion x calories
/// portion x macronutrient
/// </summary>
/// <param name="df"></param>
/// <param name="food"></param>
/// <returns></returns>
DiaryFood* Calculation::calculateDiaryFood(DiaryFood* df, Food* food) {
	double p = df->getPortion();

	df->setDfKcal(p * food->getKcal());
	df->setDfProtein(p * food->getProtein());
	df->setDfCarbs(p * food->getCarbs());
	df->setDfFats(p * food->getFats());
	return df;
}
