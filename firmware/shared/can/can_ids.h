/**
 * @file    can_ids.h
 * @brief   CAN message ID definitions for the SDV platform.
 *
 * Purpose:      Central registry of all CAN frame IDs used across ECUs.
 * Dependencies: None.
 * Limitations:  Classic CAN 2.0B, 11-bit IDs (0x000 - 0x7FF).
 *
 * ID Allocation:
 *   0x100 - 0x1FF  Body Control Module (BCM)
 *   0x200 - 0x2FF  Instrument Cluster
 *   0x300 - 0x3FF  HVAC ECU
 *   0x400 - 0x4FF  Battery ECU
 *   0x700 - 0x7FF  Diagnostics (UDS/ISO-TP)
 */

#ifndef CAN_IDS_H
#define CAN_IDS_H

/* --- Body Control Module ------------------------------------------------- */
#define CAN_ID_BCM_DOOR_STATUS        0x100U  /**< Door open/close status. */
#define CAN_ID_BCM_WINDOW_STATUS      0x101U  /**< Window position status. */
#define CAN_ID_BCM_LIGHTING_STATUS    0x102U  /**< Interior lighting state. */
#define CAN_ID_BCM_HAZARD_STATUS      0x103U  /**< Hazard light state. */

/* --- Instrument Cluster -------------------------------------------------- */
#define CAN_ID_CLUSTER_DISPLAY_CMD    0x200U  /**< Dashboard display command. */
#define CAN_ID_CLUSTER_WARNING        0x201U  /**< Warning indicator state. */
#define CAN_ID_CLUSTER_VEHICLE_STATUS 0x202U  /**< General vehicle status. */

/* --- HVAC ECU ------------------------------------------------------------ */
#define CAN_ID_HVAC_TEMP_STATUS       0x300U  /**< Cabin temperature reading. */
#define CAN_ID_HVAC_FAN_STATUS        0x301U  /**< Fan speed state. */
#define CAN_ID_HVAC_CLIMATE_CMD       0x302U  /**< Climate set-point command. */

/* --- Battery ECU --------------------------------------------------------- */
#define CAN_ID_BATTERY_VOLTAGE        0x400U  /**< Battery voltage (mV). */
#define CAN_ID_BATTERY_CURRENT        0x401U  /**< Battery current (mA). */
#define CAN_ID_BATTERY_TEMP           0x402U  /**< Battery temperature (0.1 C). */
#define CAN_ID_BATTERY_SOC            0x403U  /**< State of charge (0-100%). */

/* --- Diagnostics --------------------------------------------------------- */
#define CAN_ID_DIAG_REQUEST           0x7DFU  /**< UDS functional request (broadcast). */
#define CAN_ID_DIAG_RESPONSE_BASE     0x7E8U  /**< UDS physical response base ID. */

#endif /* CAN_IDS_H */
