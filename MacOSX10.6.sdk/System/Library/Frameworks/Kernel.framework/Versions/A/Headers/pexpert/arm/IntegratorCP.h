/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
#ifndef _PEXPERT_ARM_INTEGRATORCP_H
#define _PEXPERT_ARM_INTEGRATORCP_H

#define ARM_BOARD_CONFIG_INTEGRATORCP

// Count/Timer
#define	rTimer0Load	(*(volatile unsigned *)(timer_base + 0x000)) // Timer 0 Load Value
#define	rTimer0Value	(*(volatile unsigned *)(timer_base + 0x004)) // Timer 0 Current Value
#define	rTimer0Control	(*(volatile unsigned *)(timer_base + 0x008)) // Timer 0 Control Register
#define	rTimer0IntClr	(*(volatile unsigned *)(timer_base + 0x00C)) // Timer 0 Interrupt Clear
#define	rTimer0RIS	(*(volatile unsigned *)(timer_base + 0x010)) // Timer 0 Raw Interrupt Status
#define	rTimer0MIS	(*(volatile unsigned *)(timer_base + 0x014)) // Timer 0 Masked Interrupt Status
#define	rTimer0BGLoad	(*(volatile unsigned *)(timer_base + 0x018)) // Timer 0 Background Load Value

#define	rTimer1Load	(*(volatile unsigned *)(timer_base + 0x100)) // Timer 1 Load Value
#define	rTimer1Value	(*(volatile unsigned *)(timer_base + 0x104)) // Timer 1 Current Value
#define	rTimer1Control	(*(volatile unsigned *)(timer_base + 0x108)) // Timer 1 Control Register
#define	rTimer1IntClr	(*(volatile unsigned *)(timer_base + 0x10C)) // Timer 1 Interrupt Clear
#define	rTimer1RIS	(*(volatile unsigned *)(timer_base + 0x110)) // Timer 1 Raw Interrupt Status
#define	rTimer1MIS	(*(volatile unsigned *)(timer_base + 0x114)) // Timer 1 Masked Interrupt Status
#define	rTimer1BGLoad	(*(volatile unsigned *)(timer_base + 0x118)) // Timer 1 Background Load Value

#define	rTimer2Load	(*(volatile unsigned *)(timer_base + 0x200)) // Timer 2 Load Value
#define	rTimer2Value	(*(volatile unsigned *)(timer_base + 0x204)) // Timer 2 Current Value
#define	rTimer2Control	(*(volatile unsigned *)(timer_base + 0x208)) // Timer 2 Control Register
#define	rTimer2IntClr	(*(volatile unsigned *)(timer_base + 0x20C)) // Timer 2 Interrupt Clear
#define	rTimer2RIS	(*(volatile unsigned *)(timer_base + 0x210)) // Timer 2 Raw Interrupt Status
#define	rTimer2MIS	(*(volatile unsigned *)(timer_base + 0x214)) // Timer 2 Masked Interrupt Status
#define	rTimer2BGLoad	(*(volatile unsigned *)(timer_base + 0x218)) // Timer 2 Background Load Value


// Primary Interrupt Controller
#define rPIC_IRQ_STATUS		(*(volatile unsigned *)(pic_base + 0x000)) // IRQ Gated Interrupt Status
#define rPIC_IRQ_RAWSTAT	(*(volatile unsigned *)(pic_base + 0x004)) // IRQ Raw Interrupt Status
#define rPIC_IRQ_ENABLESET	(*(volatile unsigned *)(pic_base + 0x008)) // IRQ Enable Set
#define rPIC_IRQ_ENABLECLR	(*(volatile unsigned *)(pic_base + 0x00C)) // IRQ Enable Clear
#define rPIC_INT_SOFTSET	(*(volatile unsigned *)(pic_base + 0x010)) // Software Interrupt Set
#define rPIC_INT_SOFTCLR	(*(volatile unsigned *)(pic_base + 0x014)) // Software Interrupt Clear
#define rPIC_FIQ_STATUS		(*(volatile unsigned *)(pic_base + 0x020)) // FIQ Gated Interrupt Status
#define rPIC_FIQ_RAWSTAT	(*(volatile unsigned *)(pic_base + 0x024)) // FIQ Raw Interrupt Status
#define rPIC_FIQ_ENABLESET	(*(volatile unsigned *)(pic_base + 0x028)) // FIQ Enable Set
#define rPIC_FIQ_ENABLECLR	(*(volatile unsigned *)(pic_base + 0x02C)) // FIQ Enable Clear


// UART
#define rUART0DR	(*(volatile unsigned *)(uart_base + 0x000)) // UART 0 Data Register
#define rUART0RSR	(*(volatile unsigned *)(uart_base + 0x004)) // UART 0 Receive Status Register
#define rUART0FR	(*(volatile unsigned *)(uart_base + 0x018)) // UART 0 Flag Register
#define rUART0ILPR	(*(volatile unsigned *)(uart_base + 0x020)) // UART 0 IrDA Low Power Counter Register
#define rUART0IBRD	(*(volatile unsigned *)(uart_base + 0x024)) // UART 0 Integer Baud Rate DivisorRegister
#define rUART0FBRD	(*(volatile unsigned *)(uart_base + 0x028)) // UART 0 Fractional Baud Rate DivisorRegister
#define rUART0LCR_H	(*(volatile unsigned *)(uart_base + 0x02C)) // UART 0 Line Control High Byte Register
#define rUART0CR	(*(volatile unsigned *)(uart_base + 0x030)) // UART 0 Control Register
#define rUART0IFLS	(*(volatile unsigned *)(uart_base + 0x034)) // UART 0 Interrupt FIFO Level Select Register
#define rUART0IMSC	(*(volatile unsigned *)(uart_base + 0x038)) // UART 0 Interrupt Mask Set/Clear Register
#define rUART0RIS	(*(volatile unsigned *)(uart_base + 0x03C)) // UART 0 Raw Interrupt Register
#define rUART0MIS	(*(volatile unsigned *)(uart_base + 0x040)) // UART 0 Masked Interrupt Status Register
#define rUART0ICR	(*(volatile unsigned *)(uart_base + 0x044)) // UART 0 Interrupt Clear Register
#define rUART0DMACR	(*(volatile unsigned *)(uart_base + 0x048)) // UART 0 DMA Control Register

#define rUART1DR	(*(volatile unsigned *)(uart1_base + 0x000)) // UART 1 Data Register
#define rUART1RSR	(*(volatile unsigned *)(uart1_base + 0x004)) // UART 1 Receive Status Register
#define rUART1FR	(*(volatile unsigned *)(uart1_base + 0x018)) // UART 1 Flag Register
#define rUART1ILPR	(*(volatile unsigned *)(uart1_base + 0x020)) // UART 1 IrDA Low Power Counter Register
#define rUART1IBRD	(*(volatile unsigned *)(uart1_base + 0x024)) // UART 1 Integer Baud Rate DivisorRegister
#define rUART1FBRD	(*(volatile unsigned *)(uart1_base + 0x028)) // UART 1 Fractional Baud Rate DivisorRegister
#define rUART1LCR_H	(*(volatile unsigned *)(uart1_base + 0x02C)) // UART 1 Line Control High Byte Register
#define rUART1CR	(*(volatile unsigned *)(uart1_base + 0x030)) // UART 1 Control Register
#define rUART1IFLS	(*(volatile unsigned *)(uart1_base + 0x034)) // UART 1 Interrupt FIFO Level Select Register
#define rUART1IMSC	(*(volatile unsigned *)(uart1_base + 0x038)) // UART 1 Interrupt Mask Set/Clear Register
#define rUART1RIS	(*(volatile unsigned *)(uart1_base + 0x03C)) // UART 1 Raw Interrupt Register
#define rUART1MIS	(*(volatile unsigned *)(uart1_base + 0x040)) // UART 1 Masked Interrupt Status Register
#define rUART1ICR	(*(volatile unsigned *)(uart1_base + 0x044)) // UART 1 Interrupt Clear Register
#define rUART1DMACR	(*(volatile unsigned *)(uart1_base + 0x048)) // UART 1 DMA Control Register

#endif /* _PEXPERT_ARM_INTEGRATORCP_H */
