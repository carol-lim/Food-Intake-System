#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Food.h"
#include "FoodManager.h"
#include "DbConn.h"

int FoodManager::addNewFood(Food* food) {
	DbConn dbConn;

	string statInsert = "INSERT INTO food (name, serving_size, kcal, protein, carbs, fats, created_by) VALUES ( ?, ?, ?, ?, ?, ?, ?)";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		ps->setString(1, food->getFoodName());
		ps->setDouble(2, food->getServingSize());
		ps->setInt(3, food->getKcal());
		ps->setDouble(4, food->getProtein());
		ps->setDouble(5, food->getCarbs());
		ps->setDouble(6, food->getFats());
		ps->setInt(7, food->getCreatedBy());

		status = ps->executeUpdate();

		string lastId;
		string statSelectId = "SELECT * FROM food ORDER BY food_id DESC LIMIT 1";
		PreparedStatement* psId = dbConn.prepareStatement(statSelectId);
		ResultSet* rs = psId->executeQuery();
		while (rs->next()) {
			food->setFoodId(rs->getInt("food_id"));
			food->setCreatedDate(rs->getString("created_date"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

int FoodManager::updateFood(Food* food) {

	DbConn dbConn;

	string stat = "UPDATE food SET name = ?, serving_size= ?, kcal= ?, protein= ?, carbs= ?, fats = ?, last_updated_by = ?, last_updated_date = CAST(CURRENT_TIMESTAMP as DATE) WHERE food_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setString(1, food->getFoodName());
		ps->setDouble(2, food->getServingSize());
		ps->setInt(3, food->getKcal());
		ps->setDouble(4, food->getProtein());
		ps->setDouble(5, food->getCarbs());
		ps->setDouble(6, food->getFats());
		ps->setInt(7, food->getLastUpdatedBy());
		ps->setInt(8, food->getFoodId());

		status = ps->executeUpdate();

	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

Food* FoodManager::searchFoodById(int food_id) {

	DbConn dbConn;
	Food* f = new Food;
	string stat = "SELECT * FROM food WHERE food_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setString(1, to_string(food_id));
		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			f->setFoodId(rs->getInt("food_id"));
			f->setFoodName(rs->getString("name"));
			f->setServingSize(rs->getDouble("serving_size"));
			f->setKcal(rs->getInt("kcal"));
			f->setProtein(rs->getDouble("protein"));
			f->setCarbs(rs->getDouble("carbs"));
			f->setFats(rs->getDouble("fats"));
			f->setCreatedBy(rs->getInt("created_by"));
			f->setCreatedDate(rs->getString("created_date"));
			f->setLastUpdatedBy(rs->getInt("last_updated_by"));
			f->setLastUpdatedDate(rs->getString("last_updated_date"));

		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return f;
}

vector<Food*> FoodManager::searchFoodVecById(int food_id) {

	DbConn dbConn;
	vector<Food*> foodVector;
	string stat = "SELECT * FROM food WHERE food_id = ?";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		ps->setString(1, to_string(food_id));
		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			Food* f = new Food;
			f->setFoodId(rs->getInt("food_id"));
			f->setFoodName(rs->getString("name"));
			f->setServingSize(rs->getDouble("serving_size"));
			f->setKcal(rs->getInt("kcal"));
			f->setProtein(rs->getDouble("protein"));
			f->setCarbs(rs->getDouble("carbs"));
			f->setFats(rs->getDouble("fats"));
			f->setCreatedBy(rs->getInt("created_by"));
			f->setCreatedDate(rs->getString("created_date"));
			f->setLastUpdatedBy(rs->getInt("last_updated_by"));
			f->setLastUpdatedDate(rs->getString("last_updated_date"));

			foodVector.push_back(f);

		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return foodVector;
}


vector<Food*> FoodManager::searchFoodByName(string name) {
	DbConn dbConn;
	vector<Food*> foodVector;

	string stat = "SELECT * FROM food WHERE LOWER(name) LIKE LOWER(\'%"+name+"%\')";
	PreparedStatement* ps = dbConn.prepareStatement(stat);
	int status;
	try {
		//ps->setString(1, name);

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			Food* f = new Food;
			f->setFoodId(rs->getInt("food_id"));
			f->setFoodName(rs->getString("name"));
			f->setServingSize(rs->getDouble("serving_size"));
			f->setKcal(rs->getInt("kcal"));
			f->setProtein(rs->getDouble("protein"));
			f->setCarbs(rs->getDouble("carbs"));
			f->setFats(rs->getDouble("fats"));
			f->setCreatedBy(rs->getInt("created_by"));
			f->setCreatedDate(rs->getString("created_date"));
			f->setLastUpdatedBy(rs->getInt("last_updated_by"));
			f->setLastUpdatedDate(rs->getString("last_updated_date"));

			foodVector.push_back(f);
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return foodVector;
}


int FoodManager::checkFoodByName(string name) {
	DbConn dbConn;
	int status = 0;
	string statSelect = "SELECT COUNT(*) as Food FROM food WHERE name LIKE \'" + name + "\'";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			status = rs->getInt("Food");
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}
