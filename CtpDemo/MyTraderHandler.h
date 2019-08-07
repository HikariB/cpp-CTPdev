#pragma once
#include <Ctp/ThostFtdcTraderApi.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
class MyTraderHandler
{
public:
	MyTraderHandler();
	~MyTraderHandler();

	//注册SPI
	void RegisterSpi(CThostFtdcTraderSpi *trader_spi);
	//设置FrontID和SessionID
	void SetFrontAndSession(int front_id, int session_id);
	//根据FrontID和SessionID判断是否是自己发出的Request
	bool IsLocalReq(int front_id, int session_id);

	////TraderAPI初始化相关函数
	void Connect();
	void ReqAuthenticate();
	void Login();
	void Join();

	////登录之后必要的初始化
	//确认结算信息
	void ConfirmSettlementInfo();
	//查询合约
	void QueryInstrument();
	//查询行情
	void QueryMarketData();
	//查询当前在外挂单
	void QueryOrder();
	//查询持仓
	void QueryPosition();
	//查询账户资金
	void QueryAccount();

private:
	//API Pointer
	CThostFtdcTraderApi* trader_api_;
	//API地址账号参数
	std::string trader_front_address_;
	std::string trader_front_address_;
	std::string broker_id_;
	std::string user_id_;
	std::string password_;
	std::string auth_code_;
	std::string app_id_;
	//当前会话相关参数
	int front_id_;
	int session_id_;
	int request_id_;
	int order_ref_;
};

