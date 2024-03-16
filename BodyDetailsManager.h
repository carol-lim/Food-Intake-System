#pragma once
#include <vector>
#include "User.h"
#include "BodyDetails.h"

class BodyDetailsManager {
public:
	int addBd(BodyDetails* bd, User* user);
	void getCurrentBd(int user_id, BodyDetails* bd);
	vector<double> getWeightVector(int user_id);
	vector<string> getDateVector(int user_id);
};