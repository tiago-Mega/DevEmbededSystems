/**
 * @file    bcm_app.c
 * @brief   Body Control Module application layer.
 *
 * Purpose:      Periodic BCM state reporting via CAN.
 * Dependencies: can_driver, can_ids, FreeRTOS.
 * Limitations:  GPIO simulation only. No actuator outputs in Phase 2.
 */

#include "bcm_app.h"
#include "../../shared/can/can_driver.h"
#include "../../shared/can/can_ids.h"
#include "../../shared/rtos/task_config.h"
#include "FreeRTOS.h"
#include "task.h"

/* ---------------------------------------------------------------------------
 * Private state
 * --------------------------------------------------------------------------*/

typedef struct {
    uint8_t door_fl;     /**< Front-left door: 0=closed, 1=open. */
    uint8_t door_fr;     /**< Front-right door. */
    uint8_t door_rl;     /**< Rear-left door. */
    uint8_t door_rr;     /**< Rear-right door. */
    uint8_t window_fl;   /**< Front-left window position (0-100%). */
    uint8_t window_fr;
    uint8_t lighting;    /**< Interior lighting: 0=off, 1=on. */
    uint8_t hazard;      /**< Hazard lights: 0=off, 1=on. */
} BCM_State_t;

static BCM_State_t s_bcm_state = {0};

/* ---------------------------------------------------------------------------
 * Private helpers
 * --------------------------------------------------------------------------*/

static void BCM_TransmitDoorStatus(void)
{
    CAN_Frame_t frame = {
        .id  = CAN_ID_BCM_DOOR_STATUS,
        .dlc = 4U,
        .data = {
            s_bcm_state.door_fl,
            s_bcm_state.door_fr,
            s_bcm_state.door_rl,
            s_bcm_state.door_rr,
            0U, 0U, 0U, 0U
        }
    };
    (void)CAN_Driver_Transmit(&frame);
}

static void BCM_TransmitLightingStatus(void)
{
    CAN_Frame_t frame = {
        .id  = CAN_ID_BCM_LIGHTING_STATUS,
        .dlc = 2U,
        .data = { s_bcm_state.lighting, s_bcm_state.hazard, 0U, 0U, 0U, 0U, 0U, 0U }
    };
    (void)CAN_Driver_Transmit(&frame);
}

/* ---------------------------------------------------------------------------
 * Public API
 * --------------------------------------------------------------------------*/

void BCM_App_Init(void)
{
    /* Initialise state to safe defaults. */
    s_bcm_state.door_fl   = 0U;
    s_bcm_state.door_fr   = 0U;
    s_bcm_state.door_rl   = 0U;
    s_bcm_state.door_rr   = 0U;
    s_bcm_state.window_fl = 0U;
    s_bcm_state.window_fr = 0U;
    s_bcm_state.lighting  = 0U;
    s_bcm_state.hazard    = 0U;
}

void BCM_App_Task(void *pvParameters)
{
    (void)pvParameters;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(TASK_PERIOD_APP_MS);

    for (;;)
    {
        BCM_TransmitDoorStatus();
        BCM_TransmitLightingStatus();

        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}
