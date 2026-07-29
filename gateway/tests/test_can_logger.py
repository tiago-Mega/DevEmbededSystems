"""test_can_logger.py

Unit tests for the CAN logger service.
Uses a mock CAN bus to avoid hardware dependency.
"""

import csv
import time
from pathlib import Path
from unittest.mock import MagicMock, patch

import pytest


class MockMessage:
    def __init__(self, arb_id, dlc, data, timestamp=None):
        self.arbitration_id = arb_id
        self.dlc = dlc
        self.data = bytes(data)
        self.timestamp = timestamp or time.time()


def test_csv_row_format(tmp_path):
    """Verify CSV output format matches expected schema."""
    import sys
    sys.path.insert(0, str(Path(__file__).parent.parent / "logging"))
    import can_logger

    output_file = tmp_path / "test_session.csv"

    mock_msg = MockMessage(0x100, 4, [0x01, 0x00, 0x00, 0x00])

    with patch("can.Bus") as mock_bus_cls:
        mock_bus = MagicMock()
        mock_bus_cls.return_value = mock_bus
        mock_bus.recv.side_effect = [mock_msg, KeyboardInterrupt]

        can_logger.log_frames("vcan0", 500_000, output_file)

    with open(output_file, newline="") as f:
        rows = list(csv.reader(f))

    assert rows[0] == ["timestamp_us", "can_id", "dlc", "data_hex"]
    assert rows[1][1] == "0x100"
    assert rows[1][2] == "4"
