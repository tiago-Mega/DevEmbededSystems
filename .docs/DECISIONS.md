# Engineering Decision Log

This document records important engineering decisions made throughout the project.

The goal is to document **why** a decision was made rather than simply recording what was implemented.

---

# Decision Template

## ADR-000

Date:

Status:

Proposed | Accepted | Rejected | Superseded

---

### Decision

Describe the engineering decision.

---

### Context

Why is this decision necessary?

What problem is being solved?

---

### Alternatives Considered

Option A

Advantages

Disadvantages

Option B

Advantages

Disadvantages

---

### Rationale

Why was the chosen solution selected?

---

### Consequences

Positive

Negative

Future implications

---

### Related Components

Firmware

Gateway

Networking

Documentation

Testing

---

# Decision Log

---

## ADR-001

Date:

Status:

Accepted

### Decision

Use STM32 Nucleo boards for ECU development.

### Context

The project requires multiple inexpensive ECUs with strong community support.

### Alternatives

ESP32

Pros

- Built-in Wi-Fi

Cons

- Less representative of automotive MCUs

NXP Automotive Boards

Pros

- Industry standard

Cons

- Higher cost

### Rationale

STM32 provides an excellent balance between performance, documentation, cost, and educational value.

### Consequences

Positive

- Large ecosystem
- Excellent tooling
- Easy debugging

Negative

- Not automotive-qualified hardware

---

## ADR-002

Date:

Status:

Accepted

### Decision

Use FreeRTOS for embedded scheduling.

### Context

Multiple concurrent ECU tasks require deterministic scheduling.

### Alternatives

Bare Metal

Zephyr

### Rationale

FreeRTOS is lightweight, widely used, and well documented.

### Consequences

Positive

- Better task separation
- Easier scalability

Negative

- Additional learning curve

---

## ADR-003

Date:

Status:

Accepted

### Decision

Use CAN as the primary in-vehicle network.

### Context

CAN remains the dominant real-time communication protocol for automotive ECUs.

### Alternatives

UART

SPI

Ethernet only

### Rationale

CAN accurately reflects modern automotive communication while remaining affordable to implement.

---

## ADR-004

Date:

Status:

Proposed

### Decision

Use Raspberry Pi as the Central Vehicle Computer.

### Context

The gateway requires Linux, Ethernet, diagnostics, logging, and OTA support.

### Alternatives

Jetson Nano

BeagleBone Black

Industrial PC

### Current Status

Pending hardware evaluation.

---

# Future Decisions

Examples of future ADRs

- Gateway programming language
- CAN transceiver selection
- OTA protocol
- Bootloader architecture
- Diagnostic implementation
- AUTOSAR-inspired layering
- Logging architecture
- Security architecture
- Ethernet topology
- Performance metrics