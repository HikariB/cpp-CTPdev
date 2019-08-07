// CtpDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include "MySqlite3.h"
#include "MyWebsocketServer.h"
#include "MyMdHandler.h"

int main()
{
	//MySqlite3 sql;
	//sql.test();

	//MyWebsocketServer wsServer;
	//wsServer.run(9999);

	MyMdHandler mdHandler;
	mdHandler.SetSubscribeList();
	mdHandler.connect();
	mdHandler.subscribeMD();


	

	std::cout << "Hello World!\n";
	system("pause");
	return 0;
}

