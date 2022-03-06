/*
 * Copyright (c) 2005-2007 Apple Inc. All rights reserved.
 */

#ifndef _PEXPERT_ARM_S5L8900X_H
#define _PEXPERT_ARM_S5L8900X_H

#include <pexpert/arm/PL192_VIC.h>
#include <pexpert/arm/S3cUART.h>

// Timer
#define rTACON		(*(volatile unsigned *)(timer_base + 0x000)) // Timer-A Control Regster
#define rTACMD		(*(volatile unsigned *)(timer_base + 0x004)) // Timer-A Command Regster
#define rTADATA0	(*(volatile unsigned *)(timer_base + 0x008)) // Timer-A Data0 Regster
#define rTADATA1	(*(volatile unsigned *)(timer_base + 0x00C)) // Timer-A Data1 Regster
#define rTAPRE		(*(volatile unsigned *)(timer_base + 0x010)) // Timer-A Prescale Regster
#define rTACNT		(*(volatile unsigned *)(timer_base + 0x014)) // Timer-A Counter Regster
#define rTBCON		(*(volatile unsigned *)(timer_base + 0x020)) // Timer-B Control Regster
#define rTBCMD		(*(volatile unsigned *)(timer_base + 0x024)) // Timer-B Command Regster
#define rTBDATA0	(*(volatile unsigned *)(timer_base + 0x028)) // Timer-B Data0 Regster
#define rTBDATA1	(*(volatile unsigned *)(timer_base + 0x02C)) // Timer-B Data1 Regster
#define rTBPRE		(*(volatile unsigned *)(timer_base + 0x030)) // Timer-B Prescale Regster
#define rTBCNT		(*(volatile unsigned *)(timer_base + 0x034)) // Timer-B Counter Regster
#define rTCCON		(*(volatile unsigned *)(timer_base + 0x040)) // Timer-C Control Regster
#define rTCCMD		(*(volatile unsigned *)(timer_base + 0x044)) // Timer-C Command Regster
#define rTCDATA0	(*(volatile unsigned *)(timer_base + 0x048)) // Timer-C Data0 Regster
#define rTCDATA1	(*(volatile unsigned *)(timer_base + 0x04C)) // Timer-C Data1 Regster
#define rTCPRE		(*(volatile unsigned *)(timer_base + 0x050)) // Timer-C Prescale Regster
#define rTCCNT		(*(volatile unsigned *)(timer_base + 0x054)) // Timer-C Counter Regster
#define rTDCON		(*(volatile unsigned *)(timer_base + 0x060)) // Timer-D Control Regster
#define rTDCMD		(*(volatile unsigned *)(timer_base + 0x064)) // Timer-D Command Regster
#define rTDDATA0	(*(volatile unsigned *)(timer_base + 0x068)) // Timer-D Data0 Regster
#define rTDDATA1	(*(volatile unsigned *)(timer_base + 0x06C)) // Timer-D Data1 Regster
#define rTDPRE		(*(volatile unsigned *)(timer_base + 0x070)) // Timer-D Prescale Regster
#define rTDCNT		(*(volatile unsigned *)(timer_base + 0x074)) // Timer-D Counter Regster
#define rTM64CNTH	(*(volatile unsigned *)(timer_base + 0x080)) // Timer-64 MSB Counter Regster
#define rTM64CNTL	(*(volatile unsigned *)(timer_base + 0x084)) // Timer-64 LSB Counter Regster
#define rTM64CON	(*(volatile unsigned *)(timer_base + 0x088)) // Timer-64 Control Regster
#define rTM64DATA0H	(*(volatile unsigned *)(timer_base + 0x08C)) // Timer-64 MSB Data0  Regster
#define rTM64DATA0L	(*(volatile unsigned *)(timer_base + 0x090)) // Timer-64 LSB Data0  Regster
#define rTM64DATA1H	(*(volatile unsigned *)(timer_base + 0x094)) // Timer-64 MSB Data1  Regster
#define rTM64DATA1L	(*(volatile unsigned *)(timer_base + 0x098)) // Timer-64 LSB Data1  Regster
#define rTECON		(*(volatile unsigned *)(timer_base + 0x0A0)) // Timer-E Control Regster
#define rTECMD		(*(volatile unsigned *)(timer_base + 0x0A4)) // Timer-E Command Regster
#define rTEDATA0	(*(volatile unsigned *)(timer_base + 0x0A8)) // Timer-E Data0 Regster
#define rTEDATA1	(*(volatile unsigned *)(timer_base + 0x0AC)) // Timer-E Data1 Regster
#define rTEPRE		(*(volatile unsigned *)(timer_base + 0x0B0)) // Timer-E Prescale Regster
#define rTECNT		(*(volatile unsigned *)(timer_base + 0x0B4)) // Timer-E Counter Regster
#define rTFCON		(*(volatile unsigned *)(timer_base + 0x0C0)) // Timer-F Control Regster
#define rTFCMD		(*(volatile unsigned *)(timer_base + 0x0C4)) // Timer-F Command Regster
#define rTFDATA0	(*(volatile unsigned *)(timer_base + 0x0C8)) // Timer-F Data0 Regster
#define rTFDATA1	(*(volatile unsigned *)(timer_base + 0x0CC)) // Timer-F Data1 Regster
#define rTFPRE		(*(volatile unsigned *)(timer_base + 0x0D0)) // Timer-F Prescale Regster
#define rTFCNT		(*(volatile unsigned *)(timer_base + 0x0D4)) // Timer-F Counter Regster
#define rTGCON		(*(volatile unsigned *)(timer_base + 0x0E0)) // Timer-G Control Regster
#define rTGCMD		(*(volatile unsigned *)(timer_base + 0x0E4)) // Timer-G Command Regster
#define rTGDATA0	(*(volatile unsigned *)(timer_base + 0x0E8)) // Timer-G Data0 Regster
#define rTGDATA1	(*(volatile unsigned *)(timer_base + 0x0EC)) // Timer-G Data1 Regster
#define rTGPRE		(*(volatile unsigned *)(timer_base + 0x0F0)) // Timer-G Prescale Regster
#define rTM32INT	(*(volatile unsigned *)(timer_base + 0x0F4)) // Timer-EFG Interrupt Status Regster

#endif /* ! _PEXPERT_ARM_S5I3000_H */
