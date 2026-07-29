# HVAC ECU

## Purpose

Simulate a vehicle HVAC ECU responsible for:

- Cabin temperature sensing and reporting
- Fan speed control
- Climate set-point management

## Interfaces

| Direction | CAN ID | Description |
|-----------|--------|-------------|
| TX | 0x300 | Cabin temperature status |
| TX | 0x301 | Fan speed status |
| RX | 0x302 | Climate set-point command |

## Dependencies

- `shared/can/can_driver.h`
- `shared/can/can_ids.h`
- `shared/rtos/task_config.h`
- FreeRTOS
- STM32 HAL

## Limitations

- Simulated sensor values in Phase 2.

## Future Improvements

- Connect real temperature sensor (I2C).
- Add PID control loop for fan speed.
