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

#include "bsp.h"
#include "port.h"
#include "mb.h"
#include "mbport.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void TMR2_CallBack(void)
{
    (void)pxMBPortCBTimerExpired();
}

BOOL xMBPortTimersInit(USHORT usTimeOut50us)
{
    /* TMR2 peroid is set to 4.01ms(for 9600 bps) in MCC driver. */
    (void)usTimeOut50us;

    return TRUE;
}

inline void vMBPortTimersEnable(void)
{
    TMR2_Start();
}

inline void vMBPortTimersDisable(void)
{
    TMR2_Stop();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
