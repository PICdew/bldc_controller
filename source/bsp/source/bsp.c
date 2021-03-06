/*
 * Copyright (C) 2017 Wang Ge
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

#include "qpc.h"
#include "bsp.h"
#include "mcc_generated_files/mcc.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void TMR1_CallBack(void)
{
    QF_TICK_X(0U, (void *)0); /* process time events for rate 0 */
}

void BSP_Init(void)
{
    SYSTEM_Initialize();
}

void Q_onAssert(char const Q_ROM *const Q_ROM_VAR module, int loc)
{
    while (1U)
    {
    }
}

void QF_onStartup(void)
{
    INTERRUPT_GlobalEnable();
    TMR1_Start();
}

void QF_onCleanup(void)
{
}

void QK_onIdle(void)
{
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
