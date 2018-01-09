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

#ifndef __BLDC_CONTROLLER__
#define __BLDC_CONTROLLER__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum _bldc_controller_signals
{
    TIMEOUT_SIG = Q_USER_SIG, /* the last published signal */
    MODBUS_UPDATE_SIG,        /* Modbus data object update notification */
    MAX_PUB_SIG,              /* the last published signal */
    MODBUS_TICK_SIG,          /* tick signal for Modbus Stack */
    MODBUS_READ_SIG,          /* read Modbus data object */
    MODBUS_READ_ACK_SIG,      /* read Modbus data object ack */
    MODBUS_WRITE_SIG,         /* write Modbus data object */
    MODBUS_WRITE_ACK_SIG,     /* write Modbus data object ack */
    MAX_SIG                   /* the last signal (keep always last) */
};

#endif /* __BLDC_CONTROLLER__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
