/**
 * @file    can_driver.h
 * @brief   CAN driver interface shared across all ECUs.
 *
 * Purpose:      Provide a hardware-agnostic API for CAN frame transmission and reception.
 * Dependencies: STM32 HAL CAN, FreeRTOS queues.
 * Configuration: CAN baud rate and filter settings defined in can_config.h.
 * Limitations:  Classic CAN 2.0B only. CAN FD support is a future ADR item.
 */

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------------
 * Types
 * --------------------------------------------------------------------------*/

/** Standard CAN frame (11-bit ID, up to 8 bytes payload). */
typedef struct {
    uint32_t id;          /**< 11-bit standard CAN ID. */
    uint8_t  dlc;         /**< Data length code (0-8). */
    uint8_t  data[8];     /**< Payload bytes. */
} CAN_Frame_t;

/** CAN driver status codes. */
typedef enum {
    CAN_OK    = 0,
    CAN_ERROR = 1,
    CAN_BUSY  = 2,
    CAN_TIMEOUT = 3
} CAN_Status_t;

/* ---------------------------------------------------------------------------
 * Public API
 * --------------------------------------------------------------------------*/

/**
 * @brief  Initialise the CAN peripheral and configure acceptance filters.
 * @return CAN_OK on success, CAN_ERROR otherwise.
 */
CAN_Status_t CAN_Driver_Init(void);

/**
 * @brief  Transmit a CAN frame.
 * @param  frame  Pointer to the frame to transmit.
 * @return CAN_OK on success.
 */
CAN_Status_t CAN_Driver_Transmit(const CAN_Frame_t *frame);

/**
 * @brief  Receive a CAN frame (blocking with timeout).
 * @param  frame        Output buffer for received frame.
 * @param  timeout_ms   Timeout in milliseconds.
 * @return CAN_OK on success, CAN_TIMEOUT if no frame received.
 */
CAN_Status_t CAN_Driver_Receive(CAN_Frame_t *frame, uint32_t timeout_ms);

/**
 * @brief  CAN Rx interrupt callback — place received frame into Rx queue.
 *         Call from HAL_CAN_RxFifo0MsgPendingCallback().
 */
void CAN_Driver_RxCallback(void);

#endif /* CAN_DRIVER_H */
