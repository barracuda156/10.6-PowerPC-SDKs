/*
	NSScriptCommandDescription.h
	Copyright (c) 1997-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSScriptCommand, NSString;

@interface NSScriptCommandDescription : NSObject<NSCoding> {
    @private
    NSString *_suiteName;
    NSString *_plistCommandName;
    FourCharCode _classAppleEventCode;
    FourCharCode _idAppleEventCode;
    NSString *_objcClassName;
    NSObject *_resultTypeNameOrDescription;
    FourCharCode _plistResultTypeAppleEventCode;
    id _moreVars;
}

/* Initialize, given a scripting suite name, command name, and command declaration dictionary of the sort that is valid in .scriptSuite property list files.
*/
- (id)initWithSuiteName:(NSString *)suiteName commandName:(NSString *)commandName dictionary:(NSDictionary *)commandDeclaration;

/* Return the suite name or command name provided at initialization time.
*/
- (NSString *)suiteName;
- (NSString *)commandName;

/* Return the four character codes that identify the command in Apple events.
*/
- (FourCharCode)appleEventClassCode;
- (FourCharCode)appleEventCode;

/* Return the Objective-C class name for instances of the described command.
*/
- (NSString *)commandClassName;

/* Return the declared type name for the result of execution of the described command, or nil if the described command is not declared to return a result.
*/
- (NSString *)returnType;

/* Return the four character code that identifies in Apple events the declared type of the result of execution of the described command.
*/
- (FourCharCode)appleEventCodeForReturnType;

/* Return the strings valid for use as keys into argument dictionaries in instances of the described command.
*/
- (NSArray *)argumentNames;

/* Return the declared type of the named argument in instances of the described command.
*/
- (NSString *)typeForArgumentWithName:(NSString *)argumentName;

/* Return the four character code that identifies in Apple events the declared type of the named argument in instances of the described command.
*/
- (FourCharCode)appleEventCodeForArgumentWithName:(NSString *)argumentName;

/* Return YES if the named argument is declared to be optional, NO otherwise.
*/
- (BOOL)isOptionalArgumentWithName:(NSString *)argumentName;

/* Create an instance of the described command.
*/
- (NSScriptCommand *)createCommandInstance;
- (NSScriptCommand *)createCommandInstanceWithZone:(NSZone *)zone;

@end
