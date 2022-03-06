/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */

/*
 * ARM CPU identification
 */

#ifndef _MACHINE_CPUID_H_
#define _MACHINE_CPUID_H_

#include <stdint.h>

typedef struct {
#ifdef __BIG_ENDIAN__
uint32_t	arm_implementor	: 8,	/* 24:31	implementor (0x41)  */
			arm_variant		: 4,	/* 20:23	variant			 */
			arm_arch		: 4,	/* 16:19	architecture		*/
			arm_part		: 12,	/* 04:15	primary part number */
			arm_rev			: 4;	/* 00:03	revision number	 */
#endif // __BIG_ENDIAN__
#ifdef __LITTLE_ENDIAN__
uint32_t	arm_rev			: 4,	/* 00:03	revision number	 */
			arm_part		: 12,	/* 04:15	primary part number */
			arm_arch		: 4,	/* 16:19	architecture		*/
			arm_variant		: 4,	/* 20:23	variant			 */
			arm_implementor	: 8;	/* 24:31	implementor (0x41)  */
#endif // __LITTLE_ENDIAN__
} arm_cpuid_bits_t;

typedef struct {
#ifdef __BIG_ENDIAN__
uint32_t	reserved		: 16,
			arm_thumb2		: 4,
			arm_jazelle		: 4,
			arm_thumb_ver	: 4,
			arm_32bit_isa	: 4;
#endif //__BIG_ENDIAN__
#ifdef __LITTLE_ENDIAN__
uint32_t	arm_32bit_isa	: 4,
			arm_thumb_ver	: 4,
			arm_jazelle		: 4,
			arm_thumb2		: 4,
			reserved		: 16;
#endif //__LITTLE_ENDIAN__
} arm_feature_bits_t;

typedef union {
	arm_feature_bits_t	field;
	uint32_t			value;
} arm_feature0_reg_t;

// Register 0, subtype 21: Instruction Set Features #1
typedef struct
{
#ifdef __BIG_ENDIAN__
    uint32_t jazelle_support        : 4;
    uint32_t interworking_support   : 4;
    uint32_t immediate_support      : 4;
    uint32_t if_then_support        : 4;
    uint32_t sign_zero_ext_support  : 4;
    uint32_t exception_2_support    : 4;
    uint32_t exception_1_support    : 4;
    uint32_t endianness_support     : 4;
#endif
#ifdef __LITTLE_ENDIAN__
    uint32_t endianness_support     : 4;
    uint32_t exception_1_support    : 4;
    uint32_t exception_2_support    : 4;
    uint32_t sign_zero_ext_support  : 4;
    uint32_t if_then_support        : 4;
    uint32_t immediate_support      : 4;
    uint32_t interworking_support   : 4;
    uint32_t jazelle_support        : 4;
#endif
}
syscp_ID_instructions_feat_1_reg;

typedef union {
	uint32_t value;
	syscp_ID_instructions_feat_1_reg field;
} arm_isa_feat1_reg;

/* XXX: ARM Todo: Review the next structure for usefulness */
/* This struct is pre ARM9xx. Do we need it? */
typedef struct {
#ifdef __BIG_ENDIAN__
uint32_t	arm_implementor	: 8,	/* 24:31	implementor */
			arm_v4t			: 1,	/* 23:23	1 if on ARMv4T, 0 if on ARMv3 */
			arm_variant		: 7,	/* 22:16	variant	*/
			arm_part		: 12,	/* 15:4		part number	*/
			arm_revision	: 4;	/* 3:0		revision number */
#endif // __BIG_ENDIAN__
#ifdef __LITTLE_ENDIAN__
uint32_t	arm_revision	: 4,	/* 3:0		revision number */
			arm_part		: 12,	/* 15:4		part number	*/
			arm_variant		: 7,	/* 22:16	variant	*/
			arm_v4t			: 1,	/* 23:23	1 if on ARMv4T, 0 if on ARMv3 */
			arm_implementor	: 8;	/* 24:31	implementor */
#endif // __LITTLE_ENDIAN__
} arm_old_cpu_info_t;


/* XXX: ARM Todo -- Review
 * We use this structure to identify if we are to use the arm_old_cpu_info_t or
 * the newer, arm_cpu_info_t structure.  Do we need it??
 * Then, we fill in the appropriate structure accordingly.
 */

#define ARMv4_ID_BITS(x)	(x == 0x7)
#define ARMv6_ID_BITS(x)	(x != 0x0 && x != 0x7) // cannot be 0x0 or 0x7 to be ARMv6

typedef struct {
#ifdef __BIG_ENDIAN__
	uint32_t			: 16,	/* don't care */
				id_bits	: 4,	/* if these bits are 0x7, 
								 * processor uses arm_old_cpu_info_t; */
								/* if they are 0x0, processor uses
								 * armv6_cpu_info_t; */
						: 12;	/* don't care */
#endif // __BIG_ENDIAN__
#ifdef __LITTLE_ENDIAN__
	uint32_t			: 12,	/* don't care */
				id_bits	: 4,	/* see above */
						: 16;	/* don't care */
#endif // __LITTLE_ENDIAN__
} arm_cpu_id_info_t;

typedef union {
	arm_cpuid_bits_t	arm_info;		/* ARM9xx,  ARM11xx, and later processors */
	uint32_t			value;
} arm_cpu_info_t;

/* Implementor codes */
#define CPU_VID_ARM		0x41	// ARM Limited
#define CPU_VID_DEC		0x44	// Digital Equipment Corporation
#define CPU_VID_MOTOROLA	0x4D	// Motorola - Freescale Semiconductor Inc. 
#define CPU_VID_MARVELL	0x56	// Marvell Semiconductor Inc.
#define CPU_VID_INTEL	0x69	// Intel ARM parts.


/* ARM Architecture Codes */

#define CPU_ARCH_ARMv4		0x1		/* ARMv4 */
#define CPU_ARCH_ARMv4T		0x2		/* ARMv4 + Thumb */
#define CPU_ARCH_ARMv5		0x3		/* ARMv5 */
#define CPU_ARCH_ARMv5T		0x4		/* ARMv5 + Thumb */
#define CPU_ARCH_ARMv5TE	0x5		/* ARMv5 + Thumb + Extensions(?) */
#define CPU_ARCH_ARMv5TEJ	0x6		/* ARMv5 + Thumb + Extensions(?) + //Jazelle(?) XXX */
#define CPU_ARCH_ARMv6		0x7		/* ARMv6 */
#define CPU_ARCH_ARMv7		0x8		/* ARMv7 */

/* special code indicating we need to look somewhere else for the architecture version */
#define CPU_ARCH_EXTENDED	0xF 

/* ARM Part Numbers */
/*
 * XXX: ARM Todo
 * Fill out these part numbers more completely
 */

/* ARM9 (ARMv4T architecture) */
#define CPU_PART_920T		0x920
#define CPU_PART_926EJS		0x926	/* ARM926EJ-S */

/* ARM11  (ARMv6 architecture) */
#define CPU_PART_1136JFS	0xB36	/* ARM1136JF-S or ARM1136J-S */
#define CPU_PART_1176JZFS	0xB76	/* ARM1176JZF-S */

/* H2 (ARMv7 architecture) */
#define CPU_PART_CORTEXA8	0xC08

/* Cache type identification */

/* Supported Cache Types */
typedef enum {
	CACHE_WRITE_THROUGH,
	CACHE_WRITE_BACK,
	CACHE_UNKNOWN
} cache_type_t;

typedef struct {
	boolean_t		c_unified;	/* unified I & D cache? */
	uint32_t		c_isize;	/* in Bytes (ARM caches can be 0.5 KB) */
	boolean_t		c_i_ppage;	/* protected page restriction for I cache 
								 * (see B6-11 in ARM DDI 0100I document). */
	uint32_t		c_dsize;	/* in Bytes (ARM caches can be 0.5 KB) */
	boolean_t		c_d_ppage;	/* protected page restriction for I cache 
								 * (see B6-11 in ARM DDI 0100I document). */
	cache_type_t	c_type;		/* WB or WT */
	uint32_t		c_linesz;	/* number of bytes */
	uint32_t		c_assoc;	/* n-way associativity */
} cache_info_t;

#ifdef __cplusplus
extern "C" {
#endif

extern void do_cpuid(void);
extern arm_cpu_info_t *cpuid_info(void);

extern void do_cacheid(void);
extern cache_info_t *cache_info(void);

#ifdef __cplusplus
}
#endif

#endif // _MACHINE_CPUID_H_
