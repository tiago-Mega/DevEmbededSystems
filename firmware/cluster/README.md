# Instrument Cluster ECU

## Purpose

Simulate a vehicle Instrument Cluster responsible for:

- Dashboard display updates
- Warning indicator management
- Vehicle status reporting

## Interfaces

| Direction | CAN ID | Description |
|-----------|--------|-------------|
| TX | 0x200 | Display command |
| TX | 0x201 | Warning indicator |
| TX | 0x202 | Vehicle status |

## Dependencies

- `shared/can/can_driver.h`
- `shared/can/can_ids.h`
- `shared/rtos/task_config.h`
- FreeRTOS
- STM32 HAL

## Limitations

- Simulated display output only in Phase 2.

## Future Improvements

- Receive data from BCM and Battery ECU to drive display logic.
- Add UDS DID support.
