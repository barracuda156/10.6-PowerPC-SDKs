/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */

#ifndef _PEXPERT_ARM_BOOT_H_
#define _PEXPERT_ARM_BOOT_H_

#define BOOT_LINE_LENGTH        256

/*
 * Video information.. 
 */

struct Boot_Video {
	unsigned long	v_baseAddr;	/* Base address of video memory */
	unsigned long	v_display;	/* Display Code (if Applicable */
	unsigned long	v_rowBytes;	/* Number of bytes per pixel row */
	unsigned long	v_width;	/* Width */
	unsigned long	v_height;	/* Height */
	unsigned long	v_depth;	/* Pixel Depth */
};

typedef struct Boot_Video	Boot_Video;

/* Boot argument structure - passed into Mach kernel at boot time.
 */
#define kBootArgsRevision		1
#define kBootArgsVersion1		1
#define kBootArgsVersion2		2

typedef struct boot_args {
	uint16_t		Revision;			/* Revision of boot_args structure */
	uint16_t		Version;			/* Version of boot_args structure */
	uint32_t		virtBase;			/* Virtual base of memory */
	uint32_t		physBase;			/* Physical base of memory */
	uint32_t		memSize;			/* Size of memory */
	uint32_t		topOfKernelData;	/* Highest physical address used in kernel data area */
	Boot_Video		Video;				/* Video Information */
	uint32_t		machineType;		/* Machine Type */
	void			*deviceTreeP;		/* Base of flattened device tree */
	uint32_t		deviceTreeLength;	/* Length of flattened tree */
	char			CommandLine[BOOT_LINE_LENGTH];	/* Passed in command line */
} boot_args;

#endif /* _PEXPERT_ARM_BOOT_H_ */
