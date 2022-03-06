/*
 * Copyright (c) 2008 Apple Inc. All rights reserved.
 */

#ifndef _PEXPERT_ARM_S5L8920X_H
#define _PEXPERT_ARM_S5L8920X_H

#include <pexpert/arm/PL192_VIC.h>
#include <pexpert/arm/S3cUART.h>

#define rPMGR_TIME_LO	(*(volatile unsigned *)(timer_base + 0x200)) // Timebase Low
#define rPMGR_TIME_HI	(*(volatile unsigned *)(timer_base + 0x204)) // Timebase High
#define rPMGR_DECR0	(*(volatile unsigned *)(timer_base + 0x208)) // Decrementer0
#define rPMGR_DECR0_CTL (*(volatile unsigned *)(timer_base + 0x220)) // Decrementer0 Control

#endif /* ! _PEXPERT_ARM_S5L8920X_H */
