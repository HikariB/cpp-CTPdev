#include "MyTraderHandler.h"



MyTraderHandler::MyTraderHandler():
	trader_api_(CThostFtdcTraderApi::CreateFtdcTraderApi("ctp_trader_temp//")),
	request_id_(0),order_ref_(0)
{
	trader_front_address_ = "tcp://101.231.185.21:61205";
	broker_id_ = "7090";
	user_id_ = "83925105";
	password_ = "";
	auth_code_ = "";
	app_id_ = "";
	std::cout << broker_id_ << "," << user_id_ << "," << password_ << std::endl;
	std::cout << "Initializing CTP Trader: User " << user_id_ << ", Addr " << trader_front_address_ << std::endl;
}



MyTraderHandler::~MyTraderHandler()
{
}

void MyTraderHandler::RegisterSpi(CThostFtdcTraderSpi * trader_spi)
{
	trader_api_->RegisterSpi(trader_spi);
}

void MyTraderHandler::SetFrontAndSession(int front_id, int session_id)
{
	front_id_ = front_id;
	session_id_ = session_id;
}

bool MyTraderHandler::IsLocalReq(int front_id, int session_id)
{
	return (front_id == front_id_) && (session_id == session_id_);
}

void MyTraderHandler::Connect()
{
	trader_api_->RegisterFront(const_cast<char *>(trader_front_address_.c_str()));
	trader_api_->SubscribePrivateTopic(THOST_TERT_RESTART);
	trader_api_->SubscribePublicTopic(THOST_TERT_RESTART);
	trader_api_->Init();
}

void MyTraderHandler::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, _countof(req.BrokerID), broker_id_.c_str());
	strcpy_s(req.UserID, _countof(req.UserID), user_id_.c_str());
	strcpy_s(req.AuthCode, _countof(req.AuthCode), auth_code_.c_str());
	strcpy_s(req.AppID, _countof(req.AppID), app_id_.c_str());
	trader_api_->ReqAuthenticate(&req, ++request_id_);
}

void MyTraderHandler::Login()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, _countof(req.BrokerID), broker_id_.c_str());
	strcpy_s(req.UserID, _countof(req.UserID), user_id_.c_str());
	strcpy_s(req.Password, _countof(req.Password), password_.c_str());
	trader_api_->ReqUserLogin(&req, ++request_id_);
}

void MyTraderHandler::Join()
{
	trader_api_->Join();
}

void MyTraderHandler::ConfirmSettlementInfo()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, _countof(req.BrokerID), broker_id_.c_str());
	strcpy_s(req.InvestorID, _countof(req.InvestorID), user_id_.c_str);
	trader_api_->ReqSettlementInfoConfirm(&req, ++request_id_);
	
}

void MyTraderHandler::QueryInstrument()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	trader_api_->ReqQryInstrument(&req, ++request_id_);
}

void MyTraderHandler::QueryMarketData()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	CThostFtdcQryDepthMarketDataField req;
	memset(&req, 0, sizeof(req));
	trader_api_->ReqQryDepthMarketData(&req, ++request_id_);
}

void MyTraderHandler::QueryOrder()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	CThostFtdcQryOrderField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, _countof(req.BrokerID), broker_id_.c_str());
	strcpy_s(req.InvestorID, _countof(req.InvestorID), user_id_.c_str());
	trader_api_->ReqQryOrder(&req, ++request_id_);
}

void MyTraderHandler::QueryPosition()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, _countof(req.BrokerID), broker_id_.c_str());
	strcpy_s(req.InvestorID, _countof(req.InvestorID), user_id_.c_str());
	trader_api_->ReqQryInvestorPosition(&req, ++request_id_);
}

void MyTraderHandler::QueryAccount()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, _countof(req.BrokerID), broker_id_.c_str());
	strcpy_s(req.InvestorID, _countof(req.InvestorID), user_id_.c_str());
	trader_api_->ReqQryTradingAccount(&req, ++request_id_);
}






