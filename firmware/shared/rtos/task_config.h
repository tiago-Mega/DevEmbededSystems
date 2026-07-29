/**
 * @file    task_config.h
 * @brief   FreeRTOS task priorities and stack sizes for all ECUs.
 *
 * Purpose:      Centralise RTOS configuration to avoid priority inversions.
 * Dependencies: FreeRTOS.
 * Notes:        Higher numeric value = higher priority in FreeRTOS.
 */

#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

/* ---------------------------------------------------------------------------
 * Stack sizes (in words, not bytes)
 * --------------------------------------------------------------------------*/
#define TASK_STACK_IDLE         128U
#define TASK_STACK_CAN_RX       256U
#define TASK_STACK_CAN_TX       256U
#define TASK_STACK_APP          512U
#define TASK_STACK_DIAG         256U

/* ---------------------------------------------------------------------------
 * Task priorities
 * --------------------------------------------------------------------------*/
#define TASK_PRIO_IDLE          0U   /**< FreeRTOS idle (do not use). */
#define TASK_PRIO_APP_LOW       1U   /**< Low-priority application tasks. */
#define TASK_PRIO_APP_NORMAL    2U   /**< Normal application tasks. */
#define TASK_PRIO_CAN_TX        3U   /**< CAN Tx handler. */
#define TASK_PRIO_CAN_RX        4U   /**< CAN Rx handler — high priority. */
#define TASK_PRIO_DIAG          3U   /**< Diagnostics handler. */

/* ---------------------------------------------------------------------------
 * Timing
 * --------------------------------------------------------------------------*/
#define TASK_PERIOD_APP_MS      10U  /**< Application task cycle period (ms). */
#define TASK_PERIOD_DIAG_MS     100U /**< Diagnostics task cycle period (ms). */

#endif /* TASK_CONFIG_H */
