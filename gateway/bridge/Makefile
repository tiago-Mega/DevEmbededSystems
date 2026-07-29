CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
TARGET   := can_eth_bridge
SRCS     := src/main.cpp src/can_socket.cpp
HDRS     := src/can_socket.hpp src/tcp_server.hpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
