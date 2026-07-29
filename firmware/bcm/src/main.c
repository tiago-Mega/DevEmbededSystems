/**
 * @file    main.c
 * @brief   BCM ECU entry point.
 *
 * Purpose:      Initialise HAL, CAN driver, BCM application, then start FreeRTOS.
 * Dependencies: STM32 HAL, FreeRTOS, can_driver, bcm_app.
 */

#include "bcm_app.h"
#include "../../shared/can/can_driver.h"
#include "../../shared/rtos/task_config.h"
#include "FreeRTOS.h"
#include "task.h"

/* Forward declaration — implemented by STM32CubeIDE generated code. */
extern void SystemClock_Config(void);
extern void MX_GPIO_Init(void);
extern void MX_CAN_Init(void);

int main(void)
{
    /* 1. STM32 HAL initialisation (CubeMX generated). */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_CAN_Init();

    /* 2. CAN driver initialisation. */
    (void)CAN_Driver_Init();

    /* 3. BCM application initialisation. */
    BCM_App_Init();

    /* 4. Create FreeRTOS tasks. */
    xTaskCreate(
        BCM_App_Task,
        "BCM_App",
        TASK_STACK_APP,
        NULL,
        TASK_PRIO_APP_NORMAL,
        NULL
    );

    /* 5. Start the scheduler — does not return. */
    vTaskStartScheduler();

    /* Should never reach here. */
    for (;;) {}

    return 0;
}
