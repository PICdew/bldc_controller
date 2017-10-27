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
 * Variables
 ******************************************************************************/
/* Event queue storage for Blinky */
static QEvt const *l_blinkyQSto[10U];
static QEvt const *l_modbusQSto[10U];

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* Instantiate all active objects */
    Blinky_Ctor();
    Modbus_Ctor();

    /* initialize the framework and the underlying RT kernel */
    QF_init();
    /* initialize the Board Support Package */
    BSP_Init();

    /* publish-subscribe not used, no call to QF_psInit() */
    /* dynamic event allocation not used, no call to QF_poolInit() */

    /* Start the active objects... */
    QACTIVE_START(AO_Blinky,      /* AO pointer to start */
        1U,             /* unique QP priority of the AO */
        l_blinkyQSto,   /* storage for the AO's queue */
        Q_DIM(l_blinkyQSto), /* lenght of the queue [entries] */
        (void *)0U,     /* stack storage (not used in QK) */
        0U,             /* stack size [bytes] (not used in QK) */
        (QEvt *)0U);    /* initial event (or 0) */
    QACTIVE_START(AO_Modbus,      /* AO pointer to start */
        2U,             /* unique QP priority of the AO */
        l_modbusQSto,   /* storage for the AO's queue */
        Q_DIM(l_modbusQSto), /* lenght of the queue [entries] */
        (void *)0U,     /* stack storage (not used in QK) */
        0U,             /* stack size [bytes] (not used in QK) */
        (QEvt *)0U);    /* initial event (or 0) */

    /* run the QF application */
    return QF_run();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
