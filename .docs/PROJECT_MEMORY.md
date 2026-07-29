# Project Memory

**Last Updated:** 2026-07-29

This file is a live AI context snapshot. It must be updated at the start of each working session to reflect the current project state.

---

## Current Project Status

**Phase:** 2 — Hardware Selection & CAN Bring-Up

**Sprint Goal:** Implement `can_driver.c` and `tcp_server.cpp`, procure hardware

---

## Hardware (Confirmed)

| Component | Selection | Status |
|-----------|-----------|--------|
| Gateway | Raspberry Pi 5 (4 GB) | Confirmed (ADR-004) |
| ECU Platform | STM32 Nucleo (F446RE or G474RE) | Pending final selection (OI-001) |
| CAN Transceiver | SN65HVD230 | Confirmed (ADR-005) |
| CAN HAT (RPi) | Waveshare 2-CH CAN HAT (MCP2515) | Proposed |
| CAN Network | 500 kbps, classic CAN 2.0B | Confirmed (ADR-003) |

---

## Software Stack

| Layer | Technology | Status |
|-------|-----------|--------|
| ECU firmware | C17 + FreeRTOS on STM32 | Scaffolded |
| CAN driver | `can_driver.h` defined | Implementation pending |
| Gateway bridge | C++17 (`can_socket.cpp` done) | `tcp_server.cpp` pending |
| Gateway diagnostics | Python + `python-can` + `udsoncan` | Stubbed |
| Gateway logger | Python + `python-can` | Complete |
| Config | `gateway_config.yaml` | Complete |

---

## Current Architecture

```
Laptop → Ethernet (TCP:5000) → RPi 5 Gateway → SocketCAN (can0) → CAN 500kbps → STM32 ECUs
```

---

## Progress Checklist

- ✅ Architecture Planning (Phase 1)
- ✅ ADR-001 to ADR-006 accepted
- ✅ `/firmware` scaffolded
- ✅ `/gateway` scaffolded
- ⬜ Hardware procured
- ⬜ `can_driver.c` implemented
- ⬜ `tcp_server.cpp` implemented
- ⬜ Physical CAN bus verified
- ⬜ Gateway bring-up
- ⬜ Diagnostics (Phase 4)
- ⬜ OTA (Phase 5)
- ⬜ Performance testing (Phase 6)

---

## Budget

| Item | Estimated Cost |
|------|---------------|
| Raspberry Pi 5 (4 GB) | €65 |
| RPi CAN HAT (Waveshare) | €20 |
| STM32 Nucleo x4 | €80 (€20 each) |
| SN65HVD230 transceivers x4 | €10 |
| CAN bus wiring + connectors | €10 |
| Miscellaneous | €15 |
| **Total estimated** | **€200** |
| **Budget remaining** | **€300** |

---

## Constraints

- Budget: under €500 total
- Open-source software only
- No proprietary AUTOSAR tools
- Emphasis on educational and research value

---

## Known Unknowns

| ID | Unknown | Blocking |
|----|---------|----------|
| OI-001 | Final STM32 Nucleo variant (F446RE vs G474RE) | Phase 2 hardware order |
| OI-002 | OTA bootloader architecture | Phase 5 |
| OI-003 | IPC between gateway bridge and diagnostics | Phase 4 |
| OI-004 | Security architecture (TLS, CAN IDS) | Phase 5 |
