#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "User.h"
#include "UserManager.h"
#include "DbConn.h"

int UserManager::addUser(User* user){
	DbConn dbConn;
	
	string statInsert = "INSERT INTO User ( name, gender, yob, password, email) VALUES (?, ?, ?, ?, ?)";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		//ps->setString(1, user->user_id);
		ps->setString(1, user->name);
		ps->setString(2, user->gender);
		ps->setInt(3, user->yob);
		ps->setString(4, user->password);
		ps->setString(5, user->email);

		status = ps->executeUpdate();

		string lastId;
		string statSelectId = "SELECT * FROM user ORDER BY user_id DESC LIMIT 1";
		PreparedStatement* psId = dbConn.prepareStatement(statSelectId);
		ResultSet* rs = psId->executeQuery();
		while (rs->next()) {
			user->user_id = rs->getInt("user_id");
		}

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

int UserManager::updatePswd(User* user){
	
	DbConn dbConn;

	string stat = "UPDATE user SET password = ? WHERE user_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setString(1, user->password);
		ps->setInt(2, user->user_id);
		
		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

bool UserManager::searchUser(User* user) {
	DbConn dbConn;
	int id = user->user_id;

	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM User WHERE user_id =? ");

	ps->setString(1, to_string(id));

	ResultSet* rs = ps->executeQuery();

	while (rs->next()) {
		cout << "User ID: " << rs->getString("user_id") << endl;
		cout << "Name: " << rs->getString("name") << endl;
		cout << "Email: " << rs->getString("email") << endl;
	}

	delete ps;
}

int UserManager::updateGender(User* user) {
	DbConn dbConn;

	string stat = "UPDATE user SET gender = ? WHERE user_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setString(1, user->gender);
		ps->setInt(2, user->user_id);

		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}