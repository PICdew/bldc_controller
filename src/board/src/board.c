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
#include "board.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
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
    /* NOTE: SystemInit() has been already called from the startup code
     *  but SystemCoreClock needs to be updated
     */
    SystemCoreClockUpdate();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
