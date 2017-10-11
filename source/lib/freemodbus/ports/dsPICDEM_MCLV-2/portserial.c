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
#include "port.h"
#include "mb.h"
#include "mbport.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
    /* Handle UART Rx Enable/Disable */
    __write_to_IEC(IEC0bits.U1RXIE = (TRUE == xRxEnable) ? 1U : 0U);

    /* Handle UART Tx Enable/Disable */
    __write_to_IEC(IEC0bits.U1TXIE = (TRUE == xTxEnable) ? 1U : 0U);
}

BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
    BOOL result = TRUE;

    /* Prevent compiler warning. */
    (void)ucPORT;

    /* Setup data format */
    if ((9U == ucDataBits) && (MB_PAR_NONE == eParity))
    {
        U1MODEbits.PDSEL = 3U;
    }
    else if ((8U == ucDataBits) && (MB_PAR_ODD == eParity))
    {
        U1MODEbits.PDSEL = 2U;
    }
    else if ((8U == ucDataBits) && (MB_PAR_EVEN == eParity))
    {
        U1MODEbits.PDSEL = 1U;
    }
    else if ((8U == ucDataBits) && (MB_PAR_NONE == eParity))
    {
        U1MODEbits.PDSEL = 0U;
    }
    else
    {
        result = FALSE;
    }

    if (TRUE == result)
    {
        switch (ulBaudRate)
        {
            case 9600U:
                // BaudRate = 9600; Frequency = 30000000 Hz; BRG 780;
                U1BRG = 0x30CU;
                U1MODEbits.BRGH = 1U;
                break;

            default:
                result = FALSE;
                break;
        }
    }

    /* Disable UART Tx & Rx Interrupt */
    vMBPortSerialEnable(FALSE, FALSE);

    if (TRUE == result)
    {
        // IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled;
        // LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX;
        U1MODE = U1MODE & 0x000EU;

        // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN
        // disabled; ADDEN disabled;
        U1STA = 0x0U;

        U1MODEbits.UARTEN = 1U; // enabling UARTEN bit
        U1STAbits.UTXEN = 1U;
    }

    return result;
}

void vMBPortClose(void)
{
    /* Disable UART Module */
    U1STAbits.UTXEN = 0U;
    U1MODEbits.UARTEN = 0U;
}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
    U1TXREG = (UCHAR)ucByte;

    return TRUE;
}

BOOL xMBPortSerialGetByte(CHAR *pucByte)
{
    *pucByte = (CHAR)U1RXREG;

    return TRUE;
}

QK_ISR(no_auto_psv) _U1TXInterrupt(void)
{
    /* Clear UART Tx Interrupt Flag */
    IFS0bits.U1TXIF = 0U;

    /* Call FreeModbus Tx callback */
    pxMBFrameCBTransmitterEmpty();

    /* QPC IRQ epilog */
    QK_ISR_EXIT();
}

QK_ISR(no_auto_psv) _U1RXInterrupt(void)
{
    /* Clear UART Rx Interrupt Flag */
    IFS0bits.U1RXIF = 0U;

    /* Call FreeModbus Rx callback */
    pxMBFrameCBByteReceived();

    /* QPC IRQ epilog */
    QK_ISR_EXIT();
}

QK_ISR(no_auto_psv) _U1ErrInterrupt(void)
{
    if ((U1STAbits.OERR == 1U))
    {
        U1STAbits.OERR = 0U;
    }

    IFS4bits.U1EIF = 0U;

    /* QPC IRQ epilog */
    QK_ISR_EXIT();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
