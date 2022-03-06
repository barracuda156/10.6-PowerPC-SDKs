/*
 *  NetFS.h
 *
 *  Copyright (c) 2008 Apple Computer, Inc. All rights reserved.
 */
#ifndef _NETFS_H_
#define _NETFS_H_

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SInt32 netfsError;

/*
 * Dictionary keys for the server parameters dictionary returned by
 * GetServerInfo methods.
 *
 * Note:
 * 1)  If Kerberos is supported, then kNetFSKerberosInfoKey is a dictionary
 *     with Kerberos info
 * 2)  kNetFSServerAddressKey is the DNS address or presentation form of the
 *     IP address like "192.168.1.1"
 */
#define kNetFSServerDisplayNameKey	CFSTR("ServerDisplayName")
#define kNetFSSupportsChangePasswordKey	CFSTR("SupportsChangePassword")
#define kNetFSSupportsGuestKey		CFSTR("SupportsGuest")
#define kNetFSSupportsKerberosKey	CFSTR("SupportsKerberos")
#define kNetFSGuestOnlyKey		CFSTR("GuestOnly")
#define kNetFSNoMountAuthenticationKey	CFSTR("NoMountAuthentication")
/*
 * XXX - the strings for these will change when NetAuth changes to
 * use these #defines rather than the kMountedBy... #defines.
 */
#define	kNetFSConnectedWithKerberosKey	CFSTR("MountedByKerberos")
#define kNetFSConnectedAsUserKey	CFSTR("MountedByUser")
#define kNetFSConnectedAsGuestKey	CFSTR("MountedByGuest")
#define kNetFSConnectedMultiUserKey	CFSTR("ConnectedMultiUser")

#define kNetFSKerberosInfoKey		CFSTR("KerberosInfo")
#define kNetFSServicePrincipalKey	CFSTR("ServicePrincipal")
#define kNetFSServerAddressKey		CFSTR("ServerAddress")
#define kNetFSClientPrincipalKey	CFSTR("ClientPrincipal")

/*
 * Dictionary keys for the URL parameters dictionary returned by ParseURL
 * methods and passed as an argument to CreateURL methods.
 */
#define kNetFSSchemeKey			CFSTR("Scheme")
#define kNetFSHostKey			CFSTR("Host")
#define kNetFSAlternatePortKey		CFSTR("AlternatePort")
#define kNetFSAuthorityParamsKey	CFSTR("AuthorityParams")
#define kNetFSUserNameKey		CFSTR("UserName")
#define kNetFSPasswordKey		CFSTR("Password")
#define kNetFSPathKey			CFSTR("Path")

/*
 * Dictionary keys for the open options passed to OpenSession methods.
 *
 * kNetFSNoUserPreferencesKey is set when automounting volumes, as we
 * might be automounting a user's home directory, and can't look in that
 * directory for preferences before we mount that directory.
 */
#define kNetFSNoUserPreferencesKey	CFSTR("NoUserPreferences")
#define kNetFSForceNewSessionKey	CFSTR("ForceNewSession")
#define kNetFSUseKerberosKey		CFSTR("Kerberos")
#define kNetFSUseGuestKey		CFSTR("Guest")
#define kNetFSChangePasswordKey		CFSTR("ChangePassword")
//#define kNetFSKerberosInfoKey		CFSTR("KerberosInfo")		/* defined for GetServerInfo above */

/*
 * Dictionary keys for the kKerberosInfoKey dictionary.
 */
#define kNetFSClientPrincipalKey	CFSTR("ClientPrincipal")
//#define kNetFSServicePrincipalKey	CFSTR("ServicePrincipal")	/* defined for GetServerInfo above */

/*
 * Dictionary keys for the session information returned by OpenSession
 * and GetMountInfo methods.
 */
#define kNetFSMountedByUserKey		CFSTR("MountedByUser")
#define kNetFSMountedByGuestKey		CFSTR("MountedByGuest")
#define	kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")
#define kNetFSMountedMultiUserKey	CFSTR("MountedMultiUser")

/*
 * Additional non-errno values that can be returned by OpenSession methods.
 */
#define ENETFSACCOUNTRESTRICTED		-5042
#define ENETFSPWDNEEDSCHANGE		-5045
#define ENETFSPWDPOLICY			-5046

/*
 * Dictionary keys for options passed to EnumerateShares methods.
 */
#define kNetFSGetAccessRightsKey	CFSTR("GetAccessRights")

/*
 * Dictionary keys for the dictionary for a sharepoint, as returned
 * by EnumerateShares methods in the dictionary of sharepoints.
 * Entries in the dictionary of sharepoints have the sharepoint name
 * as the key and the dictionary for that sharepoint as the value.
 * Also used for the dictionary of mount information returned by
 * Mount methods.
 *
 * Note:
 * 1)  only one of the following may be set when a sharepoint is currently
 *     mounted - kMountedByUser or kMountedByGuest
 * 2)  If the sharepoint is currently mounted, then kMountPathKey is the
 *     path to the mounted sharepoint
 * 3)  kDisplayNameKey is optional and if not present, then use the name of
 *     the dictionary to display the sharepoint name.
 *     kDisplayName is for sharepoint names that need special handling
 *     (ie '/' in AFP sharepoint name).
 * 4)  If there are no available sharepoints, then an empty dictionary is
 *     returned with no error.
 */
#define kNetFSAlreadyMountedKey		CFSTR("AlreadyMounted")
#define kNetFSMountPathKey		CFSTR("MountPath")
//#define kNetFSMountedByUserKey	CFSTR("MountedByUser")		/* defined for OpenSession above */
//#define kNetFSMountedByGuestKey	CFSTR("MountedByGuest")		/* defined for OpenSession above */
//#define kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")	/* defined for OpenSession above */
//#define kNetFSMountedMultiUserKey	CFSTR("MountedMultiUser")	/* defined for OpenSession above */
#define kNetFSHasPasswordKey		CFSTR("HasPassword")
#define kNetFSIsHiddenKey		CFSTR("IsHidden")
#define kNetFSPrinterShareKey		CFSTR("PrinterShare")
#define kNetFSAccessRightsKey		CFSTR("AccessRights")
#define kNetFSDisplayNameKey		CFSTR("DisplayName")

/*
 * Dictionary keys for the mount options dictionary passed to Mount methods.
 *
 * Note:
 * 1)  kNetFSMountFlagsKey is a collection of MNT_ flags for mount(2), such
 *     as MNT_DONTBROWSE, MNT_RDONLY, MNT_AUTOMOUNTED, MNT_NOSUID, MNT_NODEV,
 *     and MNT_QUARANTINE.
 * 2)  kNetFSNoUserPreferencesKey is set when automounting volumes, as we
 *     might be automounting a user's home directory, and can't look in that
 *     directory for preferences before we mount that directory
 */
//#define kNetFSNoUserPreferencesKey	CFSTR("NoUserPreferences")	/* defined for GetServerInfo above */
#define kNetFSPasswordKey		CFSTR("Password")
#define kNetFSSoftMountKey		CFSTR("SoftMount")
//#define kNetFSForceNewSessionKey	CFSTR("ForceNewSession")	/* defined for OpenSession above */
#define kNetFSMountFlagsKey		CFSTR("MountFlags")

/*
 * Dictionary keys for the mount information dictionary returned by
 * GetMountInfo methods.
 */
#define kNetFSMountedURLKey		CFSTR("MountedURL")
//#define kNetFSMountedByUserKey	CFSTR("MountedByUser")		/* defined for OpenSession above */
//#define kNetFSMountedByGuestKey	CFSTR("MountedByGuest")		/* defined for OpenSession above */
//#define kNetFSMountedByKerberosKey	CFSTR("MountedByKerberos")	/* defined for OpenSession above */
//#define kNetFSMountedMultiUserKey	CFSTR("MountedMultiUser")	/* defined for OpenSession above */

#ifdef __cplusplus
}
#endif

#endif /* !_NETFS_H_ */
