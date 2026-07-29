/**
 * @file    bcm_app.h
 * @brief   Body Control Module application interface.
 */

#ifndef BCM_APP_H
#define BCM_APP_H

/**
 * @brief Initialise BCM state to safe defaults.
 *        Call once before starting the RTOS scheduler.
 */
void BCM_App_Init(void);

/**
 * @brief FreeRTOS task entry point for the BCM application.
 *        Periodically transmits CAN status frames.
 * @param pvParameters  Unused.
 */
void BCM_App_Task(void *pvParameters);

#endif /* BCM_APP_H */
