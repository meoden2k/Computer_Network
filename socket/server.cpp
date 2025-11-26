#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_THREAD_
#define ASIO_HAS_STD_TYPE_TRAITS 1
#define ASIO_HAS_STD_SHARED_PTR 1
#define ASIO_HAS_STD_FUNCTION 1
#define ASIO_HAS_STD_SYSTEM_ERROR 1
#define ASIO_HAS_STD_ARRAY 1
#define ASIO_HAS_STD_CHRONO 1
#define ASIO_HAS_STD_ADDRESSOF 1
#define ASIO_HAS_STD_ATOMIC 1

#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_THREAD_
#define _WEBSOCKETPP_NO_EXCEPTIONS_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    std::string received = msg->get_payload();
    std::cout << "Received: " << received << std::endl;

    // Gửi trả lại client
    s->send(hdl, "Server received: " + received, websocketpp::frame::opcode::text);
}

int main() {

    //----> COMPILE = g++ -std=c++17 -I./ -I./asio/include server.cpp -o server.exe -lmswsock  -lws2_32
    
    server s;

    try {
        s.init_asio();
        s.set_message_handler(std::bind(&on_message, &s, std::placeholders::_1, std::placeholders::_2));

        s.listen(9000);          // Cổng server
        s.start_accept();

        std::cout << "Server running at ws://localhost:9000\n";
        s.run();  // chạy event loop
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
