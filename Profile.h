#pragma once
#include "BodyDetails.h"
#include "Goal.h"

#include <string>
using namespace std;

class Profile {
private:
	bool validation, end;
	int menuOpt;
public:
	void profile(User* user, BodyDetails* bd, Goal* goal);
	static void changePswd(User* user);
	void updateBodyDetails(User* user, BodyDetails* bd, Goal* goal);
	void updateFitnessGoal(User* user, Goal* goal, BodyDetails* bd);
	
	template <class T>
	bool validateRange(T input, T min, T max);

	/* Methods for displaying details*/
	void displayUserDetails(User* user);
	void displayCurrentBodyDetails(BodyDetails* bd);
	void displayCurrentGoals(Goal* goal);
};