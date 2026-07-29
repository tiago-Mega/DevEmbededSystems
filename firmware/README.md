# Firmware

This directory contains all embedded firmware for the SDV platform ECUs.

Each ECU is an independent STM32 project following the AUTOSAR-inspired layered architecture.

---

## Directory Structure

```
firmware/
├── shared/          # Code shared across all ECUs (HAL wrappers, CAN driver, utilities)
├── bcm/             # Body Control Module
├── cluster/         # Instrument Cluster
├── hvac/            # HVAC ECU
├── battery/         # Battery ECU
```

---

## Architecture

Every ECU follows the same layered model:

```
Application Layer     <- ECU-specific feature logic
       ↓
Services Layer        <- Scheduling, diagnostics hooks, state machines
       ↓
Communication Layer   <- CAN driver interface, ISO-TP, message dispatching
       ↓
Drivers Layer         <- GPIO, UART, SPI, CAN peripheral drivers
       ↓
HAL                   <- STM32 HAL / CubeMX generated
```

---

## Language & RTOS

- Language: C17
- RTOS: FreeRTOS
- Toolchain: STM32CubeIDE / arm-none-eabi-gcc
- Target MCU: STM32 Nucleo (family TBD per ADR)

---

## Coding Standards

- Prefer static memory allocation
- Avoid dynamic allocation and recursion
- Keep ISR handlers short and bounded
- Separate hardware abstraction from application logic
- Every module must include a header with: Purpose, Interfaces, Dependencies, Configuration, Limitations

---

## Related Documents

- `.docs/PROJECT.md`
- `.docs/SYSTEM_SPECIFICATION.md`
- `.docs/DECISIONS.md`
