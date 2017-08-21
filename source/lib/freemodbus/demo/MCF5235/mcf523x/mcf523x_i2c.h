/************************************************************************************
 * Copyright @ 1995-2005 metrowerks inc. All rights reserved.                       *
 *                                                                                  *
 *                                                                                  *
 *    $RCSfile: mcf523x_i2c.h,v $                                                            *
 *    $Revision: 1.1 $                                                              *
 *    $Date: 2006/05/14 21:59:16 $                                                  *
 *                                                                                  *
 * DESCRIPTION                                                                      *
 *   Register and bit definitions for the MCF523X.                                  *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * NOTE                                                                             *
 *                                                                                  *
 *                                                                                  *
 *                                                                                  *
 * HISTORY                                                                          *
 *                                                                                  *	
 ************************************************************************************/

#ifndef __MCF523X_I2C_H__
#define __MCF523X_I2C_H__

/*********************************************************************
*
* I2C Module (I2C)
*
*********************************************************************/

/* Register read/write macros */
#define MCF_I2C_I2AR     (*(vuint8 *)(void*)(&__IPSBAR[0x000300]))
#define MCF_I2C_I2FDR    (*(vuint8 *)(void*)(&__IPSBAR[0x000304]))
#define MCF_I2C_I2CR     (*(vuint8 *)(void*)(&__IPSBAR[0x000308]))
#define MCF_I2C_I2SR     (*(vuint8 *)(void*)(&__IPSBAR[0x00030C]))
#define MCF_I2C_I2DR     (*(vuint8 *)(void*)(&__IPSBAR[0x000310]))
#define MCF_I2C_I2ICR    (*(vuint8 *)(void*)(&__IPSBAR[0x000320]))

/* Bit definitions and macros for MCF_I2C_I2AR */
#define MCF_I2C_I2AR_ADR(x)    (((x)&0x7F)<<1)

/* Bit definitions and macros for MCF_I2C_I2FDR */
#define MCF_I2C_I2FDR_IC(x)    (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF_I2C_I2CR */
#define MCF_I2C_I2CR_RSTA      (0x04)
#define MCF_I2C_I2CR_TXAK      (0x08)
#define MCF_I2C_I2CR_MTX       (0x10)
#define MCF_I2C_I2CR_MSTA      (0x20)
#define MCF_I2C_I2CR_IIEN      (0x40)
#define MCF_I2C_I2CR_IEN       (0x80)

/* Bit definitions and macros for MCF_I2C_I2SR */
#define MCF_I2C_I2SR_RXAK      (0x01)
#define MCF_I2C_I2SR_IIF       (0x02)
#define MCF_I2C_I2SR_SRW       (0x04)
#define MCF_I2C_I2SR_IAL       (0x10)
#define MCF_I2C_I2SR_IBB       (0x20)
#define MCF_I2C_I2SR_IAAS      (0x40)
#define MCF_I2C_I2SR_ICF       (0x80)

/* Bit definitions and macros for MCF_I2C_I2ICR */
#define MCF_I2C_I2ICR_IE       (0x01)
#define MCF_I2C_I2ICR_RE       (0x02)
#define MCF_I2C_I2ICR_TE       (0x04)
#define MCF_I2C_I2ICR_BNBE     (0x08)

/********************************************************************/

#endif /* __MCF523X_I2C_H__ */
