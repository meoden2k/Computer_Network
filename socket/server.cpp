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

#include "../application/ListApp.cpp"  // Chèn hàm liệt kê ứng dụng đã cài đặt
#include "../application/StartApp.cpp" // Chèn hàm khởi động ứng dụng

#include <iostream>
#include <string>

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    std::string received = msg->get_payload();
    std::cout << "Received: " << received << std::endl;
    if (received == "list_apps") {
        // Gọi hàm liệt kê ứng dụng và gửi kết quả về client
        std::string app_list = ListApplication(); // Giả sử hàm này trả về danh sách ứng dụng đã cài đặt
        s->send(hdl, app_list, msg->get_opcode());
    }

    if (received.rfind("start_app:", 0) == 0) {
        std::string app_to_start = received.substr(10); // Lấy tên ứng dụng sau "start_app:"
        StartApplication(app_to_start); // Giả sử hàm này khởi động ứng dụng
        s->send(hdl, "Starting application: " + app_to_start, msg->get_opcode());
    }

}

int main() {

    //----> COMPILE = g++ -std=c++17 -I./ -I./asio/include server.cpp -o server.exe -lmswsock  -lws2_32
    
    server s;

    try {
        // comment 2 dong nay roi chay List App se ra chu TRUNG QUOC
        s.clear_access_channels(websocketpp::log::alevel::all);
        s.clear_error_channels(websocketpp::log::elevel::all);

        s.init_asio();
        s.set_message_handler(std::bind(&on_message, &s, std::placeholders::_1, std::placeholders::_2));

        s.listen(9000);          // Cổng server
        s.start_accept();

        std::cout << "Server running at ws://localhost:9000\n";
        s.run();  // chạy event loop
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
