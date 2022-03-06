/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */
/* CMU_ENDHIST */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 */

/*
 * Processor registers for ARM
 */
#ifndef	_ARM_PROC_REG_H_
#define	_ARM_PROC_REG_H_

#include <pexpert/arm/board_config.h>

#if defined (ARM920T)
#define	__ARM_ARCH__	4
#define __ARM_VMSA__	4
#define __ARM_GCACHE__	0
#define __ARM_BCACHE__	0
#define __ARM_COHERENT_CACHE__ 0
#define __ARM_UNIFIED_TLB__ 0
#define __ARM_DEBUG__	0

#define	__ARM_VFP__	0

#elif defined (ARM926EJ_S)

#define	__ARM_ARCH__	5
#define __ARM_VMSA__	4
#define __ARM_GCACHE__	0
#define __ARM_BCACHE__	0
#define __ARM_COHERENT_CACHE__ 0
#define __ARM_UNIFIED_TLB__ 1
#define __ARM_DEBUG__	0

#define	__ARM_VFP__	0

#elif defined (ARM1136JF_S)

#define	__ARM_ARCH__	6
#define __ARM_VMSA__	6
#define __ARM_GCACHE__	0		/* use global cache flush instructions */
#define __ARM_BCACHE__	0		/* use block cache flush instructions */
#define	__ARM_VFP__	2
#define __ARM_COHERENT_CACHE__ 1
#define __ARM_UNIFIED_TLB__ 1
#define __ARM_DEBUG__	6

#elif defined (ARM1176JZF_S)

#define	__ARM_ARCH__	6
#define __ARM_VMSA__	6
#define __ARM_GCACHE__	0		/* use global cache flush instructions */
#define __ARM_BCACHE__	0		/* use block cache flush instructions */
#define	__ARM_VFP__	2
#define __ARM_COHERENT_CACHE__ 1
#define __ARM_UNIFIED_TLB__ 1
#define __ARM_DEBUG__	6

#elif defined (ARMXSCALE)
#define	__ARM_ARCH__	4
#define __ARM_VMSA__	4
#define __ARM_GCACHE__	0
#define __ARM_BCACHE__	0
#define	__ARM_VFP__	0
#define __ARM_COHERENT_CACHE__ 0
#define __ARM_UNIFIED_TLB__ 0
#define __ARM_DEBUG__	0

#elif defined (ARMA8)
#define	__ARM_ARCH__	7
#define __ARM_VMSA__	7
#define __ARM_GCACHE__	0		/* use global cache flush instructions */
#define __ARM_BCACHE__	0		/* use block cache flush instructions */
#define	__ARM_VFP__	3
#define __ARM_COHERENT_CACHE__ 1
#define __ARM_UNIFIED_TLB__ 1
#define __ARM_DEBUG__	7

#else
#error processor not supported
#endif

#if defined (ARM1136JF_S) || defined (ARM1176JZF_S)


/* 
 * Having anything other than 16KB of cache on arm11s
 * with otherwise coherent caches make it incoherent.
 */
#if defined(__ARM_CACHE_SIZE__) && __ARM_CACHE_SIZE__ != 16384
#undef __ARM_COHERENT_CACHE__
#define __ARM_COHERENT_CACHE__ 0
#endif

#endif

/*
 * Format of the Program Status Registers for ARM.
 *
 *  31 30 29 28 27     24     19   16      9  8  7  6  5  4   0
 * +-----------------------------------------------------------+
 * | N| Z| C| V| Q|...| J|...|GE[3:0]|...| E| A| I| F| T| MODE |
 * +-----------------------------------------------------------+
 */

/* 
 * Flags 
 */
#define PSR_NF		0x80000000	/* Negative/Less than */
#define PSR_ZF		0x40000000	/* Zero */
#define PSR_CF		0x20000000	/* Carry/Borrow/Extend */
#define PSR_VF		0x10000000	/* Overflow */
#define PSR_QF		0x08000000	/* saturation flag (QADD ARMv5) */

/*
 * Modified execution mode flags
 */
#define PSR_JF		0x01000000	/* Jazelle flag (BXJ ARMv5) */
#define PSR_EF		0x00000200	/* mixed-endian flag (SETEND ARMv6) */
#define PSR_AF		0x00000100	/* precise abort flag (ARMv6) */
#define PSR_TF		0x00000020	/* thumb flag (BX ARMv4T) */

/*
 * Interrupts
 */
#define PSR_IRQFb		 7	/* IRQ : 0 = IRQ enable */
#define PSR_IRQF	0x00000080	/* IRQ : 0 = IRQ enable */
#define PSR_FIQF	0x00000040	/* FIQ : 0 = FIQ enable */

/*
 * CPU mode
 */
#define PSR_USER_MODE 	0x00000010	/* User mode */
#define PSR_FIQ_MODE 	0x00000011 	/* FIQ mode */
#define PSR_IRQ_MODE	0x00000012	/* IRQ mode */
#define PSR_SVC_MODE	0x00000013 	/* Supervisor mode */
#define PSR_ABT_MODE	0x00000017	/* Abort mode */
#define PSR_UND_MODE	0x0000001B	/* Undefined mode */

#define PSR_MODE_MASK	0x0000001F

#define PSR_USERDFLT 	PSR_USER_MODE
#define PSR_USER_MASK 	(PSR_AF | PSR_IRQF | PSR_FIQF | PSR_MODE_MASK)
#define PSR_USER_SET	PSR_USER_MODE

#define PSR_INTMASK 	PSR_IRQF	/* Interrupt disable */

/*
 * Format of the FPEXC register
 */
#define	FPEXC_EX	0x80000000	/* Exception status */
#define	FPEXC_EX_BIT	31
#define	FPEXC_EN	0x40000000	/* VFP : 1 = EN enable */
#define	FPEXC_EN_BIT	30

/*
 * Format of the FPSCR register
 */
#define	FPSCR_DN	0x02000000	/* Default NaN */
#define	FPSCR_FZ	0x01000000	/* Flush to zero */


/*
 * FSR registers 
 */
#define	FSR_ALIGN		0x00000001	/* Alignment */
#define	FSR_DEBUG		0x00000002	/* Debug (watch/break) */
#define	FSR_SFAULT		0x00000005	/* Translation Section */
#define	FSR_PFAULT		0x00000007	/* Translation Page */
#define	FSR_SDOM		0x00000009	/* Domain Section */
#define	FSR_PDOM		0x0000000B	/* Domain Page */
#define	FSR_SPERM		0x0000000D	/* Permission Section */
#define	FSR_PPERM		0x0000000F	/* Permission Page */

#define	FSR_MASK		0x0000040F	/* Valid bits */
#define	FSR_ALIGN_MASK		0x0000040D	/* Valid bits to check align */

#if (__ARM_VMSA__ >= 6)
#define	DFSR_WRITE		0x00000800	/* write data abort fault */
#endif

#if defined (ARM920T)
#define TEST_FSR_VMFAULT(status)	(((status) == FSR_PFAULT)	\
					|| ((status) == FSR_PPERM)	\
					|| ((status) == FSR_SFAULT)	\
					|| ((status) == FSR_SPERM))

#elif defined (ARM926EJ_S)
#define TEST_FSR_VMFAULT(status)	(((status) == FSR_PFAULT)	\
                                     || ((status) == FSR_PPERM)	\
                                     || ((status) == FSR_SFAULT)	\
                                     || ((status) == FSR_SPERM))

#elif defined (ARM1136JF_S) || defined (ARM1176JZF_S)

#define	FSR_PREC_EXT		0x00000008	/* Precise External Abort */
#define	FSR_IMPREC_EXT		0x00000406	/* Imprecise External Abort */
#define	FSR_CACHE_MAINT		0x00000404	/* Cache Maintenance Operation fault */

#define TEST_FSR_VMFAULT(status)	(((status) == FSR_PFAULT)	\
					|| ((status) == FSR_PPERM)	\
					|| ((status) == FSR_SFAULT)	\
					|| ((status) == FSR_SPERM))

#elif defined (ARMA8)

#define	FSR_PREC_EXT		0x00000008	/* Precise External Abort */
#define	FSR_IMPREC_EXT		0x00000406	/* Imprecise External Abort */
#define	FSR_CACHE_MAINT		0x00000404	/* Cache Maintenance Operation fault */

#define TEST_FSR_VMFAULT(status)	(((status) == FSR_PFAULT)	\
					|| ((status) == FSR_PPERM)	\
					|| ((status) == FSR_SFAULT)	\
					|| ((status) == FSR_SPERM))

#elif defined (ARMXSCALE)

#define	FSR_LOCK_DABT		0x00000404	/* Lock Abort */
#define	FSR_COPROC_DABT		0x0000040C	/* Co-processor Data Abort */
#define	FSR_IMPREC_DABT		0x0000040C	/* Imprecise External Data Abort */
#define	FSR_DCACHE_PARITY	0x00000408	/* Imprecise External Data Abort */
#define	FSR_INST_MMU_EXCP	0x00000400	/* Intruction MMU Excetpion */
#define	FSR_INST_EXT_EXCP	0x00000406	/* External Intruction Excetpion */
#define	FSR_ICACHE_PARITY	0x00000408

#define TEST_FSR_VMFAULT(status)	(((status) == FSR_INST_MMU_EXCP) \
					|| ((status) == FSR_PFAULT)	\
					|| ((status) == FSR_PPERM)	\
					|| ((status) == FSR_SFAULT)	\
					|| ((status) == FSR_SPERM))
#else

#error Incompatible CPU type configured

#endif



#define MMU_ENABLE	0x00000001	/* enable the MMU */
#define MMU_ALIGN	0x00000002	/* enable alignment aborts */
#define MMU_DCACHE	0x00000004	/* the data cache */
#define MMU_WBUFFER	0x00000008	/* write-back buffering (ARMv6: always on) */
#define	MMU_BIGENDIAN	0x00000080	/* big-endian */
#define MMU_SYSTEM	0x00000100	/* "system" mode */
#define MMU_ROM		0x00000200	/* "rom" mode */
#define MMU_PREDIC	0x00000800	/* program flow prediction (ARMv6) */
#define MMU_ICACHE	0x00001000	/* the instruction cache */
#define MMU_HIGHVEC	0x00002000	/* vector table at 0xffff0000 */
#define MMU_RROBIN	0x00004000	/* round-robin replacement */
#define MMU_DGLOBALTCM	0x00010000	/* global data tcm (or block tcm ARMv6) */
#define MMU_IGLOBALTCM	0x00040000	/* global inst tcm (or block tcm ARMv6) */
#define MMU_UNALIGN	0x00400000	/* Allow unaligned accesses (ARMv6) */
#define MMU_XP		0x00800000	/* Extended pte mode (ARMv6) */
#define MMU_TRE		0x10000000	/* TEX remap enable (ARMv6) */
#define MMU_AFE		0x20000000	/* Access flag enable (ARMv6) */
#define MMU_NOFASTBUS	0x40000000	/* notFastBus select */
#define MMU_ASYNCCLOCK	0x80000000	/* asynchronous clock select */


#if defined (ARM920T)

#define ARM_MMU_DEFAULT (MMU_ENABLE|MMU_ALIGN|MMU_DCACHE|MMU_WBUFFER|MMU_ICACHE|MMU_HIGHVEC)

/*
 * XXX - TODO: Use the Cache type register c0 for these at runtime
 *
 *	ARM920T MMU Cache manipulation register format
 *	31      25                 7 5 4  2  0
 *	+------+------------------+---+-----+
 *	| way  |000000000000000000|set|00000|
 *	+------+------------------+---+-----+
 */
#define MMU_CSIZE	14		/* cache size as 1<<MMU_CSIZE (16K) */
#define MMU_CLINE	5		/* cache line size as 1<<MMU_CLINE (32) */
#define MMU_NWAY	6		/* set associativity 1<<MMU_NWAY (64) */
#define MMU_I7SET	5		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define MMU_I7WAY	26		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define MMU_I9WAY	26		/* cp15 c9 way incrementer 1<<MMU_I9WAY */

#define MMU_SWAY	(MMU_CSIZE - MMU_NWAY)	/* set size 1<<MMU_SWAY */
#define MMU_NSET	(MMU_SWAY - MMU_CLINE)	/* lines per way 1<<MMU_NSET */

#elif defined (FEROCEON_1850)

#define ARM_MMU_DEFAULT (MMU_ENABLE|MMU_ALIGN|MMU_DCACHE|MMU_WBUFFER|MMU_ICACHE|MMU_HIGHVEC)

/*
 * XXX - TODO: Use the Cache type register c0 for these at runtime
 *
 *	ARM926EJ-S MMU Cache manipulation register format
 *	31 30               14 13    5 4  2  0
 *	+---+-----------------+-------+-----+
 *	|way|00000000000000000|  set  |00000|
 *	+---+-----------------+-------+-----+
 */
#define MMU_CSIZE	15		/* cache size as 1<<MMU_CSIZE (32K) */
#define MMU_CLINE	5		/* cache line size as 1<<MMU_CLINE (32) */
#define MMU_NWAY	0		/* set associativity 1<<MMU_NWAY (64) */
#define MMU_I7SET	4		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define MMU_I7WAY	30		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define MMU_I9WAY	30		/* cp15 c9 way incrementer 1<<MMU_I9WAY */

#define MMU_SWAY	(MMU_CSIZE - MMU_NWAY)	/* set size 1<<MMU_SWAY */
#define MMU_NSET	(MMU_SWAY - MMU_CLINE)	/* lines per way 1<<MMU_NSET */

#elif defined (FEROCEON_2850)

#define ARM_MMU_DEFAULT (MMU_ENABLE|MMU_ALIGN|MMU_DCACHE|MMU_WBUFFER|MMU_ICACHE|MMU_HIGHVEC)

/*
 * XXX - TODO: Use the Cache type register c0 for these at runtime
 *
 *	ARM926EJ-S MMU Cache manipulation register format
 *	31 30               14 13    5 4  2  0
 *	+---+-----------------+-------+-----+
 *	|way|00000000000000000|  set  |00000|
 *	+---+-----------------+-------+-----+
 */ 
#define MMU_CSIZE	15		/* cache size as 1<<MMU_CSIZE (32K) */
#define MMU_CLINE	5		/* cache line size as 1<<MMU_CLINE (32) */
#define MMU_NWAY	2		/* set associativity 1<<MMU_NWAY (64) */
#define MMU_I7SET	5		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define MMU_I7WAY	30		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define MMU_I9WAY	30		/* cp15 c9 way incrementer 1<<MMU_I9WAY */

#define MMU_SWAY	(MMU_CSIZE - MMU_NWAY)	/* set size 1<<MMU_SWAY */
#define MMU_NSET	(MMU_SWAY - MMU_CLINE)	/* lines per way 1<<MMU_NSET */

#elif defined (ARM1136JF_S) || defined (ARM1176JZF_S)

#define ARM_MMU_DEFAULT (MMU_ENABLE|MMU_DCACHE|MMU_WBUFFER|MMU_PREDIC|MMU_ICACHE|MMU_HIGHVEC|MMU_UNALIGN|MMU_XP|MMU_DGLOBALTCM|MMU_IGLOBALTCM)

/*
 * XXX - TODO: Use the Cache type register c0 for these at runtime
 *
 *	ARM1136JF_S MMU Cache manipulation register format
 *	31 30               14 13    5 4  2  0
 *	+---+-----------------+-------+-----+
 *	|way|00000000000000000|  set  |00000|
 *	+---+-----------------+-------+-----+
 */
#if __ARM_CACHE_SIZE__ == 32768
#define MMU_CSIZE	15		/* cache size as 1<<MMU_CSIZE (32K) */
#else
#define MMU_CSIZE	14		/* cache size as 1<<MMU_CSIZE (16K) */
#endif
#define MMU_CLINE	5		/* cache line size as 1<<MMU_CLINE (32) */
#define MMU_NWAY	2		/* set associativity 1<<MMU_NWAY (4) */
#define MMU_I7SET	5		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define MMU_I7WAY	30		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define MMU_I9WAY	30		/* cp15 c9 way incrementer 1<<MMU_I9WAY */

#define MMU_SWAY	(MMU_CSIZE - MMU_NWAY)	/* set size 1<<MMU_SWAY */
#define MMU_NSET	(MMU_SWAY - MMU_CLINE)	/* lines per way 1<<MMU_NSET */

#elif defined (ARMA8)

#define ARM_MMU_DEFAULT (MMU_ENABLE|MMU_DCACHE|MMU_WBUFFER|MMU_PREDIC|MMU_ICACHE|MMU_HIGHVEC|MMU_UNALIGN|MMU_XP|MMU_DGLOBALTCM|MMU_IGLOBALTCM)

#if __ARM_CACHE_SIZE__ == 32768
#define MMU_CSIZE	15		/* cache size as 1<<MMU_CSIZE (32K) */
#else
#define MMU_CSIZE	14		/* cache size as 1<<MMU_CSIZE (16K) */
#endif
#define MMU_CLINE	6		/* cache line size as 1<<MMU_CLINE (64) */
#define MMU_NWAY	2		/* set associativity 1<<MMU_NWAY (4) */
#define MMU_I7SET	6		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define MMU_I7WAY	30		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define MMU_I9WAY	30		/* cp15 c9 way incrementer 1<<MMU_I9WAY */

#define MMU_SWAY	(MMU_CSIZE - MMU_NWAY)	/* set size 1<<MMU_SWAY */
#define MMU_NSET	(MMU_SWAY - MMU_CLINE)	/* lines per way 1<<MMU_NSET */

#define __ARM_L2CACHE__	1

#define L2_CSIZE	18		/* cache size as 1<<MMU_CSIZE (256) */
#define L2_CLINE	6		/* cache line size as 1<<MMU_CLINE (64) */
#define L2_NWAY		3		/* set associativity 1<<MMU_NWAY (8) */
#define L2_I7SET	6		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define L2_I7WAY	29		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define L2_I9WAY	29		/* cp15 c9 way incrementer 1<<MMU_I9WAY */


#define L2_SWAY	(L2_CSIZE - L2_NWAY)	/* set size 1<<MMU_SWAY */
#define L2_NSET	(L2_SWAY - L2_CLINE)	/* lines per way 1<<MMU_NSET */

#elif defined (ARMXSCALE)

#define ARM_MMU_DEFAULT (MMU_ENABLE|MMU_ALIGN|MMU_DCACHE|MMU_WBUFFER|MMU_ICACHE|MMU_HIGHVEC)

/*
 *	ARMXSCALE MMU Cache manipulation register format
 *	31 30 29            13 12    5 4    0
 *	+---+-----------------+-------+-----+
 *	|way|00000000000000000|  set  |00000|
 *	+---+-----------------+-------+-----+
 */
#define MMU_CSIZE	15		/* cache size as 1<<MMU_CSIZE (32K) */
#define MMU_CLINE	5		/* cache line size as 1<<MMU_CLINE (32) */
#define MMU_NWAY	2		/* set associativity 1<<MMU_NWAY (4) */
#define MMU_I7SET	5		/* cp15 c7 set incrementer 1<<MMU_I7SET */
#define MMU_I7WAY	30		/* cp15 c7 way incrementer 1<<MMU_I7WAY */
#define MMU_I9WAY	30		/* cp15 c9 way incrementer 1<<MMU_I9WAY */

#define MMU_SWAY	(MMU_CSIZE - MMU_NWAY)	/* set size 1<<MMU_SWAY */
#define MMU_NSET	(MMU_SWAY - MMU_CLINE)	/* lines per way 1<<MMU_NSET */

#else
#error processor not supported
#endif

/*
 * Translation Table Base register (CP15 c2 c0 0==TTB0 1==TTB1) format.
 *
 *	31                   14 13   5 4 3 2 1 0
 *	+----------------------+------+---+-+-+-+
 *	|translation table base| zero |RGN|P|S|C|
 *	+----------------------+------+---+-+-+-+
 *
 * The RGN, S, and C bits control cacheability of table walks at
 * various cache levels.  (These are all ARMv6 additions)
 *
 * There are two translation table base registers for ARMv6.  The
 * translation table base control register specifies how the processor
 * should decide to use one or the other.
 *
 * NOTE: ARM1136JF_S cannot page table walk in L1 cache.  So, write
 * through is required for the page tables, or explicit cleans are
 * required.
 */
#define MMU_TTB_CACHED	        0x00000001	/* cache in inner cache */
#define MMU_TTB_SHARED		0x00000002	/* shared with other cpu */
#define MMU_TTB_ECC		0x00000004	/* enable ECC memory */
#define MMU_TTB_RGN_DISBALED	0x00000000	/* no outer cachability */
#define MMU_TTB_RGN_WRITEBACK	0x00000008	/* write back and allocate */
#define MMU_TTB_RGN_WRITETHRU	0x00000010	/* write thru outer cache */
#define MMU_TTB_RGN_WRITEBACKNO	0x00000018	/* write back no allocate */

/*
 * Translation Table Base Control register (CP15 c2 c0 2) format.
 *
 *	31    3 2 0 
 *	+----------+
 *	| zero | N |
 *	+----------+
 *
 * If N=0, always use translation table base register 0.  Otherwise, if
 * bits [31:32-N] of the address are all zero use base register 0.  Otherwise,
 * use base register 1.
 *
 * Reading from this register also returns the page table boundary for TTB0.
 * Writing to it updates the boundary for TTB0. (0=16KB, 1=8KB, 2=4KB, etc...)
 *
 * ARMv6todo: Switch to using 1GB user address space in TTB0 - with a 4KB aligned
 *	translation table to avoid having to get 16KB aligned physical for 
 *	each translation table.
 */
#define MMU_TTBC_N	2	/* 1 GB TTB0, 3GB TTB1 */

/*
 * Domain access control register (CP15 c3 c0 0)
 * Each of the 16 domains gets one of these values set in that control register.  So,
 * different tasks can have different access without having to
 * change TTE/PTE AP values (just change the register).
 *
 * For now, we just use a single domain, set to DOM_CLIENT,
 *  and use the AP bits.
 */

#define DAC_FAULT	0x0	/* invalid domain - everyone loses */
#define DAC_CLIENT	0x1	/* client domain - use AP bits */
#define DAC_RESERVE	0x2	/* reserved domain - undefined */
#define DAC_MANAGER	0x3	/* manager domain - all access */
#define DAC_SET(dom, x) ((x)<<((dom)<<1))

/*
 * Fault status and address registers
 *
 * Data fault status register (CP15 c5 c0 0)
 *
 * ARMv6todo: use the RW bit in the fault status register to determine the
 * type of access (read or write).
 *
 * Instruction fault status register (CP15 c5 c0 1) (ARMv6)
 *
 * Data fault address register (CP15 c6 c0 0)
 * Watchpoint fault address register (CP15 c6 c0 1) (ARMv6)
 */

/*
 * Cache operations register (CP15 c7 c0 0)
 *
 * ARMv6todo: Apply "Flush Prefetch Buffer" in appropriate places
 * ARMv6todo: Use CP15 c7 block transfer operations where appropriate
 */

/*
 * TLB Operations Register (CP15 c8 c0 0)
 *
 *	31                       10 9 8 7            0
 *	+--------------------------+---+--------------+
 *	| modified virtual address |SBZ| ASID (ARMv6) |
 *	+--------------------------+---+--------------+
 *
 * ARMv6todo: add "Invalidate on ASID match" usage as appropriate
 * to flush only a given address space from the TLB.
 */
#define TLB_INVALIDATE		0	/* Invalidate whole TLB opcode */
#define TLB_INVALIDATE_ENTRY	1	/* Invalidate single (matching) entry */
#define TLB_INVALIDATE_ASID	2	/* Invalidate entire ASID entries */

/*
 *	ARM Two-level Page Table support
 */

/*
 *	Translation table
 *
 *	Each translation table is 16KB in size, must be physically
 *	contiguous and must be aligned on a 16KB boundary. Each of
 *	the 4096 32-bit entries describes 1MB of address space.
 */
#define TTE_SIZE	0x100000	/* size of area covered by a tte */
#define TTE_OFFMASK	0x0fffff	/* offset within TTE area */
#define TTESHIFT	20		/* page descriptor shift */
#define TTEMASK		0xfff00000	/* mask for page descriptor index */

/*
 * Cache and buffer control (common for TTEs and PTEs)
 */
#if (__ARM_VMSA__ >= 6)
#define CACHE_CB_DISABLE	 0x0	/* no cache, no buffer */
#define CACHE_TEX_DISABLE	 0x0	/* no cache, no buffer */
#define CACHE_CB_WRITECOMB	 0x0	/* no cache, buffered writes */
#define CACHE_TEX_WRITECOMB	 0x1	/* no cache, buffered writes */
#define CACHE_CB_WRITETHRU	 0x2	/* cache enabled, buffer disabled */
#define CACHE_TEX_WRITETHRU	 0x0	/* cache enabled, buffer disabled */
#define CACHE_CB_WRITEBACK	 0x3	/* cache enabled, buffer enabled */
#define CACHE_TEX_WRITEBACK	 0x0	/* cache enabled, buffer enabled */
#else
#define CACHE_CB_DISABLE	 0x0	/* no cache, no buffer */
#define CACHE_TEX_DISABLE	 0x0	/* set to zero */
#define CACHE_CB_WRITECOMB	 0x1	/* no cache, buffered writes */
#define CACHE_TEX_WRITECOMB	 0x0	/* set to zero */
#define CACHE_CB_WRITETHRU	 0x2	/* cache enabled, buffer disabled */
#define CACHE_TEX_WRITETHRU	 0x0	/* set to zero */
#define CACHE_CB_WRITEBACK	 0x3	/* cache enabled, buffer enabled */
#define CACHE_TEX_WRITEBACK	 0x0	/* set to zero */
#endif

/*
 * Access protection bit values (TTEs and PTEs)
 */
#define AP_NANA		0x0	/* no access (priv or user) */
#define AP_RWNA		0x1	/* priv=read/write, user=no access */
#define AP_RWRO		0x2	/* priv=read/write, user=read-only */
#define AP_RWRW		0x3	/* priv=read/write, user=read/write */
#define AP_MASK		0x3	/* mask to find ap bits */

#if (__ARM_VMSA__ >= 6)
#define APX_RW		0x0	/* keeps priv access at read/write */
#define APX_RO		0x1	/* priv access read-only (ARMv6) */
#else
#define APX_RW		0x0	/* keeps priv access at read/write */
#define APX_RO		APX_RW	/* keeps priv access at read/write */
#endif

/*
 *	Translation Table Entries
 *
 *	The translation table (L1 table) contains entries describing
 *	L2 page tables or entries directly translating 1MB pages.
 *	Entry types as follows:
 *
 *	fault entry
 *	31                            2  0
 *	+------------------------------+--+
 *	|    ignored                   |00|
 *	+------------------------------+--+
 *
 *	coarse page table entry
 *	31                   10 9 8  5  4  2  0
 *	+----------------------+-+----+--+--+--+
 *	| page table base addr |P|dom |XN|00|01|
 *	+----------------------+-+----+--+--+--+
 *
 *	direct (1MB) section entry
 *	31         20 18    15  12 10 9 8  5  4  2  0
 *	+------------+--+-+-+-+---+--+-+----+--+--+--+
 *	| base addr  |00|G|S|A|TEX|AP|P|dom |XN|CB|10|
 *	+------------+--+-+-+-+---+--+-+----+--+--+--+
 *
 *      super (16MB) section entry
 *	31      24 23  18    15  12 10 9 8  5  4  2  0
 *	+---------+------+-+-+-+---+--+-+----+--+--+--+
 *	|base addr|000001|G|S|A|TEX|AP|P|dom |XN|CB|10|
 *	+---------+------+-+-+-+---+--+-+----+--+--+--+
 *
 *	fine page table entry (ARMv4 only)
 *	31                 12   9 8  5 4  2  0
 *	+--------------------+---+----+-+--+--+
 *	| page table base    |000|dom |1|00|11|
 *	+--------------------+---+----+-+--+--+
 *
 * where:
 *	'G' is the notGlobal (process-specific) bit (ARMv6)
 *	'S' is the shared bit (ARMv6)
 *	'A' in the access permission extension (APX) bit (ARMv6) 
 *	'TEX' remap register control bits
 *	'AP' is the access protection
 *	'P' indicates ECC enabled region
 *	'dom' is the domain for the translation
 *	'XN' is the eXecute Never bit (ARMv6) 
 *	'CB' is the cache/buffer attribute 
 */
#define TTE_TYPE_FAULT	 0x00000000	/* fault entry type */
#define TTE_TYPE_COARSE	 0x00000001	/* course page table type */
#define TTE_TYPE_SECTION 0x00000002	/* (direct) section entry type */
#define TTE_TYPE_FINE	 0x00000003	/* fine page table type */
#define TTE_TYPE_MASK	 0x00000003	/* mask for extracting the type */

#define TTE_SUPER	 0x00040000	/* make section a supersection (16MB) ARMv6 */

#if (__ARM_VMSA__ >= 6)
#define TTE_EXECUTE	 0x00000000	/* section is executable */
#define TTE_NOEXECUTE	 0x00000010	/* section is NOT executable */
#else
#define TTE_EXECUTE	 0x00000010	/* can't control - always executable - must be 1 */
#define TTE_NOEXECUTE	 0x00000010	/* can't control - always executable - must be 1 */
#endif
#define TTE_EXECUTE_MASK 0x00000010	/* mask for extracting the (no)execute bit */

#define TTE_SUPER_MASK	 0xFF000000	/* mask for a super section entry */
#define TTE_SECTION_MASK 0xFFF00000	/* mask for a section entry */
#define TTE_COARSE_MASK	 0xFFFFFC00	/* mask for a coarse page table entry */
#define TTE_FINE_MASK	 0xFFFFF000	/* mask for a fine page table entry */

#define PTE_COARSE_SHIFT 12		/* shift to get course pt index */
#define PTE_COARSE_IMASK 0x000000FF	/* index mask for a shifted pt index */

#define PTE_FINE_SHIFT	 10		/* shift to get course pt index */
#define PTE_FINE_IMASK	 0x000003FF	/* index mask for a fine page table */

#define TTE_SECTION_APSHIFT 10
#define TTE_SECTION_AP(x) ((x)<<TTE_SECTION_APSHIFT) /* single access protection */

#define TTE_SECTION_APXSHIFT 15
#if (__ARM_VMSA__ >= 6)
#define TTE_SECTION_APX(x) ((x)<<TTE_SECTION_APXSHIFT) /* priv=read/only modifier */
#define TTE_SECTION_APX_MASK (1<<TTE_SECTION_APXSHIFT) /* mask for extraction */
#else
#define TTE_SECTION_APX(x) (0)
#define TTE_SECTION_APX_MASK (0)
#endif


#if (__ARM_VMSA__ >= 6)
#define ARM_TTE_TEX(x)		((x) << 12)
#define	ARM_TTE_TEX_MASK	(7<<12)
#define ARM_TTE_CB(x)		((x) << 2)
#define	ARM_TTE_CB_MASK		(3<<2)

#define TTE_CACHE_DISABLE	(ARM_TTE_TEX(CACHE_TEX_DISABLE) | ARM_TTE_CB(CACHE_CB_DISABLE))
#define TTE_CACHE_WRITECOMB	(ARM_TTE_TEX(CACHE_TEX_WRITECOMB) | ARM_TTE_CB(CACHE_CB_WRITECOMB))
#define TTE_CACHE_WRITETHRU	(ARM_TTE_TEX(CACHE_TEX_WRITETHRU) | ARM_TTE_CB(CACHE_CB_WRITETHRU))
#define TTE_CACHE_WRITEBACK	(ARM_TTE_TEX(CACHE_TEX_WRITEBACK) | ARM_TTE_CB(CACHE_CB_WRITEBACK))

#else
#define ARM_TTE_TEX(x)		((x) << 12)
#define	ARM_TTE_TEX_MASK	(7<<12)
#define ARM_TTE_CB(x)		((x) << 2)
#define	ARM_TTE_CB_MASK		(3<<2)

#define TTE_CACHE_DISABLE	(ARM_TTE_TEX(CACHE_TEX_DISABLE) | ARM_TTE_CB(CACHE_CB_DISABLE))
#define TTE_CACHE_WRITECOMB	(ARM_TTE_TEX(CACHE_TEX_WRITECOMB) | ARM_TTE_CB(CACHE_CB_WRITECOMB))
#define TTE_CACHE_WRITETHRU	(ARM_TTE_TEX(CACHE_TEX_WRITETHRU) | ARM_TTE_CB(CACHE_CB_WRITETHRU))
#define TTE_CACHE_WRITEBACK	(ARM_TTE_TEX(CACHE_TEX_WRITEBACK) | ARM_TTE_CB(CACHE_CB_WRITEBACK))

#endif

#define TTE_CACHE_DEFAULT	TTE_CACHE_WRITEBACK
#define TTE_CACHE_MASK		(ARM_TTE_TEX_MASK | ARM_TTE_CB_MASK)


/*
 * Page table entries
 *
 * The following page table entry types are possible:
 *
 *	fault page entry
 *	31                            2  0
 *	+------------------------------+--+
 *	|    ignored                   |00|
 *	+------------------------------+--+
 *
 *	large (64KB) page entry (ARMv6)
 *	31             16 15  12     9   6  4 3 2  0
 *	+----------------+--+---+-+-+-+---+--+-+-+--+
 *	| base phys addr |XN|TEX|G|S|A|000|AP|C|B|01|
 *	+----------------+--+---+-+-+-+---+--+-+-+--+
 *
 *	large (64KB) page entry (ARMv4)
 *	31             16   12 10  8  6  4 3 2  0
 *	+----------------+----+--+--+--+--+-+-+--+
 *	| base phys addr |0000|AP|AP|AP|AP|C|B|01|
 *	+----------------+----+--+--+--+--+-+-+--+
 *
 *	small (4KB) page entry (ARMv6)
 *	31                 12     9   6  4 3 2 1  0
 *	+--------------------+-+-+-+---+--+-+-+-+--+
 *	| base phys addr     |G|S|A|TEX|AP|C|B|1|XN|
 *	+--------------------+-+-+-+---+--+-+-+-+--+
 *
 *	small (4KB) page entry (ARMv4)
 *	31                 12 10  8  6  4 3 2  0
 *	+--------------------+--+--+--+--+-+-+--+
 *	| base phys addr     |AP|AP|AP|AP|C|B|10|
 *	+--------------------+--+--+--+--+-+-+--+
 *
 *	tiny (1KB) page entry (ARMv4 only)
 *	31                   10    6  4 3 2  0
 *	+----------------------+----+--+-+-+--+
 *	| base physical addr   |0000|AP|C|B|11|
 *	+----------------------+----+--+-+-+--+
 *
 * also where:
 *	'XN' is the eXecute Never bit
 *	'G' is the notGlobal (process-specific) bit (ARMv6)
 *	'S' is the shared (SMP) bit (ARMv6)
 *	'A' in the access permission extension (ATX) bit (ARMv6) 
 *	'TEX' remap register control bits (ARMv6)
 *	'AP' is the access protection
 *	'dom' is the domain for the translation
 *	'C' is the cache attribute 
 *	'B' is the write buffer attribute
 */
#define PTE_TYPE_FAULT	0x00000000	/* fault entry type */
#define PTE_TYPE_SMALL	0x00000002	/* small page entry type */

#if	(__ARM_VMSA__ >= 6)
#define PTE_TYPE_MASK	\
			0x00000002	/* mask to get pte type */
#elif (__ARM_VMSA__ == 4)
#define PTE_TYPE_LARGE	0x00000001	/* large page entry type */
#define PTE_TYPE_TINY	0x00000003	/* tiny page entry type */
#define PTE_TYPE_MASK	\
			0x00000003	/* mask to get pte type */
#endif

#define PTE_LARGE_MASK	0xFFFF0000	/* mask for a large page */
#define PTE_SMALL_MASK	0xFFFFF000	/* mask for a small page */
#define PTE_TINE_MASK	0xFFFFFC00	/* mask for a tiny page */

#define PTE_LARGE_SHIFT	16		/* page shift for 64KB page */
#define PTE_SMALL_SHIFT	12		/* page shift for 4KB page */
#define PTE_TINY_SHIFT	10		/* page shift for 1KB page */

#define PTE_SMALL_APMASK 0x30		 /* get a set of AP bits from the pte */
#define PTE_SMALL_APSHIFT 4		 /* how far to shift to isolate */
#define PTE_SMALL_APXSHIFT 9		 /* priv mode read-only modifier shift */

#if (__ARM_VMSA__ >= 6)
#define ARM_PTE_AP(x)	((x) << 4)	 /* default PTE access protections */
#define ARM_PTE_APX(x)	((x) << 9)	 /* priv mode read-only modifier */
#define ARM_PTE_APXMASK	(1 << 9)	 /* mask to get APX protection */

#define PTE_GLOBAL_MASK	0x00000800	 /* mask to determine notGlobal bit */
#define PTE_NOTGLOBAL	0x00000800	 /* value for a per-process mapping */
#define PTE_GLOBAL	0x00000000	 /* value for a global mapping */
#define PTE_SHARED_MASK	0x00000400	 /* shared (SMP) mapping mask */
#define PTE_NOTSHARED	0x00000000	 /* not shared (SMP) mapping */
#define PTE_SHARED	0x00000400	 /* shared (SMP) mapping */
#define PTE_LGXNMASK	0x00008000	 /* mask for large page XN bit */
#define PTE_LGNOEXECUTE 0x00008000	 /* large page no execute */
#define PTE_SMXNMASK	0x00000001	 /* mask for small page XN bit */
#define PTE_SMNOEXECUTE	0x00000001	 /* small page no execute */
#define PTE_EXECUTE	0x00000000	 /* same value everywhere */

#define ARM_PTE_TEX(x)		((x) << 6)
#define	ARM_PTE_TEX_MASK	(7<<6)
#define ARM_PTE_CB(x)		((x) << 2)
#define	ARM_PTE_CB_MASK		(3<<2)

#define PTE_CACHE_DISABLE	(ARM_PTE_TEX(CACHE_TEX_DISABLE) | ARM_PTE_CB(CACHE_CB_DISABLE))
#define PTE_CACHE_WRITECOMB	(ARM_PTE_TEX(CACHE_TEX_WRITECOMB) | ARM_PTE_CB(CACHE_CB_WRITECOMB))
#define PTE_CACHE_WRITETHRU	(ARM_PTE_TEX(CACHE_TEX_WRITETHRU) | ARM_PTE_CB(CACHE_CB_WRITETHRU))
#define PTE_CACHE_WRITEBACK	(ARM_PTE_TEX(CACHE_TEX_WRITEBACK) | ARM_PTE_CB(CACHE_CB_WRITEBACK))

#elif (__ARM_VMSA__ == 4)

#define ARM_PTE_AP(x)	(((x)<<10)|((x)<<8)|((x)<<6)|((x)<<4)) /* default PTE access protections, 1KB each */
#define ARM_PTE_APX(x)  (0)		 /* can't ro protect priv mode */
#define ARM_PTE_APXMASK (0)		 /* can't ro protect priv mode */

#define PTE_GLOBAL_MASK	0x00000000	 /* mask to "should be zero" */
#define PTE_NOTGLOBAL	0x00000000	 /* not implemented */
#define PTE_GLOBAL	0x00000000	 /* not implemented */
#define PTE_SHARED_MASK	0x00000000	 /* mask to "should be zero" */
#define PTE_NOTSHARED	0x00000000	 /* not implemented */
#define PTE_SHARED	0x00000000	 /* not implemented */
#define PTE_LGXNMASK	0x00000000	 /* mask to "should be zero" */
#define PTE_LGNOEXECUTE	0x00000000	 /* not implemented */
#define PTE_SMXNMASK	0x00000000	 /* mask to "should be zero" */
#define PTE_SMNOEXECUTE	0x00000000	 /* not implemented */
#define PTE_EXECUTE	0x00000000	 /* same value everywhere */

#define ARM_PTE_TEX(x)		(0)
#define	ARM_PTE_TEX_MASK	(0)
#define ARM_PTE_CB(x)		((x) << 2)
#define	ARM_PTE_CB_MASK		(3<<2)

#define PTE_CACHE_DISABLE	(ARM_PTE_CB(CACHE_CB_DISABLE))
#define PTE_CACHE_WRITECOMB	(ARM_PTE_CB(CACHE_CB_WRITECOMB))
#define PTE_CACHE_WRITETHRU	(ARM_PTE_CB(CACHE_CB_WRITETHRU))
#define PTE_CACHE_WRITEBACK	(ARM_PTE_CB(CACHE_CB_WRITEBACK))

#endif

#define PTE_CACHE_DEFAULT	PTE_CACHE_WRITEBACK
#define PTE_CACHE_MASK		(ARM_PTE_TEX_MASK | ARM_PTE_CB_MASK)


#define ARM_DOM_DEFAULT	0		 /* domain that forces AP use */
#define ARM_DAC_DEFAULT DAC_SET(ARM_DOM_DEFAULT, DAC_CLIENT)

#define ARM_TTE_TYPE	TTE_TYPE_COARSE  /* default is coarse page tables */
#define ARM_TTE_MASK	TTE_COARSE_MASK	 /* physical address part of tte */
#define ARM_TTE_EXECUTE TTE_EXECUTE	 /* default is executable at tte level */

#define ARM_PTE_SHIFT	PTE_COARSE_SHIFT /* shift to compute pt index */
#define ARM_PTE_IMASK	PTE_COARSE_IMASK /* mask to compute pt index */
#define ARM_PTE_PP	(ARM_PTE_IMASK+1)/* ptes per page */

#define ARM_PTE_TYPE	PTE_TYPE_SMALL	 /* small (4KB) pages by default */
#define ARM_PTE_NOEXECUTE	PTE_SMNOEXECUTE	 /* small version of no execute */
#define ARM_PTE_MASK	PTE_SMALL_MASK	 /* default page component of address */
#define ARM_PTE_APMASK	PTE_SMALL_APMASK /* get a set of AP bits from the pte */
#define ARM_PTE_APSHIFT	PTE_SMALL_APSHIFT/* get a set of AP bits from the pte */

#define ARM_PAGEMASK	~PTE_SMALL_MASK	 /* default is small page table entries */
#define ARM_PAGESHIFT	PTE_SMALL_SHIFT	 /* page table shift */

#define ARM_TINY_PAGE_SIZE   (1024)           /* 1KB */
#define ARM_SMALL_PAGE_SIZE  (4096)           /* 4KB */
#define ARM_LARGE_PAGE_SIZE  (64*1024)        /* 64KB */
#define ARM_SECTION_SIZE     (1024*1024)      /* 1MB */
#define ARM_SUPERSECTION_SIZE  (16*1024*1024) /* 16MB */

/*
 * Format of the Debug Status and Control Register (DBGDSCR)
 */
#define ARM_DBGDSCR_RXFULL		    (1 << 30)
#define ARM_DBGDSCR_TXFULL		    (1 << 29)
#define ARM_DBGDSCR_RXFULL_1		    (1 << 27)
#define ARM_DBGDSCR_TXFULL_1		    (1 << 26)
#define ARM_DBGDSCR_PIPEADV		    (1 << 25)
#define ARM_DBGDSCR_INSTRCOMPL_1	    (1 << 24)
#define ARM_DBGDSCR_EXTDCCMODE_MASK	    (3 << 20)
#define ARM_DBGDSCR_EXTDCCMODE_NONBLOCKING  (0 << 20)
#define ARM_DBGDSCR_EXTDCCMODE_STALL	    (1 << 20)
#define ARM_DBGDSCR_EXTDCCMODE_FAST	    (1 << 20)
#define ARM_DBGDSCR_ADADISCARD		    (1 << 19)
#define ARM_DBGDSCR_NS			    (1 << 18)
#define ARM_DBGDSCR_SPNIDDIS		    (1 << 17)
#define ARM_DBGDSCR_SPIDDIS		    (1 << 16)
#define ARM_DBGDSCR_MDBGEN		    (1 << 15)
#define ARM_DBGDSCR_HDBGEN		    (1 << 14)
#define ARM_DBGDSCR_ITREN		    (1 << 13)
#define ARM_DBGDSCR_UDCCDIS		    (1 << 12)
#define ARM_DBGDSCR_INTDIS		    (1 << 11)
#define ARM_DBGDSCR_DBGACK		    (1 << 10)
#define ARM_DBGDSCR_DBGNOPWRDWN		    (1 << 9)
#define ARM_DBGDSCR_UND_1		    (1 << 8)
#define ARM_DBGDSCR_ADABORT_1		    (1 << 7)
#define ARM_DBGDSCR_SDABORT_1		    (1 << 6)
#define ARM_DBGDSCR_MOE_MASK		    (15 << 2)
#define ARM_DBGDSCR_MOE_HALT_REQUEST	    (0 << 2)
#define ARM_DBGDSCR_MOE_BREAKPOINT	    (1 << 2)
#define ARM_DBGDSCR_MOE_ASYNC_WATCHPOINT    (2 << 2)
#define ARM_DBGDSCR_MOE_BKPT_INSTRUCTION    (3 << 2)
#define ARM_DBGDSCR_MOE_EXT_DEBUG_REQ	    (4 << 2)
#define ARM_DBGDSCR_MOE_VECTOR_CATCH	    (5 << 2)
#define ARM_DBGDSCR_MOE_DSIDE_ABORT	    (6 << 2)
#define ARM_DBGDSCR_MOE_ISIDE_ABORT	    (7 << 2)
#define ARM_DBGDSCR_MOE_OS_UNLOCK_CATCH	    (8 << 2)
#define ARM_DBGDSCR_MOE_SYNC_WATCHPOINT	    (10 << 2)

#define ARM_DBGDSCR_RESTARTED		    (1 << 1)
#define ARM_DBGDSCR_HALTED		    (1 << 0)

/*
 * Format of the Debug & Watchpoint Breakpoint Value and Control Registers
 * Using ARMv7 names; ARMv6 and ARMv6.1 are bit-compatible
 */
#define ARM_DBG_VR_ADDRESS_MASK             0xFFFFFFFC  /* BVR & WVR */
#define ARM_DBGBVR_CONTEXTID_MASK           0xFFFFFFFF  /* BVR only  */

#define ARM_DBG_CR_ADDRESS_MASK_MASK        0x1F000000  /* BCR & WCR */
#define ARM_DBGBCR_MATCH_MASK               (1 << 22)   /* BCR only  */
#define ARM_DBGBCR_MATCH_MATCH              (0 << 22)
#define ARM_DBGBCR_MATCH_MISMATCH           (1 << 22)
#define ARM_DBGBCR_TYPE_MASK                (1 << 21)   /* BCR only */
#define ARM_DBGBCR_TYPE_IVA                 (0 << 21)
#define ARM_DBGBCR_TYPE_CONTEXTID           (1 << 21)
#define ARM_DBG_CR_LINKED_MASK              (1 << 20)   /* BCR & WCR */
#define ARM_DBG_CR_LINKED_LINKED            (1 << 20)
#define ARM_DBG_CR_LINKED_UNLINKED          (0 << 20)
#define ARM_DBG_CR_LINKED_BRP_MASK          0x000F0000  /* BCR & WCR */
#define ARM_DBG_CR_SECURITY_STATE_MASK      (3 << 14)   /* BCR & WCR */
#define ARM_DBG_CR_SECURITY_STATE_BOTH      (0 << 14)
#define ARM_DBG_CR_SECURITY_STATE_NONSECURE (1 << 14)
#define ARM_DBG_CR_SECURITY_STATE_SECURE    (2 << 14)
#define ARM_DBGWCR_BYTE_ADDRESS_SELECT_MASK 0x00001FE0  /* WCR only  */
#define ARM_DBG_CR_BYTE_ADDRESS_SELECT_MASK 0x000001E0  /* BCR & WCR */
#define ARM_DBGWCR_ACCESS_CONTROL_MASK      (3 << 3)    /* WCR only */
#define ARM_DBCWCR_ACCESS_CONTROL_LOAD      (1 << 3)
#define ARM_DBCWCR_ACCESS_CONTROL_STORE     (2 << 3)
#define ARM_DBCWCR_ACCESS_CONTROL_ANY       (3 << 3)
#define ARM_DBG_CR_MODE_CONTROL_MASK        (3 << 1)    /* BCR & WCR */
#define ARM_DBG_CR_MODE_CONTROL_U_S_S       (0 << 1)    /* BCR only  */
#define ARM_DBG_CR_MODE_CONTROL_PRIVILEDGED (1 << 1)    /* BCR & WCR */
#define ARM_DBG_CR_MODE_CONTROL_USER        (2 << 1)    /* BCR & WCR */
#define ARM_DBG_CR_MODE_CONTROL_ANY         (3 << 1)    /* BCR & WCR */
#define ARM_DBG_CR_ENABLE_MASK              (1 << 0)    /* BCR & WCR */
#define ARM_DBG_CR_ENABLE_ENABLE            (1 << 0)
#define ARM_DBG_CR_ENABLE_DISABLE           (0 << 0)

#endif	/* _ARM_PROC_REG_H_ */
