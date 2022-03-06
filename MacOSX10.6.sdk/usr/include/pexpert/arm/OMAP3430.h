/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
#ifndef _PEXPERT_ARM_OMAP3430_H
#define _PEXPERT_ARM_OMAP3430_H

#define rINTCPS_CONTROL          (*(volatile unsigned *)(pic_base + 0x048)) 
#define INTCPS_CONTROL_NEWFIQAGR0x02

#define rINTCPS_ISR_SET0	(*(volatile unsigned *)(pic_base + 0x08c))
#define rINTCPS_ILR0		(*(volatile unsigned *)(pic_base + 0x100))
#define rINTCPS_ILR39		(*(volatile unsigned *)(pic_base + (0x100+(0x4*39))))

#define rINTCPS_MIR0		(*(volatile unsigned *)(pic_base + 0x084))
#define rINTCPS_MIR1		(*(volatile unsigned *)(pic_base + 0x0a4))
#define rINTCPS_MIR_CLEAR0	(*(volatile unsigned *)(pic_base + 0x088))
#define rINTCPS_MIR_CLEAR1	(*(volatile unsigned *)(pic_base + 0x0a8))
#define rINTCPS_MIR_SET0	(*(volatile unsigned *)(pic_base + 0x08c))
#define rINTCPS_MIR_SET1	(*(volatile unsigned *)(pic_base + 0x0ac))

#define rINTCPS_ISR_CLEAR0	(*(volatile unsigned *)(pic_base + 0x094))
#define rINTCPS_ISR_CLEAR1	(*(volatile unsigned *)(pic_base + 0x0b4))

// GPTIMER 2 registers
// interrupt enable register, interrupt status register, load register
// trigger register, match value register, control register
#define rGPT2_TIER    (*(volatile unsigned *)(timer_base + 0x201c))
#define rGPT2_TISR    (*(volatile unsigned *)(timer_base + 0x2018))
#define rGPT2_TLDR    (*(volatile unsigned *)(timer_base + 0x202c))
#define rGPT2_TTGR    (*(volatile unsigned *)(timer_base + 0x2030))
#define rGPT2_TMAR    (*(volatile unsigned *)(timer_base + 0x2038))
#define rGPT2_TCLR    (*(volatile unsigned *)(timer_base + 0x2024))
#define rGPT2_TOCR    (*(volatile unsigned *)(timer_base + 0x2054))
#define rGPT2_TOWR    (*(volatile unsigned *)(timer_base + 0x2058))

// GPTIMER 3 registers
// interrupt enable register, interrupt status register, load register
// trigger register, match value register, control register
#define rGPT3_TIER    (*(volatile unsigned *)(timer_base + 0x401c))
#define rGPT3_TISR    (*(volatile unsigned *)(timer_base + 0x4018))
#define rGPT3_TLDR    (*(volatile unsigned *)(timer_base + 0x402c))
#define rGPT3_TTGR    (*(volatile unsigned *)(timer_base + 0x4030))
#define rGPT3_TMAR    (*(volatile unsigned *)(timer_base + 0x4038))
#define rGPT3_TCLR    (*(volatile unsigned *)(timer_base + 0x4024))

// PER_CM registers

//  CM_FCLKEN_PER, CM_ICLKEN_PER, CM_IDLEST_PER  
#define rPRCM_FCLK_PER		  (*(volatile unsigned *)(prmc_base + 0x1000))
#define rPRCM_ICLK_PER		  (*(volatile unsigned *)(prmc_base + 0x1010))
#define rPRCM_IDLEST_PER	  (*(volatile unsigned *)(prmc_base + 0x1020))

#endif	/* _PEXPERT_ARM_OMAP3430_H */
