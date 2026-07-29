"""diag_service.py

UDS diagnostics service stub for the SDV gateway.

Phase 3 implementation. Currently provides the service skeleton
and SocketCAN bus initialisation.

Dependencies:
    pip install python-can udsoncan
"""

import logging
import can

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [diag] %(levelname)s %(message)s"
)
log = logging.getLogger(__name__)

# CAN interface configuration
CAN_INTERFACE  = "socketcan"
CAN_CHANNEL    = "can0"
CAN_BITRATE    = 500_000

# UDS addressing (functional broadcast + ECU response base)
UDS_REQUEST_ID      = 0x7DF
UDS_RESPONSE_ID_BCM = 0x7E8


def create_bus() -> can.Bus:
    """Initialise and return a python-can SocketCAN bus."""
    bus = can.Bus(
        interface=CAN_INTERFACE,
        channel=CAN_CHANNEL,
        bitrate=CAN_BITRATE
    )
    log.info("CAN bus opened: %s @ %d bps", CAN_CHANNEL, CAN_BITRATE)
    return bus


def send_tester_present(bus: can.Bus) -> None:
    """Send UDS Tester Present (SID 0x3E) broadcast."""
    msg = can.Message(
        arbitration_id=UDS_REQUEST_ID,
        data=[0x02, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00],
        is_extended_id=False
    )
    bus.send(msg)
    log.info("Sent TesterPresent (0x3E)")


def main() -> None:
    log.info("Diagnostics service starting (stub)")
    bus = create_bus()
    try:
        send_tester_present(bus)
        # TODO Phase 3: implement full UDS session loop using udsoncan
        log.info("Diagnostics service stub complete.")
    finally:
        bus.shutdown()


if __name__ == "__main__":
    main()
