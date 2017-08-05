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

#include "qpn.h"
#include "bsp.h"
#include "blinky.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _blinky
{                  /* the Blinky active object */
    QActive super; /* inherit QActive */
} blinky_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static QState Blinky_Initial(blinky_t *const me);
static QState Blinky_Off(blinky_t *const me);
static QState Blinky_On(blinky_t *const me);

/*******************************************************************************
 * Variables
 ******************************************************************************/
blinky_t AO_Blinky;

/*******************************************************************************
 * Code
 ******************************************************************************/
void Blinky_Ctor(void)
{
    blinky_t *const me = &AO_Blinky;
    QActive_ctor(&me->super, Q_STATE_CAST(&Blinky_Initial));
}

QState Blinky_Initial(blinky_t *const me)
{
    QActive_armX((QActive *)me, 0U, BSP_TICKS_PER_SEC / 2U, BSP_TICKS_PER_SEC / 2U);

    return Q_TRAN(&Blinky_Off);
}

QState Blinky_Off(blinky_t *const me)
{
    QState status;

    switch (Q_SIG(me))
    {
        case Q_ENTRY_SIG:
        {
            BSP_ledOff();
            status = Q_HANDLED();
            break;
        }

        case Q_TIMEOUT_SIG:
        {
            status = Q_TRAN(&Blinky_On);
            break;
        }

        default:
        {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }

    return status;
}

QState Blinky_On(blinky_t *const me)
{
    QState status;

    switch (Q_SIG(me))
    {
        case Q_ENTRY_SIG:
        {
            BSP_ledOn();
            status = Q_HANDLED();
            break;
        }

        case Q_TIMEOUT_SIG:
        {
            status = Q_TRAN(&Blinky_Off);
            break;
        }

        default:
        {
            status = Q_SUPER(&QHsm_top);
            break;
        }
    }

    return status;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
