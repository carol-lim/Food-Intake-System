#pragma once
#include "Goal.h"
#include "User.h"
//#ifndef GOALMANAGER_H
//#define GOALMANAGER_H

class GoalManager {
public:
	int addGoal(Goal* goal, User* user);
	//int updateBd(BodyDetails* user);
	void getCurrentGoal(int user_id, Goal* goal);
};

//#endif 
