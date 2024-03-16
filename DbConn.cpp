#pragma once
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DbConn.h"

DbConn::DbConn() {
	mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();
	// May change the port into 3306
	conn = driver->connect("tcp://127.0.0.1:3308", "root", "");

	conn->setSchema("dbfoodintake");
}

DbConn::~DbConn() {
	conn->close();

	delete conn;
}

PreparedStatement* DbConn::prepareStatement(string query) {
	try {
		return conn->prepareStatement(query);
	}
	catch (sql::SQLException& e) {
		cout << e.what();
	}

}