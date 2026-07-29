# Roadmap

**Last Updated:** 2026-07-29

---

## Phase 1 — Research & Architecture ✅

**Estimated Duration:** 2–3 weeks

**Tasks:**
- Literature review (SDV architectures, AUTOSAR, CAN)
- Hardware platform comparison
- Architecture proposal
- ADR-001 to ADR-004 written and accepted

**Deliverable:** Documented architecture proposal, accepted ADRs, repository scaffold

**Status:** Complete

---

## Phase 2 — Hardware & CAN Bring-Up 🔄

**Estimated Duration:** 3–4 weeks

**Tasks:**
- Procure STM32 Nucleo boards (F446RE or G474RE — OI-001)
- Procure SN65HVD230 transceivers (ADR-005)
- Procure Raspberry Pi 5 + CAN HAT (ADR-004)
- Implement `firmware/shared/can/can_driver.c`
- Implement `gateway/bridge/src/tcp_server.cpp`
- Bring up physical CAN bus
- Verify BCM ECU CAN transmission with `candump`

**Deliverable:** BCM ECU transmitting 0x100 frame at 10 ms cycle verified on physical bus

**Status:** In Progress

**Dependencies:** Hardware procurement

---

## Phase 3 — Full ECU Firmware

**Estimated Duration:** 4–5 weeks

**Tasks:**
- Implement Cluster, HVAC, Battery ECU app tasks
- Multi-ECU bus bring-up
- FreeRTOS task timing verification
- Unit tests for CAN driver and utility modules

**Deliverable:** All 4 ECUs communicating on bus simultaneously, no frame loss at < 30% bus load

**Dependencies:** Phase 2 complete, physical hardware available

---

## Phase 4 — Gateway & Diagnostics

**Estimated Duration:** 4–5 weeks

**Tasks:**
- SocketCAN + CAN HAT bring-up on RPi 5
- Build and test `can_eth_bridge` (C++)
- Integration test: laptop receives CAN frames over TCP
- `can_logger.py` captures and persists timestamped frames
- UDS TesterPresent end-to-end verification
- Define IPC mechanism between bridge and diagnostics (ADR-008)

**Deliverable:** Working CAN ↔ Ethernet gateway, verified latency < 5 ms at nominal load

**Dependencies:** Phase 3 complete

---

## Phase 5 — OTA & Integration

**Estimated Duration:** 3–4 weeks

**Tasks:**
- OTA bootloader architecture (resolve ADR-007)
- Security hardening (ADR-009)
- System integration test (all ECUs + gateway + laptop)
- Performance optimisation

**Deliverable:** Firmware update delivered to one ECU over CAN from RPi

**Dependencies:** Phase 4 complete, ADR-007 accepted

---

## Phase 6 — Evaluation & Thesis

**Estimated Duration:** 6–8 weeks

**Tasks:**
- Benchmarking experiments (latency, bus load, scalability)
- Data collection and statistical analysis
- Thesis writing
- Final validation and presentation

**Deliverable:** Completed Master's Thesis

**Dependencies:** Phase 5 complete

---

# Timeline Summary

| Phase | Focus | Duration | Status |
|-------|-------|----------|--------|
| 1 | Research & Architecture | 2–3 weeks | ✅ Complete |
| 2 | Hardware & CAN Bring-Up | 3–4 weeks | 🔄 In Progress |
| 3 | Full ECU Firmware | 4–5 weeks | ⬜ Not Started |
| 4 | Gateway & Diagnostics | 4–5 weeks | ⬜ Not Started |
| 5 | OTA & Integration | 3–4 weeks | ⬜ Not Started |
| 6 | Evaluation & Thesis | 6–8 weeks | ⬜ Not Started |

**Total estimated duration:** 22–29 weeks (~6–7 months)
