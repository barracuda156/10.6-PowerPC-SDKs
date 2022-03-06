/*
 *  Block.h
 *
 *  Copyright 2008 Apple. All rights reserved.
 *
 */

#ifndef _Block_H_
#define _Block_H_

#if __cplusplus
extern "C" {
#endif

// Create a heap based copy of a Block or simply add a reference to an existing one.
// This must be paired with Block_release to recover memory, even when running
// under Objective-C Garbage Collection.
void *_Block_copy(const void *aBlock);

// Lose the reference, and if heap based and last reference, recover the memory
void _Block_release(const void *aBlock);

#if __cplusplus
}
#endif

// Type correct macros

#define Block_copy(xxx) ((typeof(xxx))_Block_copy((const void *)(xxx)))
#define Block_release(xxx) _Block_release((const void *)(xxx))



// Transitional.  Same as Block_release.
#define Block_destroy(xxx) _Block_destroy((const void *)(xxx))
void _Block_destroy(const void *aBlock);

#endif
