/*
 * Copyright (c) 2008 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _LIBKERN_OSKEXT_H
#define _LIBKERN_OSKEXT_H

#include <libkern/c++/OSObject.h>
#include <libkern/c++/OSContainers.h>
#include <libkern/OSKextLib.h>
#include <IOKit/IOLocks.h>

extern "C" {
#include <libkern/kxld.h>
#include <mach/kmod.h>
}

/*********************************************************************
* C functions used for callbacks.
*********************************************************************/
extern "C" {
void osdata_kmem_free(void * ptr, unsigned int length);
void osdata_phys_free(void * ptr, unsigned int length);
void osdata_vm_deallocate(void * ptr, unsigned int length);
};

// xxx - need to define these shared between kernel & user
typedef uint8_t OSKextExcludeLevel;
#define kOSKextExcludeNone  (0)
#define kOSKextExcludeKext  (1)
#define kOSKextExcludeAll   (2)

/********************************************************************/
/*! 
 * @class OSKext
 */
/********************************************************************/
class OSKext : public OSObject
{
    OSDeclareDefaultStructors(OSKext)

    friend class IOCatalogue;
    friend class IOPMrootDomain;
    friend class KLDBootstrap;
    friend class OSMetaClass;
    
private:

   /*************************
    * Instance variables
    *************************/
    OSDictionary * infoDict;

   /* These fields are required for tracking loaded kexts and
    * will always have values for a loaded kext.
    */
    uint32_t         loadTag;           // 'index' from old kmod_info
    const OSSymbol * bundleID;
    OSString       * path;              // just a hint
    OSKextVersion    version;           // parsed
    OSKextVersion    compatibleVersion; // parsed
    OSData         * linkedExecutable;
    kmod_info_t    * kmod_info;         // address into linkedExec. (for now)
    OSData         * linkState;         // only kept for libraries
    OSArray        * dependencies;      // all required to link
    OSSet          * metaClasses;       // for C++/OSMetaClass kexts
    OSKextLogFlags   logFlags;

    struct {
        unsigned int hasAllDependencies:1;

        unsigned int interface:1;
        unsigned int kernelComponent:1;
        unsigned int prelinked:1;
        unsigned int loaded:1;
        unsigned int started:1;

        unsigned int autounloadEnabled:1;
        unsigned int delayAutounload:1;    // for development
    } flags;

public:
    // xxx - rethink the debug flag set
    static const uint32_t DebugFlagBasic      = 1;
    static const uint32_t DebugFlagLoadBasic  = 1 << 1;
    static const uint32_t DebugFlagDetail     = 1 << 2;
    static const uint32_t DebugFlagKextBasic  = 1 << 3;
    static const uint32_t DebugFlagKextDetail = 1 << 4;
    static const uint32_t DebugFlagLoadDetail = 1 << 5;

#pragma mark Private Functions
private:
    static OSData     * getKernelLinkState(KXLDContext * kxld_context);

    static OSKext * withInfoDictAndPath(OSDictionary * anInfoDict,
        const char * aPath = NULL); // priv/prot
    bool registerWithInfoDictAndPath(
        OSDictionary * anInfoDict,
        const char * aPath = NULL);
    bool setInfoDict(OSDictionary * aDictionary);
    virtual bool setExecutableAndResources(
        OSData       * anExecutable,
        OSDictionary * resourcesDict,
        OSData       * externalData = NULL,
        bool           externalDataIsMkext = false); // priv/prot

    bool initWithBooterData(OSString * deviceTreeName,
        OSData * booterData);
    bool postInit(bool status);
        
    virtual void free(void);

    static OSReturn readMkext1Archive(
        OSData * mkextData,
        uint32_t * checksumPtr = NULL);
    bool initWithMkext1Info(
        OSDictionary * anInfoDict,
        OSData       * executableWrapper,
        OSData       * mkextData);
    static OSData * extractMkext1Entry(
        const void * mkextFileBase,
        const void * entry);

    static OSReturn readMkext2Archive(
        OSData * mkextData,
        OSDictionary ** mkextPlistOut,
        uint32_t * checksumPtr = NULL);
    bool initWithMkext2Info(
        OSDictionary * anInfoDict,
        OSData * mkextData);
    OSData * createMkext2FileEntry(
        OSData * mkextData,
        OSNumber * offsetNum,
        const char * entryName);
    static OSData * extractMkext2FileData(
        const UInt8 * data,
        uint32_t compressedSize,
        uint32_t fullSize);

    virtual const char * getBundleIDAsCString();
    OSData * getExecutable(void);

    virtual bool resolveDependencies(
        OSArray * loopStack = NULL); // priv/prot
    bool addBleedthroughDependencies(OSArray * anArray);
    virtual bool flushDependencies(bool forceFlag = false); // priv/prot
    virtual uint32_t getNumDependencies(void);
    virtual OSArray * getDependencies(void);

    virtual OSReturn load(
        OSKextExcludeLevel   startOpt         = kOSKextExcludeNone,
        OSKextExcludeLevel   startMatchingOpt = kOSKextExcludeAll,
        OSArray            * personalityNames = NULL,
        KXLDContext        * kxldContext      = NULL); // priv/prot
    OSReturn loadExecutable(KXLDContext * kxld_context);
    OSReturn setKmodDependencies(void);
    void setLoaded(bool flag);
    OSData * getLinkState(void);
    virtual OSReturn unload(void);

    static OSReturn unloadKext(OSKext * aKext);

    // kext, not IOService::start()!
    virtual OSReturn start(bool startDependenciesFlag = true);
    virtual OSReturn stop(void);  // kext, not IOService::stop()!

    static OSArray * copyAllKextPersonalities(void);

    static  OSArray      * copyLoadedKextInfo(OSArray * bundleIDs);
    virtual OSDictionary * copyInfo(void);

#pragma mark Protected Functions
protected:
    static void initialize(void); // priv/prot

    void setAutounloadEnabled(void);  // no arg! once on, always on.

    static OSReturn readMkextArchive(OSData * mkextData,
        uint32_t * checksumPtr = NULL); // priv/prot

    static OSKext * withBooterData(OSString * deviceTreeName,
        OSData * booterData);

    static void flushNonloadedKexts(void);
    
    virtual OSReturn addClass(OSMetaClass * aClass, uint32_t numClasses);
    virtual OSReturn removeClass(OSMetaClass * aClass);

    static OSDictionary * copyKexts(void);

    static  void  sendAllKextPersonalitiesToCatalog(bool startMatching = false);
    virtual void  sendPersonalitiesToCatalog(
        bool      startMatching    = false,
        OSArray * personalityNames = NULL);
    
    virtual bool    hasOSMetaClassInstances(void);

public:
#pragma mark Public-By Necessity Functions - for kext-mgmt internal use only
   /* Do not call these functions, they are for internal use only.
    */
    // called by IOPMrootDomain on system shutdown
    static void setLoadEnabled(bool flag);
    static void setUnloadEnabled(bool flag);
    static void setAutounloadEnabled(bool flag);
    static void setKernelRequestsEnabled(bool flag);

    // all getters subject to race condition, caller beware
    static bool getLoadEnabled(void);
    static bool getUnloadEnabled(void);
    // I don't think it should be possible to turn the autounloadEnabled off....
    static bool getAutounloadEnabled(void);
    static bool getKernelRequestsEnabled(void);

    static OSReturn loadFromMkext(OSData * mkextData,
        OSCollection ** messages);
    static OSReturn handleRequest(
        host_priv_t     hostPriv,
        OSDictionary  * requestDict,
        OSCollection ** responseCollectionPtr,
        OSData       ** responseDataPtr);

    static OSReturn removeKext(OSKext * aKext,
        bool removePersonalitiesFlag = false);
    static OSReturn removeKextWithBundleID(const char * bundleID,
        bool removePersonalitiesFlag = false);

    virtual OSSet * getMetaClasses(void);
    virtual void    reportOSMetaClassInstances(void);
    static  void    considerUnloads(void);

    virtual void    removePersonalitiesFromCatalog(void);

    // How can I make private/protected and have work in the kern_allocate callback?
    virtual bool setLinkedExecutable(
        OSData * anExecutable,
        bool isPrelinked = false);

   /* Here for the cutover only.
    */
    static void kmodStartNotify(const char * kmod_name);
    static void kmodStopNotify(const char * kmod_name);
    static void kmodDestroyNotify(const char * kmod_name);
    static OSReturn cutoverUnload(OSKext * theKext);

#pragma mark Really Public Functions
    // caller must release
    static OSKext * lookupKextWithBundleID(const char * aBundleID);
    static OSKext * lookupKextWithBundleID(OSString * aBundleID);
    static OSKext * lookupKextWithLoadTag(uint32_t aTag);
    static OSKext * lookupKextWithAddress(vm_address_t address);

    virtual OSObject * getPropertyForHostArch(const char * key);
    virtual void       removePropertyForHostArch(const char * key);

    static OSReturn loadKextWithBundleID(
        const char       * aBundleID,
        Boolean            allowDeferFlag      = true,
        Boolean            delayAutounloadFlag = false,
        OSKextExcludeLevel startOpt            = kOSKextExcludeNone,
        OSKextExcludeLevel startMatchingOpt    = kOSKextExcludeAll,
        OSArray          * personalityNames    = NULL);
    static OSReturn loadKextWithBundleID(
        OSString         * aBundleID,
        Boolean            allowDeferFlag      = true,
        Boolean            delayAutounloadFlag = false,
        OSKextExcludeLevel startOpt            = kOSKextExcludeNone,
        OSKextExcludeLevel startMatchingOpt    = kOSKextExcludeAll,
        OSArray          * personalityNames    = NULL);
        
    virtual OSArray * copyPersonalitiesArray(void);

    virtual void clientRetain(void);
    virtual void clientRelease(void);

    virtual const OSSymbol   * getBundleID();
    virtual OSKextVersion      getVersion(void);
    virtual OSKextVersion      getCompatibleVersion(void);
    virtual bool               isCompatibleWithVersion(OSKextVersion aVersion);
    virtual uint32_t           getLoadTag(void);
    virtual bool               declaresExecutable(void);  // might be missing!
    virtual bool               isInterface(void);
    virtual bool               isKernelComponent(void);
    virtual bool               isLoadableInSafeBoot(void);
    virtual bool               isLoaded(void);
    virtual bool               isStarted(void);
    
    static  OSData * copyUUIDOfKextWithBundleID(OSString * bundleID);
    virtual OSData * copyUUID(void);

    virtual OSData * copyResourceNamed(OSString * resourceName);

};

#endif /* !_LIBKERN_OSKEXT_H */
