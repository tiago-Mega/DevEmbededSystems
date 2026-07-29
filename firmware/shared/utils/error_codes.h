/**
 * @file    error_codes.h
 * @brief   Common error code definitions for all ECU firmware.
 *
 * Purpose:      Unified error reporting across layers.
 * Dependencies: None.
 */

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#include <stdint.h>

typedef enum {
    ERR_OK              = 0,   /**< No error. */
    ERR_NULL_POINTER    = 1,   /**< Null pointer passed to function. */
    ERR_INVALID_PARAM   = 2,   /**< Invalid parameter value. */
    ERR_TIMEOUT         = 3,   /**< Operation timed out. */
    ERR_BUSY            = 4,   /**< Resource is busy. */
    ERR_HAL_FAULT       = 5,   /**< STM32 HAL returned an error. */
    ERR_CAN_TX_FAIL     = 6,   /**< CAN frame transmission failure. */
    ERR_CAN_RX_OVERFLOW = 7,   /**< CAN Rx queue overflow. */
    ERR_NOT_IMPLEMENTED = 0xFF /**< Stub not yet implemented. */
} ErrorCode_t;

#endif /* ERROR_CODES_H */
