/*
 * Copyright (C) 2018 Wang Ge
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "qpn.h"
#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_tim.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_CLOCK_STARTUP_TIMEOUT (0x500U)
#define BOARD_CLOCK_CHECK_READY(x, y)              \
    do                                             \
    {                                              \
        uint16_t startupCounter = 0U;              \
        uint32_t ready = false;                    \
                                                   \
        do                                         \
        {                                          \
            ready = x;                             \
            startupCounter++;                      \
        } while (!ready && (startupCounter <= y)); \
        if (!ready)                                \
        {                                          \
            while (1U)                             \
            {                                      \
            }                                      \
        }                                          \
        else                                       \
        {                                          \
        }                                          \
    } while (0U)

/*******************************************************************************
 * Code
 ******************************************************************************/
static void BOARD_Clock_Init(void)
{
    /* Disable PLL */
    LL_RCC_PLL_Disable();
    /* Wait until PLL is stoped */
    BOARD_CLOCK_CHECK_READY(!LL_RCC_PLL_IsReady(), BOARD_CLOCK_STARTUP_TIMEOUT);

    /* Setup PLL */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);

    /* Enable PLL */
    LL_RCC_PLL_Enable();
    /* Wait until PLL is ready */
    BOARD_CLOCK_CHECK_READY(LL_RCC_PLL_IsReady(), BOARD_CLOCK_STARTUP_TIMEOUT);

    /* Switch to HSI with PLL */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    /* Wait until Clock is switched */
    BOARD_CLOCK_CHECK_READY((LL_RCC_SYS_CLKSOURCE_STATUS_PLL == LL_RCC_GetSysClkSource()), BOARD_CLOCK_STARTUP_TIMEOUT);

    /* Enable peripheral clocks */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
    (void)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOF);

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
    (void)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM14);
}

static void BOARD_LED_Init(void)
{
    LL_GPIO_InitTypeDef gpioInitConfig;
    gpioInitConfig.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_1;
    gpioInitConfig.Mode = LL_GPIO_MODE_OUTPUT;
    gpioInitConfig.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpioInitConfig.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpioInitConfig.Pull = LL_GPIO_PULL_NO;
    gpioInitConfig.Alternate = LL_GPIO_AF_0;

    /* Initialize LED pins */
    LL_GPIO_SetOutputPin(GPIOF, LL_GPIO_PIN_0 | LL_GPIO_PIN_1);
    LL_GPIO_Init(GPIOF, &gpioInitConfig);
}

void TIM14_IRQHandler(void)
{
    LL_TIM_ClearFlag_UPDATE(TIM14);

    QF_tickXISR(0U);
}

void QF_onStartup(void)
{
    LL_TIM_InitTypeDef timerInitConfig;

    LL_TIM_StructInit(&timerInitConfig);
    timerInitConfig.Prescaler = 48U;
    timerInitConfig.Autoreload = (SystemCoreClock / 48U) / BOARD_TICKS_PER_SEC;

    /* Initialize TIM14 */
    LL_TIM_Init(TIM14, &timerInitConfig);

    /* Enable TIM14 Interrupt */
    LL_TIM_ClearFlag_UPDATE(TIM14);
    LL_TIM_EnableIT_UPDATE(TIM14);
    NVIC_EnableIRQ(TIM14_IRQn);

    /* Start Timer14 as systick */
    LL_TIM_EnableCounter(TIM14);
}

void QV_onIdle(void)
{
    /* Just enable interrupts */
    QF_INT_ENABLE();
}

void Q_onAssert(char const Q_ROM * const Q_ROM_VAR module, int loc)
{
    while (1U)
    {
    }
}

void BOARD_Init(void)
{
    /* Initialize system clock */
    BOARD_Clock_Init();

    /* NOTE: SystemInit() has been already called from the startup code
     *  but SystemCoreClock needs to be updated
     */
    SystemCoreClockUpdate();

    /* Initialize LED */
    BOARD_LED_Init();
}

void BOARD_ledOff(void)
{
    LL_GPIO_SetOutputPin(GPIOF, LL_GPIO_PIN_0);
}

void BOARD_ledOn(void)
{
    LL_GPIO_ResetOutputPin(GPIOF, LL_GPIO_PIN_0);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
