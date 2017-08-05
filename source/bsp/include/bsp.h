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

#ifndef __BSP_H__
#define __BSP_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BSP_TICKS_PER_SEC (1000U)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void BSP_Init(void);

static inline void BSP_ledOff(void)
{
}

static inline void BSP_ledOn(void)
{
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BSP_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
