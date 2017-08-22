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

#ifndef __PORT_H__
#define __PORT_H__

#include <xc.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define INLINE            inline
#define PR_BEGIN_EXTERN_C extern "C" {
#define PR_END_EXTERN_C   }
#define assert(x)

#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#define ENTER_CRITICAL_SECTION() __builtin_disi(0x3FFFU)
#define EXIT_CRITICAL_SECTION()  __builtin_disi(0x0000U)

#define MB_PORT_HAS_CLOSE	                 (1)
#define MB_ASCII_TIMEOUT_WAIT_BEFORE_SEND_MS (2)

typedef bool BOOL;
typedef uint8_t UCHAR;
typedef int8_t CHAR;
typedef uint16_t USHORT;
typedef int16_t SHORT;
typedef uint32_t ULONG;
typedef int32_t LONG;

#endif /* __PORT_H__ */
