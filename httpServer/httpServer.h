#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include <iostream>
#include <regex>
#include <thread>
#include <string>

#include "libs/crow_all.h"
#include "libs/json.hpp"

namespace http_server {

class HttpServer {
public:
	void start(std::string addr = "127.0.0.1", int port = 18080);
	void stop();
private:
	crow::SimpleApp m_app;

};

}

#endif // !HTTP_SERVER_H_
