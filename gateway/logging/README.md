# CAN Logger (Python)

## Purpose

Capture and persist timestamped CAN frames from the bus for research experiments and latency analysis.

## Output Format

Timestamped log files in CSV and `.asc` (Vector ASCII Log) format for compatibility with CANalyzer/CANoe.

## Dependencies

```bash
pip install python-can
```

## Usage

```bash
python3 can_logger.py --channel can0 --output logs/session.csv
```

## Limitations

- No real-time filtering in Phase 3 (logs all frames).

## Future Improvements

- Add per-message-ID filtering.
- Add live latency statistics output.
- Add structured JSON output for easier post-processing.
