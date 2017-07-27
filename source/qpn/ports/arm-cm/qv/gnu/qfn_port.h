/**
* @file
* @brief QF-nano port to Cortex-M, cooperative QV kernel, GNU-ARM toolset
* @cond
******************************************************************************
* Last Updated for Version: 5.9.3
* Date of the Last Update:  2017-07-03
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2005-2017 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* https://state-machine.com
* mailto:info@state-machine.com
******************************************************************************
* @endcond
*/
#ifndef qfn_port_h
#define qfn_port_h

/* QF interrupt disable/enable and log2()... */
#ifdef ARM_ARCH_V6M /* Cortex-M0/M0+/M1 ?, see NOTE2 */

    #define QF_INT_DISABLE()    __asm volatile ("cpsid i")
    #define QF_INT_ENABLE()     __asm volatile ("cpsie i")

    /* QF-aware ISR priority for CMSIS function NVIC_SetPriority(), NOTE2 */
    #define QF_AWARE_ISR_CMSIS_PRI  0

    /* macro to put the CPU to sleep inside QV_onIdle() */
    #define QV_CPU_SLEEP() do { \
        __asm volatile ("wfi"); \
        QF_INT_ENABLE(); \
    } while (0)

#else /* Cortex-M3/M4/M7, see NOTE3 */

    /* Cortex-M3/M4/M7 alternative interrupt disabling with PRIMASK */
    #define QF_PRIMASK_DISABLE() __asm volatile ("cpsid i")
    #define QF_PRIMASK_ENABLE()  __asm volatile ("cpsie i")

    /* Cortex-M3/M4/M7 interrupt disabling policy, see NOTE3 */
    #define QF_INT_DISABLE() do { \
        QF_PRIMASK_DISABLE(); \
        QF_SET_BASEPRI(QF_BASEPRI); \
        QF_PRIMASK_ENABLE(); \
    } while (0)
    #define QF_INT_ENABLE()     QF_SET_BASEPRI(0U)

    /* NOTE: keep in synch with the value defined in "qk_port.s" */
    #define QF_BASEPRI          (0xFFU >> 2)

    /* QF-aware ISR priority for CMSIS function NVIC_SetPriority(), NOTE4 */
    #define QF_AWARE_ISR_CMSIS_PRI (QF_BASEPRI >> (8 - __NVIC_PRIO_BITS))

    /* macro to put the CPU to sleep inside QV_onIdle() */
    #define QV_CPU_SLEEP() do { \
        __asm volatile ("cpsid i"); \
        QF_INT_ENABLE(); \
        __asm volatile ("wfi"); \
        __asm volatile ("cpsie i"); \
    } while (0)

    /* Cortex-M3/M4/M4F provide the CLZ instruction for fast LOG2 */
    #define QF_LOG2(n_) ((uint_fast8_t)(32U - __builtin_clz(n_)))

    /* macro for getting the BASEPRI register */
    #define QF_GET_BASEPRI(basepri_) __asm volatile (\
        "mrs %0,BASEPRI" : "=r" (basepri_) :: )

    /* macro for setting the BASEPRI register */
    #define QF_SET_BASEPRI(basepri_) __asm volatile (\
        "msr BASEPRI,%0" :: "r" (basepri_) : )

    /* initialization of the QV kernel for Cortex-M3/M4/M7 */
    #define QV_INIT() QV_init()
    void QV_init(void);

#endif

/* interrupt nesting policy for ISR level (ISRs can nest) */
#define QF_ISR_NEST

#include <stdint.h>     /* Exact-width types. WG14/N843 C99 Standard */
#include <stdbool.h>    /* Boolean type.      WG14/N843 C99 Standard */

#include "qepn.h"       /* QEP-nano platform-independent public interface */
#include "qfn.h"        /* QF-nano platform-independent public interface */
#include "qvn.h"        /* QV-nano cooperative kernel interface */

/*****************************************************************************
* NOTE2:
* On Cortex-M0/M0+/M1 (architecture v6-M, v6S-M), the interrupt disabling
* policy uses the PRIMASK register to disable interrupts globally. The
* QF_AWARE_ISR_CMSIS_PRI level is zero, meaning that all interrupts are
* "kernel-aware".
*
* NOTE3:
* On Cortex-M3/M4/M4F, the interrupt disable/enable policy uses the BASEPRI
* register (which is not implemented in Cortex-M0/M0+/M1) to disable
* interrupts only with priority lower than the level specified by the
* QF_BASEPRI macro. The interrupts with priorities above QF_BASEPRI (i.e.,
* with numerical priority values lower than QF_BASEPRI) are not disabled in
* this method. These free-running interrupts are not allowed to call any QF
* services, because QF is not aware of these interrupts. Coversely, only
* "QF-aware" interrupts, with numerical values of priorities eqal to or
* higher than QF_BASEPRI, can call QF services.
*
* NOTE4:
* For Cortex-M3/M4/M7, the macro QF_BASEPRI leaves the top 2 priority bits
* empty for QF-aware interrupts. This is the highest-possible priority
* (lowest possible numerical value) for the guaranteed 3 priority bits
* implemented in the NVIC.
*
* NOTE5:
* The QF_AWARE_ISR_CMSIS_PRI macro is useful as an offset for enumerating
* the QF-aware interrupt priority levels in the applications, whereas the
* numerical values of the QF-aware interrupts must be greater or equal to
* QF_AWARE_ISR_CMSIS_PRI. The enumerated values based on
* QF_AWARE_ISR_CMSIS_PRI can be passed directly to the CMSIS function
* NVIC_SetPriority(), which shifts them by (8 - __NVIC_PRIO_BITS) into the
* correct bit position, while __NVIC_PRIO_BITS is the CMSIS macro defining
* the number of implemented priority bits in the NVIC. Please note that
* the macro QF_AWARE_ISR_CMSIS_PRI is intended only for applications and
* is not used inside the QF port, which remains generic and not dependent
* on the number of implemented priority bits in the NVIC.
*/

#endif /* qfn_port_h */