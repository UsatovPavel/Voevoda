#include "httpServer.h"
#include "DataManeger.h"

void http_server::HttpServer::start(std::string addr, int port) {
    m_app.bindaddr(addr);
    CROW_ROUTE(m_app, "/register")
        .methods("POST"_method)
        ([](const crow::request& req) {
        auto requestJson = crow::json::load(req.body);
        crow::json::wvalue responseJson;

        std::string username = requestJson["username"].s();
        std::string password = requestJson["password"].s();
        if (!requestJson || username.empty() || password.empty()) {
            responseJson["message"] = "Bad request";
            return crow::response(400, responseJson);
        }
        
        if (data_maneger::DataManager::checkUser(username)) {
            responseJson["message"] = "User already registered";
            return crow::response(400, responseJson);
        }
        
        data_maneger::DataManager::insertUser({0, username, password});
        
        responseJson["message"] = "User registered successfully";
        return crow::response(200, responseJson);
        });

    CROW_ROUTE(m_app, "/login")
        .methods("POST"_method)
        ([](const crow::request& req) {
        auto requestJson = crow::json::load(req.body);
        crow::json::wvalue responseJson;

        std::string username = requestJson["username"].s();
        std::string password = requestJson["password"].s();
        if (!requestJson || username.empty() || password.empty()) {
            responseJson["message"] = "Bad request";
            return crow::response(400, responseJson);
        }

        User cur_user = data_maneger::DataManager::getUser(username);
        // std::cout << "found " << cur_user.id << " " << cur_user.username << " " << cur_user.password << "\n";
        if (cur_user.username != username) {
            responseJson["message"] = "No such user, check login";
            return crow::response(400, responseJson);
        }

        if (cur_user.password != password) {
            responseJson["message"] = "Wrong password";
            return crow::response(400, responseJson);
        }

        responseJson["message"] = "User logined successfully";
        return crow::response( 200, responseJson );
            });

    CROW_ROUTE(m_app, "/gotStats")
        .methods("POST"_method)
        ([](const crow::request& req) {
        std::cout << req.body << "\n";
        
        auto requestJson = crow::json::load(req.body);
        
        crow::json::wvalue responseJson;

        std::string username = requestJson["name"].s();
        long long userScore = requestJson["score"].i();
        if (!requestJson || username.empty()) {
            responseJson["message"] = "Bad request";
            return crow::response(400, responseJson);
        }
        responseJson["message"] = "Got stats successfully";
        return crow::response(200, responseJson);
            });

    m_app.port(port).multithreaded().run();
}

void http_server::HttpServer::stop() {

}

int main() {
    http_server::HttpServer VoevodaServer;
    VoevodaServer.start();
}
