#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Diary.h"
#include "DiaryManager.h"
#include "DbConn.h"
#include "DiaryFood.h"

int DiaryManager::addNewDiary(Diary* diary, User* user) {
	DbConn dbConn;

	string statInsert = "INSERT INTO diary (user_id, total_kcal, total_protein, total_carbs, total_fats) VALUES ( ?, ?, ?, ?, ?)";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		ps->setInt(1, user->user_id);
		ps->setInt(2, diary->getTotalKcal());
		ps->setDouble(3, diary->getTotalProtein());
		ps->setDouble(4, diary->getTotalCarbs());
		ps->setDouble(5, diary->getTotalFats());

		status = ps->executeUpdate();

		string lastId;
		string statSelectId = "SELECT * FROM diary ORDER BY diary_id DESC LIMIT 1";
		PreparedStatement* psId = dbConn.prepareStatement(statSelectId);
		ResultSet* rs = psId->executeQuery();
		while (rs->next()) {
			diary->setDiaryId(rs->getInt("diary_id"));
			diary->setDate(rs->getString("date"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

int DiaryManager::updateDiary(int diary_id, DiaryFood* df, string action) {
	string stat;
	DbConn dbConn;
	if (action == "add") {
		stat = "UPDATE diary SET total_kcal= total_kcal+?, total_protein= total_protein+?, total_carbs= total_carbs+?, total_fats = total_fats+? WHERE diary_id = ?";
	}
	else if (action == "remove") {
		stat = "UPDATE diary SET total_kcal= total_kcal-?, total_protein= total_protein-?, total_carbs= total_carbs-?, total_fats = total_fats-? WHERE diary_id = ?";
	}
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setInt(1, df->getDfKcal());
		ps->setDouble(2, df->getDfProtein());
		ps->setDouble(3, df->getDfCarbs());
		ps->setDouble(4, df->getDfFats());
		ps->setInt(5, diary_id);

		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

// find current diary row count
int DiaryManager::findCurrentDiary(int user_id) {
	DbConn dbConn;
	int status = 0;
	string statSelect = "SELECT COUNT(*) as DiaryRow FROM diary WHERE user_id = ? AND date = CAST(CURRENT_TIMESTAMP as DATE)";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(user_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			status = rs->getInt("DiaryRow");
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}


void DiaryManager::getCurrentDiary(int user_id, Diary* diary) {
	DbConn dbConn;

	string statSelect = "SELECT * FROM diary WHERE user_id = ? AND date = CAST(CURRENT_TIMESTAMP as DATE)";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(user_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			diary->setDiaryId(rs->getInt("diary_id"));
			diary->setTotalKcal(rs->getInt("total_kcal"));
			diary->setTotalProtein(rs->getDouble("total_protein"));
			diary->setTotalCarbs(rs->getDouble("total_carbs"));
			diary->setTotalFats(rs->getDouble("total_fats"));
			diary->setDate(rs->getString("date"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
}
