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

	//ע��SPI
	void RegisterSpi(CThostFtdcTraderSpi *trader_spi);
	//����FrontID��SessionID
	void SetFrontAndSession(int front_id, int session_id);
	//����FrontID��SessionID�ж��Ƿ����Լ�������Request
	bool IsLocalReq(int front_id, int session_id);

	////TraderAPI��ʼ����غ���
	void Connect();
	void ReqAuthenticate();
	void Login();
	void Join();

	////��¼֮���Ҫ�ĳ�ʼ��
	//ȷ�Ͻ�����Ϣ
	void ConfirmSettlementInfo();
	//��ѯ��Լ
	void QueryInstrument();
	//��ѯ����
	void QueryMarketData();
	//��ѯ��ǰ����ҵ�
	void QueryOrder();
	//��ѯ�ֲ�
	void QueryPosition();
	//��ѯ�˻��ʽ�
	void QueryAccount();

private:
	//API Pointer
	CThostFtdcTraderApi* trader_api_;
	//API��ַ�˺Ų���
	std::string trader_front_address_;
	std::string trader_front_address_;
	std::string broker_id_;
	std::string user_id_;
	std::string password_;
	std::string auth_code_;
	std::string app_id_;
	//��ǰ�Ự��ز���
	int front_id_;
	int session_id_;
	int request_id_;
	int order_ref_;
};

