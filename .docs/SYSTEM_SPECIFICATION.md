# System Specification

**Version:** 0.2

**Date:** 2026-07-29

**Status:** Active

---

## Purpose

Define the baseline technical specification for the Software Defined Vehicle (SDV) thesis platform.

This document is the primary requirements reference. All implementation decisions must trace back to a requirement defined here.

---

## Scope

This specification covers:

- Embedded ECUs (STM32 firmware)
- Gateway and networking (Raspberry Pi)
- Diagnostics and data paths
- Software architecture boundaries
- Performance targets and verification criteria

It does not define production hardware certification requirements (ISO 26262 compliance is out of scope).

---

## System Overview

The platform implements a miniature SDV architecture with distributed ECUs connected by CAN and a centralised Linux gateway.

High-level topology:

```
Laptop (Diagnostics GUI / Tooling)
          |
       Ethernet (TCP port 5000)
          |
    Raspberry Pi 5 (Gateway)
     /        |         \
  bridge    diag      logger
     \        |         /
          SocketCAN (can0)
              |
          CAN Bus 500 kbps
         /    |    |    \
       BCM  Cluster HVAC Battery
      STM32  STM32 STM32  STM32
```

---

## Functional Requirements

| ID | Requirement |
|----|-------------|
| REQ-SYS-001 | ECU firmware shall execute on STM32-class ARM Cortex-M microcontrollers. |
| REQ-SYS-002 | ECU task scheduling shall provide deterministic periodic execution using a preemptive RTOS. |
| REQ-SYS-003 | In-vehicle ECU communication shall use CAN 2.0B at 500 kbps baseline bitrate. |
| REQ-SYS-004 | The gateway shall bridge CAN frames from SocketCAN to a TCP endpoint accessible on the local Ethernet network. |
| REQ-SYS-005 | The platform shall support UDS diagnostics (ISO 14229) over ISO-TP (ISO 15765-2) on CAN. |
| REQ-SYS-006 | The gateway shall log all CAN frames with microsecond-resolution timestamps to persistent storage. |
| REQ-SYS-007 | The Body Control Module ECU shall transmit door and lighting status frames at a fixed periodic rate. |
| REQ-SYS-008 | The Battery ECU shall transmit voltage, current, temperature, and SoC frames at a fixed periodic rate. |
| REQ-SYS-009 | The HVAC ECU shall transmit cabin temperature and fan speed frames and receive climate set-point commands. |
| REQ-SYS-010 | The Instrument Cluster ECU shall transmit vehicle status and warning indicator frames. |
| REQ-SYS-011 | The gateway shall support OTA firmware update delivery to STM32 ECUs in Phase 5. |

---

## Non-Functional Requirements

| ID | Requirement |
|----|-------------|
| REQ-NFR-001 | ECU firmware shall use only static memory allocation on embedded targets (no heap allocation after init). |
| REQ-NFR-002 | ISR execution time shall not exceed 10 µs on any ECU (measured with logic analyser or DWT cycle counter). |
| REQ-NFR-003 | The firmware shall follow an AUTOSAR-inspired layered architecture: Application → Services → Communication → Drivers → HAL. |
| REQ-NFR-004 | Gateway CAN-to-TCP forwarding latency shall not exceed 5 ms at nominal bus load (< 30% utilisation). |
| REQ-NFR-005 | The complete platform (hardware + software) shall be reproducible within a €500 budget using open-source tools only. |
| REQ-NFR-006 | Every firmware module shall include inline Doxygen documentation covering: Purpose, Interfaces, Dependencies, Configuration, Limitations. |
| REQ-NFR-007 | All benchmarking workflows shall be reproducible from scripts in `/scripts` without manual steps. |

---

## Architecture Constraints

- No dependency on proprietary AUTOSAR toolchains (AUTOSAR-inspired layering only)
- Gateway language split: C++17 for performance-critical bridge, Python 3 for tooling (ADR-006)
- CAN transceiver: SN65HVD230 for 3.3 V STM32 compatibility (ADR-005)
- Gateway platform: Raspberry Pi 5 running Raspberry Pi OS (ADR-004)
- ECU platform: STM32 Nucleo boards, C17, FreeRTOS (ADR-001, ADR-002)

---

## Interfaces

### ECU Internal

- **Driver APIs:** `CAN_Driver_Init()`, `CAN_Driver_Transmit()`, `CAN_Driver_Receive()` — see `firmware/shared/can/can_driver.h`
- **Service-level:** FreeRTOS task creation, `vTaskDelayUntil`, queue-based ISR-to-task signalling
- **Application-level:** Per-ECU `<ecu>_App_Init()` and `<ecu>_App_Task()` functions

### Gateway Interfaces

- **SocketCAN:** `can0` interface at 500 kbps — consumed by bridge, diagnostics, and logger
- **TCP endpoint:** `0.0.0.0:5000` — raw `can_frame` structs streamed to/from laptop
- **Config:** `gateway/config/gateway_config.yaml` — single source of truth for all runtime parameters

### CAN Message Interface

| ECU | TX ID Range | RX ID Range |
|-----|-------------|-------------|
| BCM | 0x100–0x103 | — |
| Instrument Cluster | 0x200–0x202 | — |
| HVAC | 0x300–0x301 | 0x302 |
| Battery | 0x400–0x403 | — |
| Diagnostics | — | 0x7DF (functional) |
| ECU Responses | 0x7E8+ | — |

---

## Performance Targets

| Metric | Target | Measurement Method |
|--------|--------|--------------------|
| CAN baseline bitrate | 500 kbps | `ip link show can0` |
| ECU app task period | 10 ms ± 1 ms | FreeRTOS tick trace or logic analyser |
| ISR worst-case execution | < 10 µs | STM32 DWT cycle counter |
| Gateway forwarding latency (nominal load) | < 5 ms | Timestamped log comparison (send vs receive) |
| Gateway forwarding latency (80% bus load) | < 20 ms | Stress test with `cangen` |
| Bus utilisation at nominal operation | < 30% | `can-utils` bus statistics |

---

## Verification Strategy

| Test Type | Scope | Tool |
|-----------|-------|------|
| Unit tests | Protocol and utility modules | Unity (C), pytest (Python) |
| Integration tests | ECU ↔ Gateway CAN path | `candump`, `cansend`, pytest |
| Latency benchmarks | Gateway forwarding jitter | `can_logger.py` + post-processing |
| Bus-load stress tests | CAN bus saturation behaviour | `cangen` (can-utils) |
| Fault injection | CAN disconnect, malformed frames | Manual + scripted |
| Stability tests | 24-hour continuous operation | Automated logging |

---

## Open Items

| ID | Item | Blocking Phase |
|----|------|----------------|
| OI-001 | Final STM32 Nucleo variant selection (F446RE vs G474RE) | Phase 2 |
| OI-002 | OTA strategy and bootloader architecture (ADR-007 proposed) | Phase 5 |
| OI-003 | IPC mechanism between gateway bridge and diagnostics service | Phase 4 |
| OI-004 | Security architecture (TLS, CAN IDS) | Phase 5 |

---

## Traceability

| Document | Relationship |
|----------|--------------|
| `.docs/PROJECT.md` | Vision and objectives |
| `.docs/ROADMAP.md` | Phase timeline |
| `.docs/DECISIONS.md` | Rationale for architecture constraints |
| `firmware/shared/` | Implements REQ-SYS-001 to REQ-SYS-003, REQ-NFR-001 to REQ-NFR-003 |
| `gateway/` | Implements REQ-SYS-004 to REQ-SYS-006, REQ-NFR-004 |
