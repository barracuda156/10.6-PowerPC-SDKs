/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
#ifndef _PEXPERT_ARM_MX31_H
#define _PEXPERT_ARM_MX31_H

#define ARM_BOARD_CONFIG_MX31

// AVIC
#define rINTCNTL	(*(volatile unsigned *)(pic_base + 0x000)) // AVIC Interrupt Control Register
#define rNIMASK		(*(volatile unsigned *)(pic_base + 0x004)) // AVIC Normal Interrupt Mask Register
#define rINTENNUM	(*(volatile unsigned *)(pic_base + 0x008)) // AVIC Interrupt Enable Number Register
#define rINTDISNUM	(*(volatile unsigned *)(pic_base + 0x00C)) // AVIC Interrupt Disable Number Register
#define rINTENABLEH	(*(volatile unsigned *)(pic_base + 0x010)) // AVIC Interrupt Enable Register High
#define rINTENABLEL	(*(volatile unsigned *)(pic_base + 0x014)) // AVIC Interrupt Enable Register Low
#define rINTTYPEH	(*(volatile unsigned *)(pic_base + 0x018)) // AVIC Interrupt Type Register High
#define rINTTYPEL	(*(volatile unsigned *)(pic_base + 0x01C)) // AVIC Interrupt Type Register Low
#define rNIPRIORITY(x)	(*(volatile unsigned *)(pic_base + 0x020 4 * (x))) // AVIC Normal Interrupt Priority Registers
#define rNIVECSR	(*(volatile unsigned *)(pic_base + 0x040)) // AVIC Normal Interrupt Vector and Status Register
#define rFIVECSR	(*(volatile unsigned *)(pic_base + 0x044)) // AVIC Fast Interrupt Vector and Status Register
#define rINTSRCH	(*(volatile unsigned *)(pic_base + 0x048)) // AVIC Interrupt Source Register High
#define rINTSRCL	(*(volatile unsigned *)(pic_base + 0x04C)) // AVIC Interrupt Source Register Low
#define rINTFRCH	(*(volatile unsigned *)(pic_base + 0x050)) // AVIC Interrupt Force Register High
#define rINTFRCL	(*(volatile unsigned *)(pic_base + 0x054)) // AVIC Interrupt Force Register Low
#define rNIPNDH		(*(volatile unsigned *)(pic_base + 0x058)) // AVIC Normal Interrupt Pending Register High
#define rNIPNDL		(*(volatile unsigned *)(pic_base + 0x05C)) // AVIC Normal Interrupt Pending Register Low
#define rFIPNDH		(*(volatile unsigned *)(pic_base + 0x060)) // AVIC Fast Interrupt Pending Register High
#define rFIPNDL		(*(volatile unsigned *)(pic_base + 0x064)) // AVIC Fast Interrupt Pending Register Low
#define rVECTOR(x)	(*(volatile unsigned *)(pic_base + 0x100 + 4 * (x))) // AVIC Vector Registers


// GPT
#define rGPTCR		(*(volatile unsigned *)(timer_base + 0x00)) // GPT Control Register
#define rGPTPR		(*(volatile unsigned *)(timer_base + 0x04)) // GPT Prescaler Register
#define rGPTSR		(*(volatile unsigned *)(timer_base + 0x08)) // GPT Status Register
#define rGPTIR		(*(volatile unsigned *)(timer_base + 0x0C)) // GPT Interrupt Register
#define rGPTOCR1	(*(volatile unsigned *)(timer_base + 0x10)) // GPT Output Compare Register 1
#define rGPTOCR2	(*(volatile unsigned *)(timer_base + 0x14)) // GPT Output Compare Register 2
#define rGPTOCR3	(*(volatile unsigned *)(timer_base + 0x18)) // GPT Output Compare Register 3
#define rGPTICR1	(*(volatile unsigned *)(timer_base + 0x1C)) // GPT Input Capture Register 1
#define rGPTICR2	(*(volatile unsigned *)(timer_base + 0x20)) // GPT Input Capture Register 2
#define rGPTCNT		(*(volatile unsigned *)(timer_base + 0x24)) // GPT Counter Register

// UART
#define rURXD1		(*(volatile unsigned *)(uart_base + 0x00)) // UART 1 Receiver Register
#define rUTXD1		(*(volatile unsigned *)(uart_base + 0x40)) // UART 1 Transmitter Register
#define rUTS1		(*(volatile unsigned *)(uart_base + 0xB4)) // UART 1 Test Register

#define rURXD2		(*(volatile unsigned *)(uart2_base + 0x00)) // UART 2 Receiver Register
#define rUTXD2		(*(volatile unsigned *)(uart2_base + 0x40)) // UART 2 Transmitter Register
#define rUTS2		(*(volatile unsigned *)(uart2_base + 0xB4)) // UART 2 Test Register

#endif /* ! _PEXPERT_ARM_MX31_H */
