/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
	.text
	.align 2
L_ExceptionVectorsBase:
	.long  EXT(ExceptionVectorsBase) 
L_CurrentThread:
	.long  EXT(CurrentThread) 
L_BootCpuDatap:
	.long  EXT(BootCpuDatap) 
L_intstack_top:
	.long  EXT(intstack_top)
L_fiqstack_top:
	.long  EXT(fiqstack_top)
L_gVirtBase:
	.long  EXT(gVirtBase)
L_gPhysBase:
	.long  EXT(gPhysBase)
L_EntropyDatap:
	.long  EXT(EntropyData)
L_kdebug_enable:
	.long  EXT(kdebug_enable)
