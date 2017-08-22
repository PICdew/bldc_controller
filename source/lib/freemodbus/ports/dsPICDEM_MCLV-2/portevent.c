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

#include "mb.h"
#include "mbport.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static eMBEventType eQueuedEvent;
static BOOL xEventInQueue;

/*******************************************************************************
 * Code
 ******************************************************************************/
BOOL xMBPortEventInit(void)
{
    xEventInQueue = FALSE;

    return TRUE;
}

BOOL xMBPortEventPost(eMBEventType eEvent)
{
    xEventInQueue = TRUE;
    eQueuedEvent = eEvent;

    return TRUE;
}

BOOL xMBPortEventGet(eMBEventType *eEvent)
{
    BOOL xEventHappened = FALSE;

    if (xEventInQueue)
    {
        *eEvent = eQueuedEvent;
        xEventInQueue = FALSE;
        xEventHappened = TRUE;
    }

    return xEventHappened;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
