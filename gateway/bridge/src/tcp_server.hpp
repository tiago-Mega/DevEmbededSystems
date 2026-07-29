#pragma once
/**
 * @file    tcp_server.hpp
 * @brief   Simple TCP server for CAN frame forwarding to laptop tooling.
 *
 * Purpose:      Accept one client connection and stream CAN frames over TCP.
 * Dependencies: POSIX sockets.
 * Limitations:  Single client only in Phase 3.
 */

#include <cstdint>
#include <linux/can.h>

namespace sdv::gateway {

class TcpServer {
public:
    /**
     * @brief Create a TCP server socket and listen on the given port.
     * @param port  TCP port number.
     * @throws std::runtime_error on socket/bind/listen failure.
     */
    explicit TcpServer(uint16_t port);
    ~TcpServer();

    TcpServer(const TcpServer&)            = delete;
    TcpServer& operator=(const TcpServer&) = delete;

    /**
     * @brief Block until one client connects. Returns client fd.
     * @return Connected client file descriptor.
     */
    int acceptClient() const;

    /**
     * @brief Send a CAN frame to the connected client.
     * @param client_fd  File descriptor returned by acceptClient().
     * @param frame      Frame to send.
     * @return true on success.
     */
    static bool sendFrame(int client_fd, const struct can_frame& frame);

    /**
     * @brief Receive a CAN frame from the connected client.
     * @param client_fd  Client file descriptor.
     * @param frame      Output frame.
     * @return true on success, false on disconnect or error.
     */
    static bool recvFrame(int client_fd, struct can_frame& frame);

private:
    int server_fd_{-1};
};

} // namespace sdv::gateway
