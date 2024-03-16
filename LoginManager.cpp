#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "LoginManager.h"
#include "User.h"
#include "DbConn.h"

bool LoginManager::checkId(User* user) {
	DbConn dbConn;
	bool idValidity = false;
	int id = user->user_id;

	string statSelectId = "SELECT * FROM user WHERE user_id =? ";
	PreparedStatement* psId = dbConn.prepareStatement(statSelectId);
	try {
		psId->setString(1, to_string(id));

		ResultSet* rs = psId->executeQuery();

		while (rs->next()) {
			user->password = rs->getString("password");
			user->name = rs->getString("name");
			user->gender = rs->getString("gender");
			user->yob = rs->getInt("yob");
			user->email= rs->getString("email");
			idValidity = true;
		}
	}

	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete psId;

	return idValidity;
}

bool LoginManager::checkEmail(User* user) {
	DbConn dbConn;
	bool idValidity = false;
	//int id = user->user_id;

	string stat = "SELECT * FROM user WHERE email =? ";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	try {
		ps->setString(1, user->email);

		ResultSet* rs = ps->executeQuery();

		while (rs->next()) {
			user->user_id = rs->getInt("user_id");
			user->password = rs->getString("password");
			user->name = rs->getString("name");
			user->gender = rs->getString("gender");
			user->yob = rs->getInt("yob");
			user->email= rs->getString("email");
			idValidity = true;
		}
	}

	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;

	return idValidity;
}


bool LoginManager::checkPswd(User* user, string inputPswd) {
	bool pswdValidity = false;

	if (inputPswd==user->password) {
		pswdValidity = true;
	}
	else {
		pswdValidity = false;
	}

	return pswdValidity;
}