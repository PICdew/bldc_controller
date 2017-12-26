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

#include <stdbool.h>
#include "qpc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum _modbus_data_type {
    MODBUS_DataType_Discrete = 0U,
    MODBUS_DataType_Coils = 1U,
    MODBUS_DataType_Input = 2U,
    MODBUS_DataType_Holding = 3U,
} modbus_data_type_t;

typedef struct _modbus_update_evt
{
    QEvt super;
    modbus_data_type_t type;
    uint16_t offset;
    uint16_t num;
} modbus_update_evt_t;

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
