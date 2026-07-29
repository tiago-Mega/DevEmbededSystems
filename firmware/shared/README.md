# Shared Firmware Modules

This directory contains code shared across all ECUs.

No ECU-specific logic belongs here.

---

## Contents

```
shared/
├── can/         # CAN driver wrapper and frame definitions
├── utils/       # Ring buffers, error codes, type definitions
├── rtos/        # FreeRTOS task and queue helper wrappers
```
