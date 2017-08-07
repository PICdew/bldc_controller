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
#include "bldc_controller.h"
#include "blinky.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Event queue storage for Blinky */
static QEvt l_blinkyQSto[10U];

/* clang-format off */
/* QF_active[] array defines all active object control blocks */
QActiveCB const Q_ROM QF_active[] = {
    { (QActive *)0U,          (QEvt *)0U,       0U                      },
    { (QActive *)&AO_Blinky,  l_blinkyQSto,     Q_DIM(l_blinkyQSto)     }
};
/* clang-format on */

/*******************************************************************************
 * Code
 ******************************************************************************/
void Q_onAssert(char const Q_ROM *const Q_ROM_VAR module, int loc)
{
    while (1U)
    {
    }
}

void QF_onStartup(void)
{
    INTERRUPT_GlobalEnable();
}

void QK_onIdle(void)
{
}

int main(void)
{
    /* Instantiate all Blinky AO */
    Blinky_Ctor();

    /* Initialize the QF-nano framework */
    QF_init(Q_DIM(QF_active));

    /* Initialize the Board Support Package */
    BSP_Init();

    /* Transfer control to QF-nano */
    return QF_run();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
