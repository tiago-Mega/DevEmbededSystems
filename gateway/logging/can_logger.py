"""can_logger.py

Timestamped CAN frame logger for SDV platform research experiments.

Logs all frames on the bus to a CSV file with microsecond timestamps.
Useful for gateway latency benchmarking and bus-load analysis.

Dependencies:
    pip install python-can

Usage:
    python3 can_logger.py --channel can0 --output logs/session.csv
"""

import argparse
import csv
import logging
import time
from pathlib import Path

import can

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [logger] %(levelname)s %(message)s"
)
log = logging.getLogger(__name__)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="SDV CAN Logger")
    parser.add_argument("--channel",  default="can0",              help="SocketCAN interface")
    parser.add_argument("--bitrate",  default=500_000, type=int,   help="CAN bitrate (bps)")
    parser.add_argument("--output",   default="logs/session.csv",  help="Output CSV file path")
    return parser.parse_args()


def log_frames(channel: str, bitrate: int, output_path: Path) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)

    bus = can.Bus(interface="socketcan", channel=channel, bitrate=bitrate)
    log.info("Logging started: %s -> %s", channel, output_path)

    with open(output_path, "w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["timestamp_us", "can_id", "dlc", "data_hex"])

        try:
            while True:
                msg = bus.recv(timeout=1.0)
                if msg is None:
                    continue
                timestamp_us = int(msg.timestamp * 1_000_000)
                data_hex = msg.data.hex().upper()
                writer.writerow([
                    timestamp_us,
                    f"0x{msg.arbitration_id:03X}",
                    msg.dlc,
                    data_hex
                ])
                csvfile.flush()
        except KeyboardInterrupt:
            log.info("Logging stopped by user.")
        finally:
            bus.shutdown()


def main() -> None:
    args = parse_args()
    log_frames(
        channel=args.channel,
        bitrate=args.bitrate,
        output_path=Path(args.output)
    )


if __name__ == "__main__":
    main()
