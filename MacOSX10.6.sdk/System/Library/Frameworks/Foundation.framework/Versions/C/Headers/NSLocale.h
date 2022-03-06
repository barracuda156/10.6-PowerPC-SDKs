/*	NSLocale.h
	Copyright (c) 2003-2008, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSArray, NSDictionary, NSString;

// Toll-free bridged with CFLocaleRef

@interface NSLocale : NSObject <NSCopying, NSCoding>

- (id)objectForKey:(id)key;

- (NSString *)displayNameForKey:(id)key value:(id)value;

@end

@interface NSLocale (NSExtendedLocale)

- (NSString *)localeIdentifier;  // same as NSLocaleIdentifier

@end

@interface NSLocale (NSLocaleCreation)

+ (id)systemLocale;
+ (id)currentLocale;
+ (id)autoupdatingCurrentLocale AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (id)initWithLocaleIdentifier:(NSString *)string;

@end

@interface NSLocale (NSLocaleGeneralInfo)

+ (NSArray *)availableLocaleIdentifiers;
+ (NSArray *)ISOLanguageCodes;
+ (NSArray *)ISOCountryCodes;
+ (NSArray *)ISOCurrencyCodes;
+ (NSArray *)commonISOCurrencyCodes AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (NSArray *)preferredLanguages AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

+ (NSDictionary *)componentsFromLocaleIdentifier:(NSString *)string;
+ (NSString *)localeIdentifierFromComponents:(NSDictionary *)dict;

+ (NSString *)canonicalLocaleIdentifierFromString:(NSString *)string;
+ (NSString *)canonicalLanguageIdentifierFromString:(NSString *)string;

+ (NSString *)localeIdentifierFromWindowsLocaleCode:(uint32_t)lcid AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (uint32_t)windowsLocaleCodeFromLocaleIdentifier:(NSString *)localeIdentifier AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end


FOUNDATION_EXPORT NSString * const NSCurrentLocaleDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


FOUNDATION_EXPORT NSString * const NSLocaleIdentifier AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleLanguageCode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleCountryCode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleScriptCode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleVariantCode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// NSString
FOUNDATION_EXPORT NSString * const NSLocaleExemplarCharacterSet AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;// NSCharacterSet
FOUNDATION_EXPORT NSString * const NSLocaleCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		// NSCalendar
FOUNDATION_EXPORT NSString * const NSLocaleCollationIdentifier AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // NSString
FOUNDATION_EXPORT NSString * const NSLocaleUsesMetricSystem AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSNumber boolean
FOUNDATION_EXPORT NSString * const NSLocaleMeasurementSystem AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleCurrencySymbol AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;      // NSString
FOUNDATION_EXPORT NSString * const NSLocaleCurrencyCode AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// NSString
FOUNDATION_EXPORT NSString * const NSLocaleCollatorIdentifier AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSString value

// Values for NSCalendar identifiers (not the NSLocaleCalendar property key)
FOUNDATION_EXPORT NSString * const NSGregorianCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSBuddhistCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSChineseCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSHebrewCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSIslamicCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSIslamicCivilCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSJapaneseCalendar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
FOUNDATION_EXPORT NSString * const NSTaiwaneseCalendar AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
FOUNDATION_EXPORT NSString * const NSPersianCalendar AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
FOUNDATION_EXPORT NSString * const NSIndianCalendar AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
FOUNDATION_EXPORT NSString * const NSISO8601Calendar AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#endif

