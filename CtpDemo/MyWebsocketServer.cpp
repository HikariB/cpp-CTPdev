#include "MyWebsocketServer.h"



MyWebsocketServer::MyWebsocketServer()
{
	m_endpoint.set_access_channels(websocketpp::log::alevel::none);
	m_endpoint.set_error_channels(websocketpp::log::elevel::warn);
	m_endpoint.init_asio();

	m_endpoint.set_message_handler(bind(&type::onMessage, this, ::_1, ::_2));
	m_endpoint.set_fail_handler(bind(&type::onFail, this, ::_1));
	m_endpoint.set_open_handler(bind(&type::onOpen, this, ::_1));
	m_endpoint.set_close_handler(bind(&type::onClose, this, ::_1));
}


MyWebsocketServer::~MyWebsocketServer()
{
}

void MyWebsocketServer::run(int port)
{
	m_endpoint.listen(port);
	m_endpoint.start_accept();
	m_endpoint.run();
}

void MyWebsocketServer::onFail(websocketpp::connection_hdl hdl)
{
	std::lock_guard<std::mutex> lock(serverMutex);
	server::connection_ptr con = m_endpoint.get_con_from_hdl(hdl);
	std::cout << "fail handler: " << con->get_ec() << " " << con->get_ec().message() << std::endl;
}

void MyWebsocketServer::onOpen(websocketpp::connection_hdl hdl)
{
	server::connection_ptr con = m_endpoint.get_con_from_hdl(hdl);
	std::cout << "onOpen handler: "  << std::endl;
}

void MyWebsocketServer::onClose(websocketpp::connection_hdl hdl)
{
	std::cout << "onClose handler: " << std::endl;
}

void MyWebsocketServer::onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg)
{
	std::string clientMsg = msg->get_payload();
	try
	{
		std::cout << clientMsg << std::endl;
		this->sendTextMessage(hdl, clientMsg);
	}
	catch (const std::exception&)
	{

	}
}

void MyWebsocketServer::sendTextMessage(websocketpp::connection_hdl hdl, const std::string & msg)
{
	m_endpoint.send(hdl, msg, websocketpp::frame::opcode::text);
}



