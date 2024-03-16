#pragma once
#include <string>
using namespace std;
#include "BodyDetails.h"
#include "Goal.h"

class RegisterUser {
private:
	string name, gender, email, password;
	int yob;
	double height, weight;

public:

	void registerUser();
};
