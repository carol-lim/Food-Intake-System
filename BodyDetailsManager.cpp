#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DbConn.h"
#include "BodyDetails.h"
#include "BodyDetailsManager.h"

int BodyDetailsManager::addBd(BodyDetails* bd, User* user) {
	DbConn dbConn;

	string statInsert = "INSERT INTO bodydetails (user_id, age, height, weight, act_level, tdee) VALUES (?, ?, ?, ?, ?, ? )";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		ps->setInt(1, user->user_id);
		ps->setInt(2, bd->getAge());
		ps->setDouble(3, bd->getHeight());
		ps->setDouble(4, bd->getWeight());
		ps->setString(5, bd->getActLvl());
		ps->setInt(6, bd->getTdee());

		status = ps->executeUpdate();

		string lastId;
		string statSelectId = "SELECT * FROM bodydetails ORDER BY bd_id DESC LIMIT 1";
		PreparedStatement* psId = dbConn.prepareStatement(statSelectId);
		ResultSet* rs = psId->executeQuery();
		while (rs->next()) {
			bd->setBdId(rs->getInt("bd_id"));
			bd->setDate(rs->getString("date"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

/// <summary>
/// Get latest body details of a user based on latest date and user ID
/// </summary>
/// <param name="user_id">user ID</param>
/// <param name="bd">BodyDetails</param>
void BodyDetailsManager::getCurrentBd(int user_id, BodyDetails* bd) {
	DbConn dbConn;

	string statSelect= "SELECT * FROM bodydetails WHERE user_id = ? AND date in (SELECT MAX(date) from bodydetails GROUP BY user_id)";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(user_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			bd->setBdId(rs->getInt("bd_id"));
			bd->setAge(rs->getInt("age"));
			bd->setHeight(rs->getDouble("height"));
			bd->setWeight(rs->getDouble("weight"));
			bd->setActLvl(rs->getString("act_level"));
			bd->setTdee(rs->getInt("tdee"));
			bd->setDate(rs->getString("date"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
}

/// <summary>
/// Get all recorded weights of a user
/// Invoke by report module
/// </summary>
/// <param name="user_id">User ID</param>
/// <returns>Vector of user's weights</returns>
vector<double> BodyDetailsManager::getWeightVector(int user_id) {
	DbConn dbConn;
	vector<double> weight;

	string stat = "SELECT * FROM bodydetails WHERE user_id = ? ORDER BY date";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setInt(1, user_id);

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			weight.push_back(rs->getInt("weight"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return weight;
}

/// <summary>
/// Get all recorded body details date of a user
/// </summary>
/// <param name="user_id">User ID</param>
/// <returns>Vector of date</returns>
vector<string> BodyDetailsManager::getDateVector(int user_id) {
	DbConn dbConn;
	vector<string> dates;

	string stat = "SELECT * FROM bodydetails WHERE user_id = ? ORDER BY date";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setInt(1, user_id);

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			dates.push_back(rs->getString("date"));

		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return dates;
}