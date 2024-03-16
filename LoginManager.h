#pragma once
//#ifndef LOGINMANAGER_H
//#define LOGINMANAGER_H

#include <string>
using namespace std;
#include "User.h"

class LoginManager {

public:
	bool checkId(User* user);
	bool checkEmail(User* user);
	bool checkPswd(User* user, string inputPassword);
};

//#endif 