#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DiaryFood.h"
#include "DiaryFoodManager.h"
#include "DbConn.h"

int DiaryFoodManager::addNewDiaryFood(int diary_id, int food_id, DiaryFood* df) {
	DbConn dbConn;

	//string statInsert = "INSERT INTO Diaryfood (diary_id, food_id, portion, df_kcal, df_protein, df_carbs, df_fats) VALUES ( ?, ?, ?, ?, ?, ?, ?)";
	string statInsert = "INSERT INTO `diaryfood`(`diary_id`, `food_id`, `portion`, `df_kcal`, `df_protein`, `df_carbs`, `df_fats`) VALUES (?,?,?,?,?,?,?)";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		ps->setInt(1, diary_id);
		ps->setInt(2, food_id);
		ps->setDouble(3, df->getPortion());
		ps->setDouble(4, df->getDfKcal());
		ps->setDouble(5, df->getDfProtein());
		ps->setDouble(6, df->getDfCarbs());
		ps->setDouble(7, df->getDfFats());

		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;

}

int DiaryFoodManager::removeDiaryFood(int diary_id, int food_id) {
	DbConn dbConn;

	string statInsert = "DELETE FROM diaryfood WHERE diary_id = ? AND food_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		ps->setInt(1, diary_id);
		ps->setInt(2, food_id);

		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

int DiaryFoodManager::updateDiaryFood(int diary_id, int food_id, DiaryFood* df) {

	DbConn dbConn;

	string stat = "UPDATE `diaryfood` SET `portion` = ?, `df_kcal` = ?, `df_protein`= ?, `df_carbs`= ?, `df_fats` = ? WHERE `diary_id` = ? AND `food_id` =?";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setDouble(1, df->getPortion());
		ps->setDouble(2, df->getDfKcal());
		ps->setDouble(3, df->getDfProtein());
		ps->setDouble(4, df->getDfCarbs());
		ps->setDouble(5, df->getDfFats());
		ps->setInt(6, diary_id);
		ps->setInt(7, food_id);

		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

// find current diary row count
int DiaryFoodManager::countDiaryFoodByDiaryId(int diary_id) {
	DbConn dbConn;
	int status = 0;
	string statSelect = "SELECT COUNT(*) as DiaryFoodRow FROM diaryfood WHERE diary_id = ? ";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(diary_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			status = rs->getInt("DiaryFoodRow");
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}


vector<DiaryFood*> DiaryFoodManager::getCurrentDiaryFood(int diary_id) {
	DbConn dbConn;
	vector<DiaryFood*> dfVector;
	
	string statSelect = "SELECT * FROM diaryfood WHERE diary_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(diary_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			DiaryFood* df = new DiaryFood;
			df->setDfFoodId(rs->getInt("food_id"));
			df->setPortion(rs->getDouble("portion"));
			df->setDfKcal(rs->getDouble("df_kcal"));
			df->setDfProtein(rs->getDouble("df_protein"));
			df->setDfCarbs(rs->getDouble("df_carbs"));
			df->setDfFats(rs->getDouble("df_fats"));

			dfVector.push_back(df);
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;

	return dfVector;
}

DiaryFood* DiaryFoodManager::getSingleDiaryFood(int diary_id, int food_id) {
	DbConn dbConn;
	DiaryFood* df = new DiaryFood;

	string statSelect = "SELECT * FROM diaryfood WHERE diary_id = ? AND food_id =?";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(diary_id));
		ps->setString(2, to_string(food_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			df->setDfFoodId(rs->getInt("food_id"));
			df->setPortion(rs->getDouble("portion"));
			df->setDfKcal(rs->getDouble("df_kcal"));
			df->setDfProtein(rs->getDouble("df_protein"));
			df->setDfCarbs(rs->getDouble("df_carbs"));
			df->setDfFats(rs->getDouble("df_fats"));

		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;

	return df;
}

int DiaryFoodManager::checkDiaryFoodByDiaryId(int diary_id, int food_id) {
	DbConn dbConn;
	int status = 0;
	string statSelect = "SELECT COUNT(*) as DiaryFood FROM diaryfood WHERE diary_id = ? AND food_id =? ";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(diary_id));
		ps->setString(2, to_string(food_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			status = rs->getInt("DiaryFood");
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}
