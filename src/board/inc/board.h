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

#ifndef BOARD_H
#define BOARD_H

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_TICKS_PER_SEC (1000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

void BOARD_Init(void);
void BOARD_ledOff(void);
void BOARD_ledOn(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
