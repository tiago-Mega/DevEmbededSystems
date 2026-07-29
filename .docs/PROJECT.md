# Software Defined Vehicle (SDV) Platform

## Project Information

**Project Name:** Software Defined Vehicle Platform

**Degree:** MSc Electrical and Computer Engineering

**Status:** Phase 2 — Hardware Selection & CAN Bring-Up

**Version:** 0.2

**Last Updated:** 2026-07-29

---

# Vision

Design and implement a miniature Software Defined Vehicle (SDV) platform that demonstrates the transition from traditional distributed Electronic Control Units (ECUs) toward centralized automotive computing.

The project should emphasize:

- Embedded Systems Engineering
- Automotive Networking
- Real-Time Systems
- Embedded Linux
- Software Architecture
- AUTOSAR-inspired design
- Diagnostics
- Gateway development

The system should be modular and expandable throughout the duration of the master's project.

---

# Long-Term Objectives

Develop practical experience with:

- Embedded C17
- Modern C++17
- STM32 (ARM Cortex-M)
- FreeRTOS
- Raspberry Pi 5 (Linux)
- CAN / CAN FD
- Automotive Ethernet
- TCP/IP
- UDS / ISO-TP
- SocketCAN
- AUTOSAR concepts
- Embedded debugging
- System integration

---

# Research Goal

Investigate modern Software Defined Vehicle architectures.

Possible research topics include:

- Gateway forwarding latency (CAN → Ethernet)
- CAN versus CAN FD throughput comparison
- Centralized vs distributed computing tradeoffs
- ECU scalability under increasing bus load
- Network utilisation benchmarking
- Fault tolerance and recovery behaviour
- Modular AUTOSAR-inspired software architectures

These research questions will be narrowed to a primary thesis question in Phase 6.

---

# Current System Architecture

```
Laptop (Diagnostics / Tooling)
          |
       Ethernet (TCP)
          |
    Raspberry Pi 5 (Gateway)
     /        |        \
  bridge    diag     logger
          |
       SocketCAN (can0)
          |
       CAN Bus (500 kbps)
       /   |   |   \
     BCM  CLU HVAC BAT
     STM32 ECUs
```

---

# Planned ECUs

## Body Control Module (BCM)

- Doors, Windows, Interior Lighting, Hazard Lights
- CAN TX: 0x100–0x103

## Instrument Cluster

- Dashboard Display, Warning Indicators, Vehicle Status
- CAN TX: 0x200–0x202

## HVAC ECU

- Cabin Temperature, Fan Speed, Climate Simulation
- CAN TX: 0x300–0x301 | RX: 0x302

## Battery ECU

- Voltage, Current, Temperature, State of Charge
- CAN TX: 0x400–0x403

## Future ECUs

- ABS, Steering, Infotainment, ADAS, Engine Simulator

---

# Networking

- **Primary:** CAN 2.0B at 500 kbps (ADR-003)
- **Future:** CAN FD, Automotive Ethernet, SOME/IP
- **Diagnostics:** UDS over ISO-TP (Phase 4)
- **Gateway:** CAN ↔ Ethernet bridge (Phase 4)

---

# Embedded Software

- **MCU:** STM32 Nucleo (ADR-001) — F446RE or G474RE (OI-001)
- **Language:** C17
- **RTOS:** FreeRTOS (ADR-002)
- **Transceiver:** SN65HVD230 at 3.3 V (ADR-005)

**Architecture layers:**

```
Application
     ↓
Services
     ↓
Communication   ← can_driver.h
     ↓
Drivers
     ↓
HAL             ← STM32CubeIDE / CubeMX generated
```

---

# Raspberry Pi Gateway

- **Platform:** Raspberry Pi 5 (ADR-004)
- **OS:** Raspberry Pi OS (Linux)
- **Languages:** C++17 (bridge), Python 3 (diagnostics, logging)
- **CAN interface:** MCP2515-based HAT (Waveshare 2-CH CAN HAT or equivalent)

---

# Design Principles

- Modularity
- Simplicity
- Maintainability
- Testability
- Documentation
- Reusability

---

# Coding Standards

**Embedded (C17):**

- Static allocation only
- No recursion
- No dynamic allocation after init
- ISRs ≤ 10 µs execution time
- Separate hardware abstraction (HAL never called above Driver layer)

**Gateway (C++17 / Python 3):**

- C++17 for performance-critical bridge (RAII, no raw owning pointers)
- Python 3 for tooling and diagnostics
- Modular service design

---

# Testing Strategy

Every subsystem must include:

- Unit testing (Unity for C, pytest for Python)
- Integration testing (ECU ↔ Gateway)
- Latency benchmarking
- Stress testing (`cangen` bus load)
- Fault injection
- 24-hour stability testing

---

# Documentation

Every module must include Doxygen-compatible header with:

- Purpose
- Interfaces
- Dependencies
- Communication (CAN IDs if applicable)
- Configuration
- Limitations
- Future Improvements

---

# Milestones

## Phase 1 — Research & Architecture ✅

- Literature review
- Architecture proposal
- Hardware comparison
- ADR-001 to ADR-004 accepted

**Deliverable:** Architecture proposal + documented ADRs

---

## Phase 2 — Hardware & CAN Bring-Up 🔄 (Current)

- Purchase STM32 Nucleo boards and SN65HVD230 transceivers
- Purchase Raspberry Pi 5 + CAN HAT
- Bring up physical CAN bus
- Verify BCM ECU transmits CAN frames (candump)
- Complete `can_driver.c` implementation

**Done when:** BCM transmits 0x100 frame at 10 ms cycle, verified with `candump can0`

---

## Phase 3 — Full ECU Firmware

- Implement Cluster, HVAC, Battery ECU app tasks
- Multi-ECU CAN bus verified
- FreeRTOS task timing verified

**Done when:** All 4 ECUs transmit on bus simultaneously, no frame loss at nominal load

---

## Phase 4 — Gateway & Diagnostics

- SocketCAN + CAN HAT bring-up on RPi 5
- `can_eth_bridge` compiled and tested
- `can_logger.py` captures timestamped frames
- UDS TesterPresent (0x3E) verified end-to-end

**Done when:** Laptop receives CAN frames over TCP, logger writes CSV, UDS session opens

---

## Phase 5 — OTA & Integration

- OTA bootloader architecture (ADR-007)
- System integration test
- Performance optimisation
- Security hardening

**Done when:** Firmware update delivered to one ECU over CAN from RPi

---

## Phase 6 — Evaluation & Thesis

- Benchmarking experiments
- Data collection and analysis
- Thesis writing
- Final validation

**Done when:** Thesis submitted

---

# Stretch Goals

- AUTOSAR-like RTE
- CAN FD migration
- SOME/IP
- Automotive Ethernet
- Secure Boot
- Intrusion Detection System
- TinyML on RPi
- Qt Dashboard

---

# Repository Structure

```
.docs/       ← Project documentation and ADRs
firmware/    ← STM32 ECU firmware (C17 + FreeRTOS)
gateway/     ← Raspberry Pi gateway (C++17 + Python)
tests/       ← System-level tests
hardware/    ← Schematics, BOM, transceiver datasheets
scripts/     ← Build automation, flash scripts, benchmarking
tools/       ← DBC files, diagnostics tooling
thesis/      ← Research writing and experiments
```

---

# Current Sprint

**Sprint Goal:** Complete firmware scaffold and begin hardware procurement.

**Current Focus:**
- ✅ `/firmware` scaffolded (BCM fully stubbed, shared drivers defined)
- ✅ `/gateway` scaffolded (C++ bridge, Python diagnostics/logger)
- ✅ ADR-005 (SN65HVD230), ADR-006 (language split), ADR-007 (OTA proposed)
- ⬜ Implement `can_driver.c` (STM32 HAL CAN implementation)
- ⬜ Implement `tcp_server.cpp` (gateway TCP implementation)
- ⬜ Procure hardware: STM32 Nucleo + SN65HVD230 + RPi 5 CAN HAT

**Next Milestone:** BCM transmits 0x100 frame verified with `candump`

**Current Blockers:** Hardware not yet procured
