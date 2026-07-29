# Diagnostics Service (Python)

## Purpose

Provide a UDS (ISO 14229) diagnostics interface between the laptop tooling and the STM32 ECUs via ISO-TP over CAN.

## Responsibilities

- Receive UDS requests from the laptop (TCP or stdin)
- Encode requests as ISO-TP frames and transmit on CAN
- Decode ISO-TP responses from ECUs and return to laptop

## Dependencies

```bash
pip install python-can udsoncan
```

## Supported Services (Phase 3)

| SID   | Service                      |
|-------|------------------------------|
| 0x10  | Diagnostic Session Control   |
| 0x11  | ECU Reset                    |
| 0x22  | Read Data By Identifier      |
| 0x27  | Security Access              |
| 0x3E  | Tester Present               |

## Limitations

- Phase 3 implementation. Stub only in Phase 2.
- No security access seed/key implementation yet.

## Future Improvements

- Add 0x2E Write Data By Identifier for OTA preparation.
- Add 0x34/0x36/0x37 for firmware download sequence.
