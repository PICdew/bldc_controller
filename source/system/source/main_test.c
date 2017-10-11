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
#include "bldc_controller.h"
#include "blinky.h"
#include "modbus.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    uint8_t ch;

    /* initialize the Board Support Package */
    BSP_Init();
    UART1_Initialize();

    while (1U)
    {
        if (!UART1_ReceiveBufferIsEmpty())
        {
            ch = UART1_Read();
            if (0x0U == ch)
            {
                UART1_Write('E');
                UART1_Write('R');
                UART1_Write('R');
                UART1_Write('O');
                UART1_Write('R');
                UART1_Write('!');
                UART1_Write('\r');
                UART1_Write('\n');
            }
        }
    }

    /* run the QF application */
    return 0U;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
