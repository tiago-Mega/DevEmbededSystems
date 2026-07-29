# Body Control Module (BCM)

## Purpose

Simulate a vehicle Body Control Module responsible for:

- Door open/close status reporting
- Window position status reporting
- Interior lighting control
- Hazard light control

## Interfaces

| Direction | CAN ID | Description |
|-----------|--------|-------------|
| TX | 0x100 | Door status |
| TX | 0x101 | Window status |
| TX | 0x102 | Lighting status |
| TX | 0x103 | Hazard light status |

## Dependencies

- `shared/can/can_driver.h`
- `shared/can/can_ids.h`
- `shared/rtos/task_config.h`
- FreeRTOS
- STM32 HAL

## Communication

The BCM periodically broadcasts status frames onto the CAN bus.
It does not currently receive commands (future ADR item).

## Configuration

Task period: `TASK_PERIOD_APP_MS` (10 ms default).

## Limitations

- GPIO simulation only — no real actuators in Phase 2.
- No command reception in initial implementation.

## Future Improvements

- Add RX command handling from gateway.
- Add UDS DID support for door/window state read.
