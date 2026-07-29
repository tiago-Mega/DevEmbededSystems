# Gateway

This directory contains all software running on the Raspberry Pi Central Vehicle Computer.

The gateway bridges the CAN bus (connected to STM32 ECUs) with Ethernet (connected to the laptop tooling).

---

## Directory Structure

```
gateway/
├── bridge/          # C++ CAN-to-Ethernet forwarding core (performance-critical)
├── diagnostics/     # Python UDS/ISO-TP diagnostics service
├── logging/         # Python timestamped CAN message logger
├── config/          # Runtime configuration files
└── tests/           # Gateway-level integration tests
```

---

## Responsibilities

- Forward CAN frames from SocketCAN to Ethernet (TCP/UDP) endpoints
- Receive diagnostic requests from laptop and route via ISO-TP to ECUs
- Log timestamped CAN messages for research experiments
- Expose vehicle data for visualization and OTA (future)

---

## Language Split

| Component       | Language | Rationale                                      |
|-----------------|----------|------------------------------------------------|
| CAN-ETH Bridge  | C++17    | Low-latency forwarding, minimal jitter         |
| Diagnostics     | Python   | Rapid iteration, UDS library ecosystem         |
| Logging         | Python   | Simple, readable, easy to extend               |
| Config / Tools  | Python   | Scripting and automation                       |

> ADR for language split is pending. See `.docs/DECISIONS.md`.

---

## Interface Overview

```
Laptop (Diagnostics GUI / Logger)
          |
       Ethernet (TCP)
          |
    Raspberry Pi Gateway
     /             \
  bridge/        diagnostics/ logging/
     |                  |
  SocketCAN          SocketCAN
     |
  CAN Bus
     |
  STM32 ECUs
```

---

## Dependencies

### System (Raspberry Pi OS)

- `can-utils` — SocketCAN utilities (`candump`, `cansend`)
- `linux-can` kernel modules
- `libsocketcan` (optional C++ binding)
- Python 3.10+
- `python-can` — Python CAN bus library
- `udsoncan` — Python UDS implementation

### C++ Bridge

- C++17 compiler (`g++`)
- POSIX sockets
- `<linux/can.h>` kernel headers

---

## Setup

```bash
# Enable CAN interface (replace can0 with your interface)
sudo ip link set can0 up type can bitrate 500000

# Verify
ip link show can0
candump can0
```

---

## Related Documents

- `.docs/PROJECT.md`
- `.docs/SYSTEM_SPECIFICATION.md`
- `.docs/DECISIONS.md` (ADR-004, gateway language ADR pending)
