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

#include <stdbool.h>
#include "bsp.h"
#include "port.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
USHORT usMBCRC16(UCHAR *pucFrame, USHORT usLen)
{
    /* Start the CRC */
    CRC_CalculateBufferStart(pucFrame, usLen);

    /* wait until done */
    while (false == CRC_CalculationIsDone())
    {
        /* perform the CRC task */
        CRC_Task();
    }

    return (USHORT)CRC_CalculationResultGet(false, 0);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
