/*
 * Copyright (C) 2018 Wang Ge
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

#include "board.h"
#include "qpn.h"
#include "bldc_controller.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
static QEvt l_blinkyQSto[10];
QActiveCB const Q_ROM QF_active[] = {
    { (QActive *)0,           (QEvt *)0,        0U                      },
    { (QActive *)&AO_Blinky,  l_blinkyQSto,     Q_DIM(l_blinkyQSto)     }
};

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* Instantiate the AOs */
    Blinky_ctor();

    /* Initialize the QF-nano framework */
    QF_init(Q_DIM(QF_active));

    /* Initialize the Board Support Package */
    BOARD_Init();

    /* Transfer control to QF-nano */
    return QF_run();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
