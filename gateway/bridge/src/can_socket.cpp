#include "can_socket.hpp"

#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

namespace sdv::gateway {

CanSocket::CanSocket(const std::string& iface)
{
    fd_ = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (fd_ < 0) {
        throw std::runtime_error("CanSocket: failed to open socket");
    }

    struct ifreq ifr{};
    std::strncpy(ifr.ifr_name, iface.c_str(), IFNAMSIZ - 1);
    if (::ioctl(fd_, SIOCGIFINDEX, &ifr) < 0) {
        ::close(fd_);
        throw std::runtime_error("CanSocket: interface not found: " + iface);
    }

    struct sockaddr_can addr{};
    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (::bind(fd_, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd_);
        throw std::runtime_error("CanSocket: bind failed");
    }
}

CanSocket::~CanSocket()
{
    if (fd_ >= 0) {
        ::close(fd_);
    }
}

bool CanSocket::read(struct can_frame& frame) const
{
    const ssize_t nbytes = ::read(fd_, &frame, sizeof(frame));
    return nbytes == static_cast<ssize_t>(sizeof(frame));
}

bool CanSocket::write(const struct can_frame& frame) const
{
    const ssize_t nbytes = ::write(fd_, &frame, sizeof(frame));
    return nbytes == static_cast<ssize_t>(sizeof(frame));
}

} // namespace sdv::gateway
