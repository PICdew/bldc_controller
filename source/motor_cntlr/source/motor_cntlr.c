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
#include "motor_cntlr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _motor_cntlr
{
    QActive super; /* inherit QActive */
} motor_cntlr_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
motor_cntlr_t AO_MotorCntlr;

/*******************************************************************************
 * Code
 ******************************************************************************/
void MotorCntlr_Ctor(void)
{
}

/*******************************************************************************
 * EOF
 ******************************************************************************/