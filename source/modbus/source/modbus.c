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
#include "bldc_controller.h"
#include "bsp.h"
#include "mb.h"
#include "modbus.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MODBUS_EXECUTE_PERIOD (10U)
#define MODBUS_SLAVE_ADDRESS (0x01U)
#define MODBUS_PORT (0U)
#define MODBUS_BAUD_RATE (9600U)

typedef struct _modbus
{                     /* the Blinky active object */
    QActive super;    /* inherit QActive */
    QTimeEvt timeEvt; /* private time event generator */
    QMutex mutex;     /* mutex used to lock Modbus data */
} modbus_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static QState Modbus_Initial(modbus_t *const me, QEvt const *const e);
static QState Modbus_Running(modbus_t *const me, QEvt const *const e);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static modbus_t l_modbus;
QActive *const AO_Modbus = &l_modbus.super;
static uint8_t mbRegDiscreteBuf[MB_REG_DISCRETE_NREGS];
static uint8_t mbRegCoilsBuf[MB_REG_COILS_NREGS];
static uint8_t mbRegInputBuf[MB_REG_INPUT_NREGS];
static uint8_t mbRegHoldingBuf[MB_REG_HOLDING_NREGS];

/*******************************************************************************
 * Code
 ******************************************************************************/
eMBErrorCode eMBRegDiscreteCB(uint8_t *pucRegBuffer, uint16_t usAddress, uint16_t usNDiscrete)
{
    return MB_ENOREG;
}

eMBErrorCode eMBRegCoilsCB(uint8_t *pucRegBuffer, uint16_t usAddress, uint16_t usNCoils, eMBRegisterMode eMode)
{
    return MB_ENOREG;
}

eMBErrorCode eMBRegInputCB(uint8_t *pucRegBuffer, uint16_t usAddress, uint16_t usNRegs)
{
    eMBErrorCode eStatus = MB_ENOERR;
    uint16_t i;

    if ((usAddress >= MB_REG_INPUT_START) && (usAddress + usNRegs <= MB_REG_INPUT_START + MB_REG_INPUT_NREGS))
    {
        for (i = ((usAddress - MB_REG_INPUT_START) >> 1U); i < usNRegs; i++)
        {
            *pucRegBuffer++ = (uint8_t)(mbRegInputBuf[i] >> 8U);
            *pucRegBuffer++ = (uint8_t)(mbRegInputBuf[i] & 0xFFU);
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode eMBRegHoldingCB(uint8_t *pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, eMBRegisterMode eMode)
{
    return MB_ENOREG;
}

void Modbus_Ctor(void)
{
    modbus_t *const me = &l_modbus;

    QActive_ctor(&me->super, Q_STATE_CAST(&Modbus_Initial));
    QTimeEvt_ctorX(&me->timeEvt, &me->super, MODBUS_TICK_SIG, 0U);
    QMutex_init(&me->mutex, QF_MAX_ACTIVE);
}

bool Modbus_Read(uint16_t *buffer, uint16_t address, uint16_t num, modbus_data_type_t type)
{
    modbus_t *const me = &l_modbus;
    bool result;

    QMutex_lock(&me->mutex);
    switch (type)
    {
        case MODBUS_DataType_Discrete:
            result = true;
            break;

        case MODBUS_DataType_Coils:
            result = true;
            break;

        case MODBUS_DataType_Input:
            result = true;
            break;

        case MODBUS_DataType_Holding:
            result = true;
            break;

        default:
            result = false;
    }
    QMutex_unlock(&me->mutex);

    return result;
}

bool Modbus_Write(uint16_t *buffer, uint16_t address, uint16_t num, modbus_data_type_t type)
{
    modbus_t *const me = &l_modbus;
    bool result;

    QMutex_lock(&me->mutex);
    switch (type)
    {
        case MODBUS_DataType_Discrete:
            result = true;
            break;

        case MODBUS_DataType_Coils:
            result = true;
            break;

        case MODBUS_DataType_Input:
            result = true;
            break;

        case MODBUS_DataType_Holding:
            result = true;
            break;

        default:
            result = false;
    }
    QMutex_unlock(&me->mutex);

    return result;
}

QState Modbus_Initial(modbus_t *const me, QEvt const *const e)
{
    (void)e; /* avoid compiler warning about unused parameter */

    /* Initialize the Modbus protocol stack. */
    (void)eMBInit(MB_RTU, MODBUS_SLAVE_ADDRESS, MODBUS_PORT, MODBUS_BAUD_RATE, MB_PAR_NONE);

    return Q_TRAN(&Modbus_Running);
}

QState Modbus_Running(modbus_t *const me, QEvt const *const e)
{
    QState status;

    switch (e->sig)
    {
        case Q_ENTRY_SIG:
        {
            /* Enable the Modbus protocol stack */
            (void)eMBEnable();
            /* arm the time event to expire in MODBUS_EXECUTE_PERIOD ms */
            QTimeEvt_armX(&me->timeEvt, MODBUS_EXECUTE_PERIOD, MODBUS_EXECUTE_PERIOD);

            status = Q_HANDLED();
            break;
        }

        case MODBUS_TICK_SIG:
        {
            /* The main pooling loop of the Modbus protocol stack. */
            (void)eMBPoll();

            status = Q_HANDLED();
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
