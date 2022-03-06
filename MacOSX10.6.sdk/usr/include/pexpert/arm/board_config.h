/*
 * Copyright (c) 2005-2007 Apple Inc. All rights reserved.
 */
#ifndef _PEXPERT_ARM_BOARD_CONFIG_H
#define _PEXPERT_ARM_BOARD_CONFIG_H

#include <AppleSecureBootEpoch.h>


#ifdef ARM_BOARD_CONFIG_LN2410_920T
#define ARM920T	
#ifndef	ASSEMBLER
#include <pexpert/arm/S3c2410x.h>
#endif
#endif /* ARM_BOARD_CONFIG_LN2410_920T */

#ifdef ARM_BOARD_CONFIG_INTEGRATORCP_1136JFS
#define ARM1136JF_S
#ifndef	ASSEMBLER
#include <pexpert/arm/IntegratorCP.h>
#endif
#endif /* ARM_BOARD_CONFIG_INTEGRATORCP_1136JFS */

#ifdef ARM_BOARD_CONFIG_MX31ADS_1136JFS
#define ARM1136JF_S
#ifndef	ASSEMBLER
#include <pexpert/arm/MX31.h>
#endif
#endif  /* ARM_BOARD_CONFIG_MX31ADS_1136JFS */

#ifdef ARM_BOARD_CONFIG_S5I3000SMDK_1176JZFS
#define ARM1176JZF_S
#ifndef	ASSEMBLER
#include <pexpert/arm/S5I3000.h>
#endif
#define __ARM_RESTRICT_CACHE__ 1

#if __ARM_RESTRICT_CACHE__
#define __ARM_CACHE_SIZE__ 16384
#else
#define __ARM_CACHE_SIZE__ 32768
#endif

#endif  /* ARM_BOARD_CONFIG_S5I3000SMDK_1176JZFS */

#ifdef ARM_BOARD_CONFIG_OMAP3430SDP_A8
#define ARMA8
#ifndef	ASSEMBLER
#include <pexpert/arm/OMAP3430.h>
#endif
#define __ARM_CACHE_SIZE__ 16384

#endif  /* ARM_BOARD_CONFIG_OMAP3430_A8 */

#ifdef ARM_BOARD_CONFIG_S5L8900XFPGA_1136JFS
#define ARM1136JF_S
#ifndef	ASSEMBLER
#include <pexpert/arm/S5L8900X.h>
#endif
#endif  /* ARM_BOARD_CONFIG_S5L8900XFPGA_1136JFS */

#ifdef ARM_BOARD_CONFIG_S5L8720X
#define ARM1176JZF_S
#ifndef	ASSEMBLER
#include <pexpert/arm/S5L8900X.h>
#endif
#define ARM_BOARD_SECURITY_EPOCH __APPLE_SECURE_BOOT_EPOCH_S5L8720
#endif  /* ARM_BOARD_CONFIG_S5L8720X */

#ifdef ARM_BOARD_CONFIG_S5L8900X
#define ARM1176JZF_S
#include <pexpert/arm/S5L8900X.h>
#ifndef	ASSEMBLER
#endif
#define ARM_BOARD_SECURITY_EPOCH __APPLE_SECURE_BOOT_EPOCH_S5L8900
#define ARM_BOARD_CLASS_S5L8900X
#endif  /* ARM_BOARD_CONFIG_S5L8900X */

#ifdef ARM_BOARD_CONFIG_S5L8901X
#define ARM1176JZF_S
#include <pexpert/arm/S5L8900X.h>
#ifndef	ASSEMBLER
#endif
#define ARM_BOARD_SECURITY_EPOCH __APPLE_SECURE_BOOT_EPOCH_S5L8901
#define ARM_BOARD_CLASS_S5L8900X
#endif  /* ARM_BOARD_CONFIG_S5L8901X */

#ifdef ARM_BOARD_CONFIG_S5L8920X
#define ARMA8
#ifndef	ASSEMBLER
#include <pexpert/arm/S5L8920X.h>
#endif
#define __ARM_CACHE_SIZE__ 32768

#define ARM_BOARD_SECURITY_EPOCH __APPLE_SECURE_BOOT_EPOCH_S5L8920
#endif  /* ARM_BOARD_CONFIG_S5L8920X */

#ifdef ARM_BOARD_CONFIG_OLOCREEK
#define ARMXSCALE
#ifndef	ASSEMBLER
#include <pexpert/arm/olocreek.h>
#endif
#endif  /* ARM_BOARD_CONFIG_OLOCREEK */

#ifdef ARM_BOARD_CONFIG_MV88F5X81
#define ARM926EJ_S
#ifndef	ASSEMBLER
#include <pexpert/arm/MV88F5X81.h>
#endif
#endif  /* ARM_BOARD_CONFIG_MV88F5X81 */

#ifndef ARM_BOARD_SECURITY_EPOCH
#define ARM_BOARD_SECURITY_EPOCH 0
#endif

#endif /* ! _PEXPERT_ARM_BOARD_CONFIG_H */
