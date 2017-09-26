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

#ifndef __MODBUS_H__
#define __MODBUS_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MB_REG_INPUT_START (0x0U)
#define MB_REG_INPUT_NREGS (64U)
#define MB_REG_HOLDING_START (0x1000U)
#define MB_REG_HOLDING_NREGS (32U)

extern QActive *const AO_Modbus;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void Modbus_Ctor(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __MODBUS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
