#pragma once
/**
 * @file    can_socket.hpp
 * @brief   POSIX SocketCAN interface wrapper.
 *
 * Purpose:      Open a SocketCAN socket and send/receive raw CAN frames.
 * Dependencies: Linux kernel headers (<linux/can.h>), POSIX sockets.
 * Limitations:  Classic CAN 2.0B only. CAN FD is a future extension.
 */

#include <cstdint>
#include <string>
#include <linux/can.h>

namespace sdv::gateway {

class CanSocket {
public:
    /**
     * @brief Construct and open a SocketCAN socket on the given interface.
     * @param iface  Interface name, e.g. "can0".
     * @throws std::runtime_error if the socket cannot be opened or bound.
     */
    explicit CanSocket(const std::string& iface);
    ~CanSocket();

    CanSocket(const CanSocket&)            = delete;
    CanSocket& operator=(const CanSocket&) = delete;

    /**
     * @brief Read one CAN frame (blocking).
     * @param frame  Output frame.
     * @return true on success, false on error or socket close.
     */
    bool read(struct can_frame& frame) const;

    /**
     * @brief Write one CAN frame to the bus.
     * @param frame  Frame to transmit.
     * @return true on success.
     */
    bool write(const struct can_frame& frame) const;

    int fd() const { return fd_; }

private:
    int fd_{-1};
};

} // namespace sdv::gateway
