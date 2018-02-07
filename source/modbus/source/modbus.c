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
#include "modbus_conf.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _modbus
{                     /* the Blinky active object */
    QActive super;    /* inherit QActive */
    QTimeEvt timeEvt; /* private time event generator */
} modbus_t;

#define REG_INPUT_START 1000
#define REG_INPUT_NREGS 4

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
static USHORT usRegInputStart = REG_INPUT_START;
static USHORT usRegInputBuf[REG_INPUT_NREGS] = {0x11, 0x22, 0x33, 0x44};

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
    int iRegIndex;

    usAddress--;
    if ((usAddress >= REG_INPUT_START) && (usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS))
    {
        iRegIndex = (int)(usAddress - usRegInputStart);
        while (usNRegs > 0)
        {
            *pucRegBuffer++ = (unsigned char)(usRegInputBuf[iRegIndex] >> 8);
            *pucRegBuffer++ = (unsigned char)(usRegInputBuf[iRegIndex] & 0xFF);
            iRegIndex++;
            usNRegs--;
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
}

static QState Modbus_Initial(modbus_t *const me, QEvt const *const e)
{
    (void)e; /* avoid compiler warning about unused parameter */

    /* Initialize the Modbus protocol stack. */
    (void)eMBInit(MB_RTU, MODBUS_SLAVE_ADDRESS, MODBUS_PORT, MODBUS_BAUD_RATE, MB_PAR_NONE);

    return Q_TRAN(&Modbus_Running);
}

static QState Modbus_Running(modbus_t *const me, QEvt const *const e)
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
