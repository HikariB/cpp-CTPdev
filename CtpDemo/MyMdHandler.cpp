#include "MyMdHandler.h"



MyMdHandler::MyMdHandler() :
	
	request_id_(0)
{
	md_api_ = CThostFtdcMdApi::CreateFtdcMdApi("ctp_md_temp//");
	md_front_address_ = "tcp://101.231.185.21:61213";
}

MyMdHandler::~MyMdHandler()
{
}

void MyMdHandler::SetSubscribeList()
{
	subscribe_list_.push_back("IF");
	subscribe_list_.push_back("IH");
	subscribe_list_.push_back("IC");
}

void MyMdHandler::connect()
{
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << "Initializing CTP MD: Addr " << md_front_address_ << std::endl;
	md_api_->RegisterSpi(this);
	md_api_->RegisterFront(const_cast<char *>(md_front_address_.c_str()));
	md_api_->Init();
}

void MyMdHandler::login()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	md_api_->ReqUserLogin(&req, ++request_id_);
}

void MyMdHandler::subscribeMD()
{
	int subscription_list_size = (int)subscribe_list_.size();
	char ** subscription_list = new char*[subscription_list_size];
	for (int i = 0; i < subscription_list_size; i++)
		subscription_list[i] = (char*)subscribe_list_[i].c_str();
	md_api_->SubscribeMarketData(subscription_list, subscription_list_size);
	delete[] subscription_list;
}

void MyMdHandler::join()
{
	md_api_->Join();
}

void MyMdHandler::OnFrontConnected()
{
	std::cout << "CTP MD: --->>> connected to front.\n";
	this->login();
}

void MyMdHandler::OnFrontDisconnected(int nReason)
{
	std::cerr << "CTP MD: --->>> disconnected from front for reason: " << std::hex << "0x" << nReason << ".\n" << std::dec;
	//md_receiver_->OnCtpMdDisconnected(nReason);
}

void MyMdHandler::OnRspUserLogin(CThostFtdcRspUserLoginField * pRspUserLogin, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspUserLogin != NULL && pRspInfo->ErrorID == 0) {
		std::cout << "CTP MD: --->>> md login successfully.\n";
	}
	else
		std::cout << "CTP MD: --->>> user login failed for reason " << pRspInfo->ErrorID << ": " << pRspInfo->ErrorMsg << ".\n";
}

void MyMdHandler::OnRspError(CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	std::cerr << "CTP MD: --->>> md request " << nRequestID << " encountered no." << pRspInfo->ErrorID << " error of " << pRspInfo->ErrorMsg << ".\n";
}

void MyMdHandler::OnRspSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast)
		std::cout << "Finished subscribing market data.\n";
}

void MyMdHandler::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField * pSpecificInstrument, CThostFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast)
		std::cout << "Finished unsubscribing market data.\n";
}

void MyMdHandler::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField * pDepthMarketData)
{
	std::cout << "OnRtnDepthMarketData.\n";
	if (!((pDepthMarketData->BidVolume1 > 0) && (pDepthMarketData->AskVolume1 > 0)))
		return;
}
