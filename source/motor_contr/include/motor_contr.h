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

#ifndef __MOTOR_CONTR_H__
#define __MOTOR_CONTR_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum _motor_contr_signals
{
    TIMEOUT_SIG = Q_USER_SIG, /* the last published signal */
};

extern struct _motor_contr AO_MotorContr;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void MotorContr_Ctor(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __MOTOR_CONTR_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
