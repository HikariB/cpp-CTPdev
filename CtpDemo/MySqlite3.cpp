#include "MySqlite3.h"
#include <iostream>
#include <sqlite3/sqlite3.h>


MySqlite3::MySqlite3()
{
	sql = NULL;
	stmt = NULL;
}


MySqlite3::~MySqlite3()
{
}

bool MySqlite3::openConnection(const char* path)
{
	bool isOK = true;
	int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX |
		SQLITE_OPEN_SHAREDCACHE, NULL);
	if (result == SQLITE_OK) {
		std::cout << "Open DataBase Success." << std::endl;
	}
	else {
		std::clog << "Open DataBase Error" << std::endl;
		isOK = false;
	}
	return isOK;
}

bool MySqlite3::createTable(const char* sqlSentence)
{
	bool isOK = true;
	int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
	if (result == SQLITE_OK)
	{
		std::clog << "Create Table Sql OK - Const Char *" << std::endl;
		//Ö´ÐÐ¸ÃÓï¾ä
		sqlite3_step(stmt);
	}
	else
	{
		std::clog << "Illegal Create TABLE SQL Statement" << std::endl;
		isOK = false;
	}
	sqlite3_finalize(stmt);
	return isOK;
}

bool MySqlite3::insert(const char * sqlSentence)
{
	bool isOK = true;
	int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
	if (result == SQLITE_OK)
	{
		std::clog << "Insert SQL OK" << std::endl;
		sqlite3_step(stmt);
	}
	else
	{
		std::clog << "Illegal Insert SQL Statement" << std::endl;
		isOK = false;
	}
	sqlite3_finalize(stmt);
	return isOK;
}

bool MySqlite3::query(const char * sqlSentence)
{
	bool isOk = true;
	int result = sqlite3_prepare_v2(sql, sqlQuery, -1, &stmt, NULL);
	if (result == SQLITE_OK)
	{
		std::clog << "Query SQL OK" << std::endl;
		//sqlite3_step(stmt);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			const unsigned char *name = sqlite3_column_text(stmt, 0);
			int age = sqlite3_column_int(stmt, 1);
			std::clog << "name = " << name << ", age = " << age << std::endl;
		}
	}
	else
	{
		isOk = false;
		std::clog << "Illegal Query SQL Statement" << std::endl;
	}
	sqlite3_finalize(stmt);
	return isOk;
}

void MySqlite3::closeCon()
{
	if (sql)
	{
		sqlite3_close_v2(sql);
		sql = nullptr;
	}
}

void MySqlite3::test()
{
	openConnection(path);
	createTable(sqlCreateTableSentenceC);
	insert(sqlInsert);
	query(sqlQuery);
	closeCon();
}
