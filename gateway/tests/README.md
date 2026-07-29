# Gateway Tests

## Purpose

Integration and unit tests for gateway services.

## Test Strategy

| Test Type         | Scope                                          |
|-------------------|------------------------------------------------|
| Unit tests        | Individual Python service functions            |
| Integration tests | Full CAN frame path: ECU → SocketCAN → TCP     |
| Latency tests     | Gateway forwarding jitter measurement          |
| Fault injection   | Disconnect/reconnect, malformed frames         |

## Dependencies

```bash
pip install pytest python-can
```

## Running Tests

```bash
cd gateway/tests
pytest -v
```

## Limitations

- Phase 3 tests require real hardware (RPi + CAN HAT).
- Phase 2 uses virtual CAN (`vcan0`) for development.

## Setting Up Virtual CAN for Development

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```
