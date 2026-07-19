# System Specification

## Purpose

Define the baseline technical specification for the Software Defined Vehicle (SDV) thesis platform.

---

## Scope

This specification covers:

- Embedded ECUs
- Gateway and networking
- Diagnostics and data paths
- Software architecture boundaries

It does not define final production hardware certification requirements.

---

## System Overview

The platform implements a miniature SDV architecture with distributed ECUs connected by CAN and a centralized Linux gateway.

High-level topology:

Laptop

↓

Diagnostics / Tooling

↓

Ethernet

↓

Gateway (Raspberry Pi)

↓

CAN Bus

↓

STM32 ECUs

---

## Functional Requirements

- ECU firmware shall run on STM32-class MCUs.
- ECU scheduling shall support deterministic real-time behavior.
- In-vehicle communication shall use CAN at 500 kbps baseline.
- Gateway shall bridge CAN data to Linux user-space services.
- Platform shall support diagnostics workflow (UDS/ISO-TP planned).
- Logging shall support timestamped message capture for experiments.

---

## Non-Functional Requirements

- Prefer static allocation on embedded targets.
- Keep ISR execution short and bounded.
- Maintain modular layered architecture.
- Ensure reproducible test and benchmark workflows.
- Keep total project cost within stated budget constraints.

---

## Architecture Constraints

- No dependency on proprietary AUTOSAR toolchains.
- Use AUTOSAR-inspired layering where practical:

Application

↓

Services

↓

Communication

↓

Drivers

↓

Hardware

---

## Interfaces

### ECU Internal

- Driver APIs for peripherals and communication
- Service-level interfaces for scheduling and diagnostics hooks
- Application-level interfaces for feature logic

### Gateway Interfaces

- SocketCAN interface for CAN frames
- Ethernet/TCP/UDP endpoints for tooling and integration
- Logging and diagnostics service interfaces

---

## Performance Targets (Initial)

- CAN network baseline: 500 kbps
- ECU control tasks: bounded latency with deterministic scheduling
- Gateway forwarding: low jitter suitable for lab-scale integration

Precise numeric thresholds should be defined during benchmarking phase.

---

## Verification Strategy

- Unit tests for protocol and utility modules
- Integration tests across ECU and gateway boundaries
- Bus-load and latency measurements on CAN traffic
- Fault-injection tests for communication failures
- Long-duration stability tests

---

## Open Items

- Final MCU family selection
- CAN transceiver selection
- Gateway implementation language split (Python vs C++)
- OTA strategy and security architecture

---

## Traceability

Related documents:

- .docs/PROJECT.md
- .docs/ROADMAP.md
- .docs/PROJECT_MEMORY.md
- .docs/DECISIONS.md
