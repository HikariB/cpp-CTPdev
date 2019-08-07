#pragma once
#include <iostream>
#include <string>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <mutex>

struct ClientLogin
{
	std::string userId;
	std::string password;
};

struct SubScriptionTopic
{
	std::string accountId;
	std::string instrumentId;
};

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::server<websocketpp::config::asio> server;


class MyWebsocketServer
{
public:
	typedef MyWebsocketServer type;
	
	MyWebsocketServer();
	~MyWebsocketServer();
	void run(int port);
	void onFail(websocketpp::connection_hdl hdl);
	void onOpen(websocketpp::connection_hdl hdl);
	void onClose(websocketpp::connection_hdl hdl);
	void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
	void sendTextMessage(websocketpp::connection_hdl hdl, const std::string &msg);
	//void onClientLoginRequeset(ClientLogin &, websocketpp::connection_hdl);
	//void onClientSubscribeRequest(SubScriptionTopic &, websocketpp::connection_hdl);

	


private:
	server m_endpoint;
	std::mutex serverMutex;
};

