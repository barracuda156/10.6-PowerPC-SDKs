/*
/* ColorSync- ColorSyncProfile.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
*/

#include <ColorSync/CMApplication.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef CMProfileRef ColorSyncProfileRef;

CSEXTERN float
ColorSyncProfileEstimateGammaWithDisplayID (const int32_t displayID, CFErrorRef* error);
   /*
    *   displayID - system-wide unique display ID (defined by IOKIt)
    *   error     - (optional) pointer to the error that will be returned in
    *               case of failure
    *   
    *   returns non-zero value if success or 0.0 in case of error.
    */

CSEXTERN float
ColorSyncProfileEstimateGamma (ColorSyncProfileRef prof, CFErrorRef* error);
    /*
    *   prof    - profile to perform estimation on
    *   error   - (optional) pointer to the error that will be returned in
    *             case of failure
    *   
    *   returns non-zero value if success or 0.0 in case of error
    */

#ifdef __cplusplus
}
#endif

