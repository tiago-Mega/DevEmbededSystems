# Battery ECU

## Purpose

Simulate a vehicle Battery Management ECU responsible for:

- Voltage monitoring
- Current monitoring
- Temperature monitoring
- State of Charge (SoC) estimation

## Interfaces

| Direction | CAN ID | Description |
|-----------|--------|-------------|
| TX | 0x400 | Battery voltage (mV) |
| TX | 0x401 | Battery current (mA) |
| TX | 0x402 | Battery temperature (0.1°C) |
| TX | 0x403 | State of Charge (0–100%) |

## Dependencies

- `shared/can/can_driver.h`
- `shared/can/can_ids.h`
- `shared/rtos/task_config.h`
- FreeRTOS
- STM32 HAL

## Limitations

- Simulated ADC readings in Phase 2.

## Future Improvements

- Connect real ADC channels for voltage and current sensing.
- Implement Coulomb counting SoC algorithm.
- Add UDS DID support for BMS diagnostics.
