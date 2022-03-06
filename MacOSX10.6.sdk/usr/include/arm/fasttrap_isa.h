/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_FASTTRAP_ISA_H
#define	_FASTTRAP_ISA_H

/* #pragma ident	"@(#)fasttrap_isa.h	1.4	05/06/08 SMI" */

#include <sys/types.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef	uint32_t		fasttrap_instr_t;

typedef struct fasttrap_machtp {
        fasttrap_instr_t        ftmt_instr;     /* original instruction */

	uint8_t			ftmt_fntype;	/* One of the FASTTRAP_FN* constants defined below */
	/* Once the tracepoint is initialized, fntype will be FN_DONE_INIT and thumb will be 0 for ARM, 1 for Thumb */
	uint8_t			ftmt_thumb;

	uint8_t			ftmt_type;
} fasttrap_machtp_t;

#define ftt_instr	ftt_mtp.ftmt_instr
#define ftt_fntype	ftt_mtp.ftmt_fntype
#define ftt_thumb	ftt_mtp.ftmt_thumb
#define ftt_type	ftt_mtp.ftmt_type

#define FASTTRAP_T_INV 1
#define FASTTRAP_T_COMMON 2
#define FASTTRAP_T_BLX 3
#define FASTTRAP_T_B_COND 4
#define FASTTRAP_T_B 5
#define FASTTRAP_T_BX_REG 6
#define FASTTRAP_T_POP_PC 7
#define FASTTRAP_T_CPY_PC 9
#define FASTTRAP_T_MOV_PC_REG 10
#define FASTTRAP_T_LDM_PC 11
#define FASTTRAP_T_LDR_PC_IMMED 13

#define FASTTRAP_ARM_INSTR 0xe7ffdefc
#define FASTTRAP_THUMB_INSTR 0xdefc

#define FASTTRAP_ARM_RET_INSTR 0xe7ffdefb
#define FASTTRAP_THUMB_RET_INSTR 0xdefb

#define FASTTRAP_FN_DONE_INIT 255
#define FASTTRAP_FN_UNKNOWN 0
#define FASTTRAP_FN_ARM 1
#define FASTTRAP_FN_THUMB 2
#define FASTTRAP_FN_USDT 3

#define ARM_RM(x) ((x) & 0xF)
#define ARM_RS(x) (((x) >> 8) & 0xF)
#define ARM_RD(x) (((x) >> 12) & 0xF)
#define ARM_RN(x) (((x) >> 16) & 0xF)
#define ARM_CONDCODE(x) ((x) >> 28)

#define THUMB16_HRM(x) (((x) >> 3) & 0xF)
#define THUMB16_HRD(x) (((x) & 0x7) | ((((x) >> 4) & 0x8)))

#define THUMB32_RN(x,y) ((x) & 0xF)
#define THUMB32_RD(x,y) (((y) >> 8) & 0xF)

#define REG_SP 13
#define REG_LR 14
#define REG_PC 15

#define	FASTTRAP_AFRAMES		0
#define	FASTTRAP_RETURN_AFRAMES		0
#define	FASTTRAP_ENTRY_AFRAMES		0
#define	FASTTRAP_OFFSET_AFRAMES		0

#ifdef	__cplusplus
}
#endif

#endif	/* _FASTTRAP_ISA_H */
