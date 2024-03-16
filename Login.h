#pragma once
#include "User.h"
#include "BodyDetails.h"
#include "Goal.h"
#include <string>
using namespace std;

class Login
{
public:
	bool login(User* user, BodyDetails* bodyDetails, Goal* goal);
};