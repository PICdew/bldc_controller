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

#ifndef __BLINKY_H__
#define __BLINKY_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
extern QActive *const AO_Blinky;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void Blinky_Ctor(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BLINKY_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
