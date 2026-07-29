# References

**Last Updated:** 2026-07-29

All references should include a one-sentence personal summary written in your own words.

Do not copy abstracts verbatim.

---

## Standards

- **ISO 26262** — Functional safety standard for automotive electrical/electronic systems; defines ASIL safety integrity levels.
- **ISO 14229 (UDS)** — Unified Diagnostic Services protocol; defines the diagnostic service layer implemented in `gateway/diagnostics/`.
- **ISO 15765-2 (ISO-TP)** — Transport protocol for CAN that enables multi-frame messages beyond 8 bytes; required for UDS.
- **ISO 11898 (CAN)** — Physical and data-link layer standard for the CAN bus; defines the 500 kbps baseline in this project.
- **ISO 11898-2 (CAN FD)** — Extension supporting up to 8 Mbps and 64-byte payloads; targeted as a stretch goal.
- **AUTOSAR Classic** — Layered software architecture standard for ECUs; this project adopts its layering pattern without its toolchain.
- **AUTOSAR Adaptive** — Service-oriented AUTOSAR variant for high-compute platforms; relevant to gateway architecture research.
- **SOME/IP** — AUTOSAR middleware protocol for service-oriented Ethernet communication; stretch goal for future phases.

---

## Research Papers

### SDV Architecture & E/E Systems

- **"The Rise of the Software-Defined Vehicle: Architectures, Enabling Technologies, and Operational Frameworks"** (arXiv, 2026)
  - DOI/URL: https://arxiv.org/abs/2605.30001
  - *Summary: Comprehensive survey of modern SDV architectures directly aligned with this platform's design goals.*

- **"Vehicle E/E Architecture and Key Technologies Enabling Software-Defined Vehicle"** (SAE WCX, 2024)
  - DOI: 10.4271/2024-01-2035
  - *Summary: Covers zone-based E/E architecture, centralized HPC, OTA, and cybersecurity — maps directly to Phases 4 and 5 of this project.*

- **"Demystifying Software-Defined Vehicle Architecture for Modern Automotive Systems"** (Zenodo, 2025)
  - URL: https://zenodo.org/records/16735475
  - *Summary: Examines hypervisors, mixed-criticality workloads, and hardware abstraction layers relevant to the gateway and firmware architecture.*

- **"Rethinking Vehicle Architecture Through Softwarization and Servitization"** (IEEE Xplore, 2025)
  - DOI: 10.1109/ACCESS.2025.11078249
  - URL: https://ieeexplore.ieee.org/document/11078249
  - *Summary: Analyses service-oriented design principles applicable to the gateway's diagnostics and OTA services.*

- **"Towards Conceptualizing Software-Defined Vehicles: A Systematic Review and Future Research Avenues"** (ECIS, 2025)
  - URL: https://aisel.aisnet.org/ecis2025/92
  - *Summary: Systematic literature review useful for framing the thesis introduction and identifying research gaps.*

### Security & Cybersecurity

- **"Emerging Architecture Design, Control, and Security Challenges in Software Defined Vehicles"** (University of Essex / CODES+ISSS, 2024)
  - URL: https://repository.essex.ac.uk/39107/
  - *Summary: Covers SDV security challenges from both industry and academia; directly relevant to the IDS and Secure Boot stretch goals.*

- **"The Software Defined Vehicle – Technical and Organizational Challenges and Opportunities"** (Springer ISSY, 2023)
  - DOI: 10.1007/978-3-658-42048-2_29
  - *Summary: Examines deployment challenges and organisational implications of SDV transitions; useful for thesis discussion section.*

### CAN / Gateway / Networking

- **"Formal Timing Analysis of CAN-to-Ethernet Gateway Strategies in Automotive Networks"** (Springer, Real-Time Systems, 2015)
  - DOI: 10.1007/s11241-015-9243-y
  - URL: https://link.springer.com/article/10.1007/s11241-015-9243-y
  - *Summary: Provides formal worst-case latency bounds for CAN-to-Ethernet gateway forwarding — the primary benchmark baseline for Phase 6 latency experiments.*

- **"Autonomy-driven Emerging Directions in Software-defined Vehicles"** (DATE, 2023)
  - URL: https://past.date-conference.com/proceedings-archive/2023/DATA/6018.pdf
  - *Summary: Identifies autonomy as the key driver for SDV evolution; relevant to the ADAS and future ECU sections.*

---

## Books

- **"The FreeRTOS Reference Manual"** — FreeRTOS.org — Primary reference for task, queue, and scheduler API used in all ECU firmware.
- **"Automotive Embedded Systems Handbook"** — Nicolas Navet & Françoise Simonot-Lion (CRC Press) — Comprehensive reference for CAN, automotive OS, and ECU architecture.
- **"Embedded Systems Architecture"** — Tammy Noergaard (Newnes) — Reference for layered firmware architecture and HAL design patterns.

---

## Online Resources

- **STM32 HAL Documentation** — https://www.st.com/en/embedded-software/stm32cube-mcu-mpu-packages.html
- **FreeRTOS Documentation** — https://www.freertos.org/Documentation/RTOS_book.html
- **SocketCAN / Linux CAN** — https://www.kernel.org/doc/html/latest/networking/can.html
- **python-can** — https://python-can.readthedocs.io
- **udsoncan** — https://udsoncan.readthedocs.io
- **SN65HVD230 Datasheet** — https://www.ti.com/product/SN65HVD230
- **Waveshare 2-CH CAN HAT** — https://www.waveshare.com/2-ch-can-hat.htm

---

## Personal Notes

Summarise important ideas here while reading.

Write concise summaries in your own words — never copy large excerpts.

Link notes back to a requirement ID (e.g., REQ-SYS-004) where possible.
