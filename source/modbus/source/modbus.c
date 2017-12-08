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
#define MODBUS_DISCRETE_START (0x1000U)
#define MODBUS_DISCRETE_BUF_SIZE (16U)
#define MODBUS_COILS_START (0x2000U)
#define MODBUS_COILS_BUF_SIZE (16U)
#define MODBUS_INPUT_START (0x3000U)
#define MODBUS_INPUT_BUF_SIZE (16U)
#define MODBUS_HOLDING_START (0x4000U)
#define MODBUS_HOLDING_BUF_SIZE (16U)
#define MODBUS_EXECUTE_PERIOD (10U)
#define MODBUS_SLAVE_ADDRESS (0x01U)
#define MODBUS_PORT (0U)
#define MODBUS_BAUD_RATE (9600U)

typedef struct _modbus
{                     /* the Blinky active object */
    QActive super;    /* inherit QActive */
    QTimeEvt timeEvt; /* private time event generator */
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
// static uint8_t mbRegDiscreteBuf[MODBUS_DISCRETE_BUF_SIZE] = {0U};
// static uint8_t mbRegCoilsBuf[MODBUS_COILS_BUF_SIZE] = {0U};
// static uint8_t mbRegInputBuf[MODBUS_INPUT_BUF_SIZE] = {0U};
// static uint8_t mbRegHoldingBuf[MODBUS_HOLDING_BUF_SIZE] = {0U};
QActive *const AO_Modbus = &l_modbus.super;

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
    return MB_ENOREG;
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
