# CAN-Ethernet Bridge (C++)

## Purpose

Forward CAN frames received on SocketCAN (`can0`) to a TCP server socket,
and forward incoming TCP messages back onto the CAN bus.

This is the performance-critical path — designed for low latency and minimal jitter.

## Architecture

```
SocketCAN (can0)
      |
  RxThread  ──►  frame queue  ──►  TxThread (TCP)
      ▲                                  |
  TxThread (CAN)  ◄──  frame queue  ◄──  RxThread (TCP)
```

## Build

```bash
cd gateway/bridge
make
```

## Usage

```bash
./can_eth_bridge --can-iface can0 --tcp-port 5000
```

## Limitations

- TCP only in Phase 3. UDP multicast is a future option.
- No authentication on TCP socket in initial implementation (security ADR pending).

## Future Improvements

- Add TLS for secure bridge channel.
- Add UDP multicast for lower overhead.
- Add frame filtering rules per message ID.
