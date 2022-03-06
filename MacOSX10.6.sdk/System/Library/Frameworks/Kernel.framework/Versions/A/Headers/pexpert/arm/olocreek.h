/*
 * Copyright (c) 2006-2007 Apple Inc. All rights reserved.
 */
#ifndef _PEXPERT_ARM_OLOCREEK_H
#define _PEXPERT_ARM_OLOCREEK_H

//#define ARM_BOARD_CONFIG_OLOCREEK

/* Timers */
#define T0_RELOAD	(*(volatile unsigned *)(timer_base + 0x00)) // Timer/Counter #0 Reload Register (also called T0_DATA)
#define T0_CAPTURE	(*(volatile unsigned *)(timer_base + 0x04)) // Timer/Counter #0 Capture Register
#define T0_STATUS	(*(volatile unsigned *)(timer_base + 0x08)) // Timer Unit Status Register
#define T0_CONFIG	(*(volatile unsigned *)(timer_base + 0x0C)) // Timer/Counter #0 Configuration Register
#define T1_RELOAD	(*(volatile unsigned *)(timer_base + 0x10)) // Timer/Counter #1 Reload Register (also called T1_DATA)
#define T1_CAPTURE	(*(volatile unsigned *)(timer_base + 0x14)) // Timer/Counter #1 Capture Register
#define T1_STATUS	(*(volatile unsigned *)(timer_base + 0x18)) // Timer Unit Status Register (alias to T0_STATUS)
#define T1_CONFIG	(*(volatile unsigned *)(timer_base + 0x1C)) // Timer/Counter #1 Configuration Register
#define TSTAMP_DATA	(*(volatile unsigned *)(timer_base + 0x80)) // Timestamp Counter
#define WDT_RELOAD	(*(volatile unsigned *)(timer_base + 0x84)) // Watchdog Timer Reload Value
#define WDT_CTRL	(*(volatile unsigned *)(timer_base + 0x88)) // Watchdog Timer Control Register
#define WDT_KEY		(*(volatile unsigned *)(timer_base + 0x8C)) // Watchdog Timer Key Register

/* Interrupt Controller */
#define INTR_ST		(*(volatile unsigned *)(pic_base + 0x000)) // Interrupt Status Register
#define INTR_EN		(*(volatile unsigned *)(pic_base + 0x004)) // Interrupt Enable Register
#define INTR_SEL	(*(volatile unsigned *)(pic_base + 0x008)) // Interrupt Select Register
#define INTR_IRQ_ST	(*(volatile unsigned *)(pic_base + 0x00C)) // IRQ Status Register
#define INTR_FIQ_ST	(*(volatile unsigned *)(pic_base + 0x010)) // FIQ Status Register
#define INTR_PRTY	(*(volatile unsigned *)(pic_base + 0x014)) // Interrupt Priority Register
#define INTR_IRQ_ENC_ST	(*(volatile unsigned *)(pic_base + 0x018)) // IRQ Highest Priority Register
#define INTR_FIQ_ENC_ST	(*(volatile unsigned *)(pic_base + 0x01C)) // FIQ Highest Priority Register
#define IRQ8_STATUS	(*(volatile unsigned *)(pic_base + 0x020)) // Timers Status Register
#define IRQ8_CONFIG	(*(volatile unsigned *)(pic_base + 0x024)) // Timers IRQ Enable Register
#define		TSTAMP_INTEN	(1 << 2)
#define		TIMER1_INTEN	(1 << 1)
#define		TIMER0_INTEN	(1 << 0)

#define IRQ20_STATUS	(*(volatile unsigned *)(pic_base + 0x080)) // SmartCard Status Register
#define IRQ20_CONFIG	(*(volatile unsigned *)(pic_base + 0x084)) // SmartCard IRQ Enable Register
#define IRQ27_STATUS	(*(volatile unsigned *)(pic_base + 0x0B8)) // GPIO & I2C Status Register
#define IRQ27_CONFIG	(*(volatile unsigned *)(pic_base + 0x0BC)) // GPIO & I2C IRQ Enable Register
#define IRQ29_STATUS	(*(volatile unsigned *)(pic_base + 0x0C8)) // UART Status Register
#define IRQ29_CONFIG	(*(volatile unsigned *)(pic_base + 0x0CC)) // UART IRQ Enable Register
#define MISC_STATUS	(*(volatile unsigned *)(pic_base + 0x0D8)) // Misc Status Register
#define MISC_CONFIG	(*(volatile unsigned *)(pic_base + 0x0CC)) // Misc IRQ Enable Register

/* UART Register Descriptions */
#define U0_RBR_THR	(*(volatile unsigned *)(uart_base + 0x000)) // Receive Buffer register (read) and Transmit Holding register (write)
#define U0_IER		(*(volatile unsigned *)(uart_base + 0x004)) // Interrupt Enable register (read/write)
#define U0_IIR_FCR	(*(volatile unsigned *)(uart_base + 0x008)) // Interrupt ID register (read) and FIFO Control register (write)
#define U0_LCR		(*(volatile unsigned *)(uart_base + 0x00C)) // Line Control register (read/write)
#define U0_MCR		(*(volatile unsigned *)(uart_base + 0x010)) // Modem Control register (read/write)
#define U0_LSR		(*(volatile unsigned *)(uart_base + 0x014)) // Line Status register (read)
#define U0_MSR		(*(volatile unsigned *)(uart_base + 0x018)) // Modem Status register (read)
#define U0_SPR		(*(volatile unsigned *)(uart_base + 0x01C)) // Scratch Pad register (read/write)
#define U0_DLL		(*(volatile unsigned *)(uart_base + 0x000)) // Divisor Latch Reg. low byte (only when DLAB is high)
#define U0_DLH		(*(volatile unsigned *)(uart_base + 0x004)) // Divisor Latch Reg. high byte (only when DLAB is high)
#define U0_ISR		(*(volatile unsigned *)(uart_base + 0x020)) // Slow Infrared Select register (read/write)
#define U0_FOR		(*(volatile unsigned *)(uart_base + 0x024)) // FIFO Occupancy register (read)
#define U0_ABR		(*(volatile unsigned *)(uart_base + 0x028)) // Autobaud Control register (read/write)
#define U0_ACR		(*(volatile unsigned *)(uart_base + 0x02C)) // Autobaud Control register
#define U1_RBR_THR	(*(volatile unsigned *)(uart_base + 0x100)) // Receive Buffer register (read) and Transmit Holding register (write)
#define U1_IER		(*(volatile unsigned *)(uart_base + 0x104)) // Interrupt Enable register (read/write)
#define U1_IIR_FCR	(*(volatile unsigned *)(uart_base + 0x108)) // Interrupt ID register (read) and FIFO Control register (write)
#define U1_LCR		(*(volatile unsigned *)(uart_base + 0x10C)) // Line Control register (read/write)
#define U1_MCR		(*(volatile unsigned *)(uart_base + 0x110)) // Modem Control register (read/write)
#define U1_LSR		(*(volatile unsigned *)(uart_base + 0x114)) // Line Status register (read)
#define U1_MSR		(*(volatile unsigned *)(uart_base + 0x118)) // Modem Status register (read)
#define U1_SPR		(*(volatile unsigned *)(uart_base + 0x11C)) // Scratch Pad register (read/write)
#define U1_DLL		(*(volatile unsigned *)(uart_base + 0x100)) // Divisor Latch Reg. low byte (only when DLAB is high)
#define U1_DLH		(*(volatile unsigned *)(uart_base + 0x104)) // Divisor Latch Reg. high byte (only when DLAB is high)
#define U1_ISR		(*(volatile unsigned *)(uart_base + 0x120)) // Slow Infrared Select register (read/write)
#define U1_FOR		(*(volatile unsigned *)(uart_base + 0x124)) // FIFO Occupancy register (read)
#define U1_ABR		(*(volatile unsigned *)(uart_base + 0x128)) // Autobaud Control register (read/write)
#define U1_ACR		(*(volatile unsigned *)(uart_base + 0x12C)) // Autobaud Control register

#endif /* ! _PEXPERT_ARM_OLOCREEK_H */
