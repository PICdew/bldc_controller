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
void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
}

BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
    return FALSE;
}

void vMBPortClose(void)
{
}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
    return TRUE;
}

BOOL xMBPortSerialGetByte(CHAR *pucByte)
{
    return TRUE;
}

// static void prvvUARTTxReadyISR(void)
// {
//     pxMBFrameCBTransmitterEmpty();
// }

// static void prvvUARTRxISR(void)
// {
//     pxMBFrameCBByteReceived();
// }

/*******************************************************************************
 * EOF
 ******************************************************************************/
