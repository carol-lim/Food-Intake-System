#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "Goal.h"
#include "GoalManager.h"
#include "DbConn.h"
#include "User.h"

int GoalManager::addGoal(Goal* goal, User* user) {
	DbConn dbConn;

	string statInsert = "INSERT INTO goal (user_id, fitness_goal, kcal_goal, protein_perc, carbs_perc, fats_perc, protein_gram, carbs_gram, fats_gram) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
	PreparedStatement* ps = dbConn.prepareStatement(statInsert);
	int status;
	try {
		ps->setInt(1, user->user_id);
		ps->setString(2, goal->getFitGoal());
		ps->setInt(3, goal->getKcalGoal());
		ps->setInt(4, goal->getProtPerc());
		ps->setInt(5, goal->getCarbsPerc());
		ps->setInt(6, goal->getFatsPerc());
		ps->setInt(7, goal->getProtGram());
		ps->setInt(8, goal->getCarbsGram());
		ps->setInt(9, goal->getFatsGram());
		//ps->setString(8, goal->date);

		status = ps->executeUpdate();

		string lastId;
		string statSelectId = "SELECT * FROM goal ORDER BY goal_id DESC LIMIT 1";
		PreparedStatement* psId = dbConn.prepareStatement(statSelectId);
		ResultSet* rs = psId->executeQuery();
		while (rs->next()) {
			goal->setGoalId(rs->getInt("goal_id"));
			goal->setDate(rs->getString("date"));
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
	return status;
}

void GoalManager::getCurrentGoal(int user_id, Goal* goal) {
	DbConn dbConn;

	string statSelect = "SELECT * FROM goal WHERE user_id = ? AND date in (SELECT MAX(date) from goal GROUP BY user_id)";
	PreparedStatement* ps = dbConn.prepareStatement(statSelect);
	try {
		ps->setString(1, to_string(user_id));

		ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			goal->setGoalId(rs->getInt("goal_id"));
			goal->setFitGoal(rs->getString("fitness_goal"));
			goal->setKcalGoal(rs->getInt("kcal_goal"));
			goal->setProtPerc(rs->getInt("protein_perc"));
			goal->setCarbsPerc(rs->getInt("carbs_perc"));
			goal->setFatsPerc(rs->getInt("fats_perc"));
			goal->setProtGram(rs->getInt("protein_gram"));
			goal->setCarbsGram(rs->getInt("carbs_gram"));
			goal->setFatsGram(rs->getInt("fats_gram"));
			goal->setDate(rs->getString("date"));
			
		}
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

	delete ps;
}