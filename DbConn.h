#pragma once

/// <summary>
/// Database connection
/// </summary>
class DbConn
{
private:
	Connection* conn;

public:
	DbConn();
	~DbConn();

	PreparedStatement* prepareStatement(string sql);
};