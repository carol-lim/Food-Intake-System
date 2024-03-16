#pragma once
#ifndef USERMANAGER_H
#define USERMANAGER_H

//#include "User.h"

class UserManager {
public:
	int addUser(User* user);
	int updatePswd(User* user);
	int updateGender(User* user);
	bool searchUser(User* user);

};

#endif // USERMANAGER_H
