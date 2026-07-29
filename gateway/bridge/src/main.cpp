#include "can_socket.hpp"
#include "tcp_server.hpp"

#include <iostream>
#include <thread>
#include <atomic>
#include <csignal>

static std::atomic<bool> g_running{true};

static void signal_handler(int) { g_running = false; }

int main(int argc, char* argv[])
{
    /* Default parameters — override via CLI args when needed. */
    const std::string can_iface = (argc > 1) ? argv[1] : "can0";
    const uint16_t    tcp_port  = (argc > 2) ? static_cast<uint16_t>(std::stoi(argv[2])) : 5000;

    std::signal(SIGINT,  signal_handler);
    std::signal(SIGTERM, signal_handler);

    std::cout << "[bridge] Starting CAN-ETH bridge\n"
              << "[bridge]   CAN interface : " << can_iface << "\n"
              << "[bridge]   TCP port      : " << tcp_port  << "\n";

    try {
        sdv::gateway::CanSocket  can(can_iface);
        sdv::gateway::TcpServer  tcp(tcp_port);

        std::cout << "[bridge] Waiting for client connection...\n";
        const int client_fd = tcp.acceptClient();
        std::cout << "[bridge] Client connected.\n";

        /* CAN → TCP forwarding thread. */
        std::thread can_to_tcp([&]() {
            struct can_frame frame{};
            while (g_running) {
                if (can.read(frame)) {
                    if (!sdv::gateway::TcpServer::sendFrame(client_fd, frame)) {
                        g_running = false;
                    }
                }
            }
        });

        /* TCP → CAN forwarding thread. */
        std::thread tcp_to_can([&]() {
            struct can_frame frame{};
            while (g_running) {
                if (sdv::gateway::TcpServer::recvFrame(client_fd, frame)) {
                    can.write(frame);
                } else {
                    g_running = false;
                }
            }
        });

        can_to_tcp.join();
        tcp_to_can.join();

    } catch (const std::exception& ex) {
        std::cerr << "[bridge] Fatal: " << ex.what() << "\n";
        return 1;
    }

    std::cout << "[bridge] Shutdown complete.\n";
    return 0;
}
