/*
 * Copyright (c) 2005-2007 Apple Inc. All rights reserved.
 */

#ifndef _PEXPERT_ARM_S5I3000_H
#define _PEXPERT_ARM_S5I3000_H

#include <pexpert/arm/PL192_VIC.h>
#include <pexpert/arm/S3cUART.h>

#define ARM_BOARD_CONFIG_S5I3000

// TZIC
#define rTZICFIQSTATUS		(*(volatile unsigned *)(tzic_base + 0x000)) // TZIC FIQ Status Register
#define rTZICRAWINTR		(*(volatile unsigned *)(tzic_base + 0x004)) // TZIC Raw Interrupt Status Register
#define rTZICINTSELECT		(*(volatile unsigned *)(tzic_base + 0x008)) // TZIC Interrupt Select Register
#define rTZICFIQENABLE		(*(volatile unsigned *)(tzic_base + 0x00c)) // TZIC FIQ Enable Register
#define rTZICFIQBYPASS		(*(volatile unsigned *)(tzic_base + 0x014)) // TZIC FIQ Bypass Register
#define rTZICLock		(*(volatile unsigned *)(tzic_base + 0x01C)) // TZIC FIQ Bypass Register

#endif /* ! _PEXPERT_ARM_S5I3000_H */
