# Engineering Decision Log

This document records important engineering decisions made throughout the project.

The goal is to document **why** a decision was made rather than simply recording what was implemented.

All ADRs must include a date, status, rationale, and at least two alternatives considered.

---

# Decision Template

## ADR-000

**Date:** YYYY-MM-DD

**Status:** Proposed | Accepted | Rejected | Superseded

---

### Decision

Describe the engineering decision in one sentence.

### Context

Why is this decision necessary? What problem is being solved?

### Alternatives Considered

**Option A**
- Advantages:
- Disadvantages:

**Option B**
- Advantages:
- Disadvantages:

### Rationale

Why was the chosen solution selected over the alternatives?

### Consequences

- **Positive:**
- **Negative:**
- **Future implications:**

### Related Components

- Firmware / Gateway / Networking / Documentation / Testing

---

# Decision Log

---

## ADR-001

**Date:** 2026-07-19

**Status:** Accepted

### Decision

Use STM32 Nucleo boards as the ECU development platform.

### Context

The project requires multiple independent ECUs that are inexpensive, supported by mature tooling, and representative of real automotive microcontrollers. The platform must support CAN peripherals, FreeRTOS, and C17 development.

### Alternatives Considered

**ESP32**
- Advantages: Built-in Wi-Fi, very low cost, large hobbyist community
- Disadvantages: Not representative of automotive-grade MCUs; Xtensa architecture differs significantly from ARM Cortex-M used in production ECUs

**NXP S32K Automotive Boards**
- Advantages: Industry-standard automotive MCU, AUTOSAR-qualified, CAN FD native support
- Disadvantages: High cost (>€100/board), limited open-source tooling, steep learning curve for academic timelines

### Rationale

STM32 Nucleo boards provide an optimal balance between cost (€15–€25/board), ARM Cortex-M architecture (representative of automotive targets), HAL maturity, STM32CubeIDE tooling, and extensive community documentation. The Nucleo-F446RE and Nucleo-G474RE both offer native CAN/CAN FD peripherals suitable for Phase 2 and future CAN FD work.

### Consequences

- **Positive:** Large ecosystem, excellent debugging (ST-Link on-board), FreeRTOS and CubeMX integration, low cost enables multiple ECUs within budget
- **Negative:** Not automotive-qualified hardware; results are not directly transferable to production without re-validation on certified MCUs
- **Future implications:** If CAN FD is required (stretch goal), prefer Nucleo-G474RE which has FDCAN peripheral natively

### Related Components

- Firmware (`firmware/shared/`, `firmware/bcm/`, etc.)
- Hardware selection (BOM, schematics in `/hardware`)

---

## ADR-002

**Date:** 2026-07-19

**Status:** Accepted

### Decision

Use FreeRTOS as the real-time operating system for all STM32 ECUs.

### Context

Each ECU must execute multiple concurrent tasks with deterministic timing — CAN Rx handling, application logic, and diagnostics hooks must not block each other. A cooperative or preemptive scheduler is required.

### Alternatives Considered

**Bare Metal (super-loop)**
- Advantages: Zero RTOS overhead, simplest possible execution model, no context-switch jitter
- Disadvantages: Does not scale to multiple tasks; adding diagnostics or logging to a bare-metal loop introduces coupling and timing interference

**Zephyr RTOS**
- Advantages: Modern RTOS with strong safety and networking features, growing automotive adoption
- Disadvantages: Significantly higher learning curve, larger footprint, less native STM32CubeIDE integration at project start

### Rationale

FreeRTOS is the industry's most widely deployed embedded RTOS, is directly integrated into STM32CubeIDE via CubeMX, and provides sufficient task isolation and determinism for this platform's requirements. Its MIT license satisfies the open-source constraint.

### Consequences

- **Positive:** Clean task separation (CAN Rx, App, Diagnostics), `vTaskDelayUntil` enables deterministic periodic execution, scales easily as ECU features grow
- **Negative:** Adds learning curve for stack sizing, priority assignment, and avoiding priority inversion; requires careful ISR-to-task notification design
- **Future implications:** FreeRTOS+TCP is available if lightweight TCP/IP stack is needed on ECU side in future phases

### Related Components

- `firmware/shared/rtos/task_config.h`
- All ECU `main.c` files

---

## ADR-003

**Date:** 2026-07-19

**Status:** Accepted

### Decision

Use CAN (ISO 11898, 500 kbps) as the primary in-vehicle ECU communication network.

### Context

The platform must implement realistic automotive inter-ECU communication. The chosen protocol must support multi-master broadcast, deterministic arbitration, and be affordable to implement with STM32 hardware.

### Alternatives Considered

**UART point-to-point**
- Advantages: Simplest to implement, no external transceiver needed
- Disadvantages: Not a bus topology; cannot model realistic multi-ECU automotive networks; no broadcast or arbitration

**LIN Bus**
- Advantages: Very low cost, used in automotive body electronics
- Disadvantages: Master-slave only, 20 kbps maximum — not representative of modern ECU backbone networks

**Ethernet only**
- Advantages: High bandwidth, directly maps to Automotive Ethernet research direction
- Disadvantages: Requires additional hardware (switch), does not reflect current ECU deployment reality; CAN remains dominant in production vehicles

### Rationale

CAN remains the backbone network in the vast majority of production vehicles. Implementing CAN accurately reflects the domain, enables direct comparison with literature, and is supported natively by all chosen STM32 targets. The 500 kbps baseline matches the most common automotive deployment.

### Consequences

- **Positive:** Realistic network behaviour, direct comparison with published benchmarks, native STM32 CAN peripheral, low-cost transceivers
- **Negative:** 8-byte payload limit constrains message design; 500 kbps limits total bus throughput in multi-ECU stress tests
- **Future implications:** CAN FD (up to 8 Mbps, 64-byte payload) is a stretch goal and a direct research comparison point

### Related Components

- `firmware/shared/can/can_ids.h`
- `firmware/shared/can/can_driver.h`
- `gateway/bridge/` (SocketCAN consumer)

---

## ADR-004

**Date:** 2026-07-19

**Status:** Accepted

### Decision

Use Raspberry Pi 5 as the Central Vehicle Computer (gateway).

### Context

The gateway must run Linux, support SocketCAN (via CAN HAT), provide Ethernet connectivity to the laptop, host diagnostics and logging services, and support future OTA. It must be affordable and within the €500 project budget.

### Alternatives Considered

**Jetson Nano**
- Advantages: GPU acceleration for potential TinyML stretch goal
- Disadvantages: Higher cost (~€100+), larger power draw, overkill for gateway workload in Phases 3–4

**BeagleBone Black**
- Advantages: Has PRU real-time co-processors, industrial-grade Linux
- Disadvantages: Weaker community support compared to RPi, less RAM, CAN HAT ecosystem smaller

**x86 Industrial PC**
- Advantages: Maximum compute, full desktop Linux
- Disadvantages: Significantly over-budget, physically too large for a miniature SDV platform

### Rationale

Raspberry Pi 5 provides 4-core ARM Cortex-A76, 4–8 GB RAM, gigabit Ethernet, and USB 3.0 — more than sufficient for the gateway workload. The RPi ecosystem has mature SocketCAN support via MCP2515-based HATs (e.g., Waveshare 2-CH CAN HAT). Cost (~€60–€80) fits comfortably within budget. Confirmed in PROJECT_MEMORY.md.

### Consequences

- **Positive:** Mature Linux ecosystem, excellent SocketCAN documentation, large community, fits budget, supports Python and C++ natively
- **Negative:** Not a real-time OS — gateway forwarding latency is subject to Linux scheduler jitter (this is an explicit research measurement point)
- **Future implications:** RPi 5 PCIe interface opens potential for NVMe storage (long-term logging) and M.2 HATs

### Related Components

- `gateway/bridge/` (C++ bridge)
- `gateway/diagnostics/` (Python UDS)
- `gateway/logging/` (Python logger)
- `gateway/config/gateway_config.yaml`

---

## ADR-005

**Date:** 2026-07-29

**Status:** Accepted

### Decision

Use the SN65HVD230 CAN transceiver for STM32 ECU nodes.

### Context

STM32 Nucleo boards expose the CAN TX/RX signal lines at 3.3 V logic level. A physical transceiver is required to convert these signals to the differential CAN bus voltage levels (ISO 11898). The transceiver must be compatible with 3.3 V logic, support 500 kbps, and be low cost.

### Alternatives Considered

**TJA1050 (NXP)**
- Advantages: Industry-standard, widely available, robust EMC performance
- Disadvantages: Requires 5 V supply and 5 V-compatible logic levels — needs level shifting when used with 3.3 V STM32 targets, adding circuit complexity

**MCP2551 (Microchip)**
- Advantages: Well-documented, common in hobbyist CAN projects
- Disadvantages: Also 5 V logic; same level-shifting requirement as TJA1050

### Rationale

The SN65HVD230 (Texas Instruments) operates directly at 3.3 V supply and logic, eliminating the need for level shifters when interfacing with STM32 Nucleo boards. It supports up to 1 Mbps (sufficient for 500 kbps baseline and CAN FD test frames), is available in breadboard-friendly breakout modules, and costs ~€2–€4 per node.

### Consequences

- **Positive:** Direct 3.3 V compatibility, no level shifters, low cost, supports future 1 Mbps experiments, breakout modules available
- **Negative:** Less ruggedized than automotive-grade TJA1050 for EMC — acceptable for lab environment
- **Future implications:** If CAN FD at >1 Mbps is required, upgrade to TJA1044G or SN65HVD251 which support higher data rates

### Related Components

- `firmware/shared/can/can_driver.h`
- `/hardware` (schematics, BOM)

---

## ADR-006

**Date:** 2026-07-29

**Status:** Accepted

### Decision

Split gateway implementation between C++17 (performance-critical bridge) and Python 3 (diagnostics, logging, tooling).

### Context

The gateway has two distinct workload types: (1) high-frequency, low-latency CAN frame forwarding where jitter must be minimised, and (2) diagnostic session management and data logging where development speed and library availability matter more than raw performance.

### Alternatives Considered

**Pure Python**
- Advantages: Consistent codebase, fast development, rich library ecosystem (`python-can`, `udsoncan`)
- Disadvantages: Python's GIL and interpreter overhead introduce non-deterministic latency in the forwarding path — unacceptable for a platform benchmarking gateway latency

**Pure C++**
- Advantages: Maximum performance, deterministic behaviour
- Disadvantages: Significantly slower development for diagnostics and logging; reinvents functionality already available in mature Python libraries

### Rationale

A hybrid approach assigns each language to its area of strength. The C++17 bridge (`gateway/bridge/`) uses POSIX threads and raw socket I/O for deterministic forwarding. Python handles diagnostics (`gateway/diagnostics/`) and logging (`gateway/logging/`) where `python-can` and `udsoncan` libraries accelerate development. Both share `gateway_config.yaml` as a common configuration source.

### Consequences

- **Positive:** Optimal performance in the critical path, fast iteration for tooling, clean separation of concerns
- **Negative:** Two languages increase cognitive overhead; interprocess communication between bridge and diagnostics requires a defined IPC mechanism (future ADR)
- **Future implications:** If IPC is needed between bridge and diagnostics service, consider Unix domain sockets or a lightweight message bus

### Related Components

- `gateway/bridge/` (C++17)
- `gateway/diagnostics/` (Python)
- `gateway/logging/` (Python)
- `gateway/config/gateway_config.yaml`

---

## ADR-007

**Date:** 2026-07-29

**Status:** Proposed

### Decision

Define the OTA firmware update strategy for STM32 ECUs.

### Context

Phase 5 requires the ability to update ECU firmware over the network without physical access. The update must be delivered from the Raspberry Pi gateway to individual STM32 ECUs. The mechanism must be safe (no brick on failed update) and use open-source tooling.

### Alternatives Considered

**Custom bootloader over CAN (UDS 0x34/0x36/0x37)**
- Advantages: Follows automotive industry standard (UDS download services), integrates with existing diagnostics stack
- Disadvantages: Requires implementing a custom STM32 bootloader — significant development effort

**STM32 built-in UART/USB bootloader**
- Advantages: Zero bootloader development, uses factory STM32 ROM bootloader
- Disadvantages: Requires physical UART connection per ECU; not truly OTA over CAN

### Rationale

Pending evaluation. UDS-based OTA is the correct long-term approach and aligns with thesis research goals. Decision deferred until Phases 3–4 are complete.

### Consequences

- **Future implications:** Bootloader architecture must reserve a protected flash region; dual-bank flash (available on some STM32 families) is preferred for safe rollback

### Related Components

- `firmware/` (bootloader partition)
- `gateway/diagnostics/` (UDS download services)

---

# Future Decisions

- ADR-008: IPC mechanism between gateway bridge and diagnostics service
- ADR-009: Security architecture (TLS on TCP bridge, CAN intrusion detection)
- ADR-010: CAN FD migration path
- ADR-011: Logging storage format and retention strategy
- ADR-012: Performance benchmark methodology and acceptance thresholds
