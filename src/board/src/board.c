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
#include "board.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
static void BOARD_Clock_Init(void)
{
    /* Disable PLL */
    LL_RCC_PLL_Disable();
    /* Wait until PLL is stoped */
    while (LL_RCC_PLL_IsReady())
    {
    }

    /* Setup PLL */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);

    /* Enable PLL */
    LL_RCC_PLL_Enable();
    /* Wait until PLL is ready */
    while (!LL_RCC_PLL_IsReady())
    {
    }

    /* Switch to HSI with PLL */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    /* Wait until Clock is switched */
    while (LL_RCC_SYS_CLKSOURCE_STATUS_PLL != LL_RCC_GetSysClkSource())
    {
    }

    /* Enable peripheral clocks */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
    (void)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPIOF);
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
    LL_GPIO_Init(GPIOF, &gpioInitConfig);
}

void SysTick_Handler(void)
{
    QF_tickXISR(0U);
}

void QF_onStartup(void)
{
    SysTick_Config(SystemCoreClock / BOARD_TICKS_PER_SEC);
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
