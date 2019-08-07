#pragma once
#include <sqlite3/sqlite3.h>
#include <string>
class MySqlite3
{
public:
	MySqlite3();
	~MySqlite3();
	bool openConnection(const char* path);
	bool createTable(const char* sqlSentence);
	bool insert(const char* sqlSentence);
	bool query(const char* sqlSentence);
	void closeCon();
	void test();


private:
	const char *path = "testDB";
	const char * sqlCreateTableSentenceC = "CREATE TABLE IF NOT EXISTS t_person ("\
		"id integer PRIMARY KEY AUTOINCREMENT, "\
		"name text NOT NULL, "\
		"age integer NOT NULL)";
	const std::string sqlCreateTableSentenceStr = "CREATE TABLE IF NOT EXISTS t_person_str ("\
		"id TEXT, name TEXT, age INTEGER )";
	const char *sqlInsert = "INSERT INTO t_person(name,age) VALUES('o_O',21)";
	const char	* sqlQuery = "SELECT name, age FROM t_person WHERE age > 20";
	sqlite3 *sql;
	sqlite3_stmt *stmt;
};

