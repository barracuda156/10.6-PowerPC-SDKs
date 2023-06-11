/*
        NSSpellChecker.h
        Application Kit
        Copyright (c) 1990-2008, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSTextCheckingResult.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSDictionary, NSString, NSOrthography, NSPanel, NSView;

/* The NSSpellChecker object is used by a client (e.g. a document in an application) to spell-check a given NSString.  There is only one NSSpellChecker instance per application (since spell-checking is interactive and you only have one mouse and one keyboard).

The string being spell-checked need only be valid for the duration of the call to checkSpellingOfString:... or countWordsInString:.

The usual usage of this is to implement a checkSpelling: method in an object that has text to check, then, upon receiving checkSpelling:, the object calls [[NSSpellChecker sharedInstance] checkSpellingOfString:...] with an NSString object consisting of the text that should be checked.  The caller is responsible for selecting the misspelled word that is found and for updating the panel UI if desired with the updateSpellPanelWithMisspelledWord: method.
*/

@interface NSSpellChecker : NSObject  {

/*All instance variables are private*/

@private
    // All instance variables are private and subject to future change.  Do not access them.
    id _guessesBrowser;
    id _wordField;
    id _languagePopUp;
    id _guessesList;
    id _panel;
    id _userDictionaries;
    id _correctButton;
    id _guessButton;
    id _ignoreButton;
    id _accessoryView;
    id _dictionaryBrowser;
    NSString *_selectionString;
    id _spellServers;
    NSString *_lastGuess;
    
    struct __scFlags {
        unsigned int autoShowGuesses:1;
        unsigned int needDelayedGuess:1;
        unsigned int unignoreInProgress:1;
        unsigned int wordFieldEdited:1;
        unsigned int inSpelling:1;
        unsigned int reconnectSpelling:1;
        unsigned int inGrammar:1;
        unsigned int reconnectGrammar:1;
        unsigned int languageIdentification:1;
        unsigned int _reserved:23;
    } _scFlags;
    
    id _deleteButton;
    id _openButton;
    id _learnButton;
    id _infoField;
    id _grammarControl;
}

/* Only one per application. */
+ (NSSpellChecker *)sharedSpellChecker;
+ (BOOL)sharedSpellCheckerExists;

/* Returns a guaranteed unique tag to use as the spell document tag for a document.  You should use this method to generate tags, if possible, to avoid collisions with other objects that can be spell checked. */
+ (NSInteger)uniqueSpellDocumentTag;

/* Initiates a spell-check of a string.  Returns the range of the first misspelled word (and optionally the wordCount by reference). */
- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset language:(NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(NSInteger)tag wordCount:(NSInteger *)wordCount;

- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset;

/* Just counts the words without checking spelling.  Returns -1 if counting words isn't supported by the spell server selected. */
- (NSInteger)countWordsInString:(NSString *)stringToCount language:(NSString *)language;

/* Initiates a grammar-check of a string.  Returns the range of the first flagged sentence (or similar grammatical unit), and optionally an array of dictionaries describing details within this sentence.  Keys in the details dictionaries are described in Foundation/NSSpellServer.h. */
- (NSRange)checkGrammarOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset language:(NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(NSInteger)tag details:(NSArray **)details AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Requests unified text checking for the given range of the given string.  The checkingTypes should be a bitmask of checking types from NSTextCheckingResult.h, describing which types of checking are desired.  The options dictionary allows clients to pass in options for certain types of checking.  The orthography and wordCount arguments will return by reference these two attributes of the range as a whole, while the return value is an array of NSTextCheckingResult objects describing particular items found during checking and their individual ranges. */  
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
- (NSArray *)checkString:(NSString *)stringToCheck range:(NSRange)range types:(NSTextCheckingTypes)checkingTypes options:(NSDictionary *)options inSpellDocumentWithTag:(NSInteger)tag orthography:(NSOrthography **)orthography wordCount:(NSInteger *)wordCount;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 */

/* Optional keys that may be used in the options dictionary with checkString:range:types:options:inSpellDocumentWithTag:orthography:wordCount:. */
APPKIT_EXTERN NSString *NSTextCheckingOrthographyKey    AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSOrthography indicating an orthography to be used as a starting point for orthography checking, or as the orthography if orthography checking is not enabled
APPKIT_EXTERN NSString *NSTextCheckingQuotesKey         AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSArray containing four strings to be used with NSTextCheckingTypeQuote (opening double quote, closing double quote, opening single quote, and closing single quote in that order); if not specified, values will be taken from user's preferences
APPKIT_EXTERN NSString *NSTextCheckingReplacementsKey   AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSDictionary containing replacements to be used with NSTextCheckingTypeReplacement; if not specified, values will be taken from user's preferences

/* The checkSpellingOfString:... methods return the range of the misspelled word found.  It is up to the client to select that word in their document and to cause the spelling panel to update itself to reflect the found misspelling.  Clients should call updateSpellPanelWithMisspelledWord: to inform the spelling panel of the word to be displayed. */
- (void)updateSpellingPanelWithMisspelledWord:(NSString *)word;

/* The checkGrammarOfString:... method return the range of the sentence (or equivalent grammatical unit) with grammar issues, and an array of details describing the individual issues.  It is up to the client to select one of those details in their document and to cause the spelling panel to update itself to reflect the found issue.  Clients should call updateSpellingPanelWithGrammarString:detail: to inform the spelling panel of this.  The string should be the entire sentence, i.e., the substring corresponding to the overall range returned by checkGrammarOfString:..., and the detail should be one of the elements of the details array. */
- (void)updateSpellingPanelWithGrammarString:(NSString *)string detail:(NSDictionary *)detail AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Sets and gets attributes of the spell-correction panel. */

- (NSPanel *)spellingPanel;
- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;

/* This method should be called from the client's implementation of -ignoreSpelling: */
- (void)ignoreWord:(NSString *)wordToIgnore inSpellDocumentWithTag:(NSInteger)tag;

- (NSArray *)ignoredWordsInSpellDocumentWithTag:(NSInteger)tag;
- (void)setIgnoredWords:(NSArray *)words inSpellDocumentWithTag:(NSInteger)tag;
- (NSArray *)guessesForWord:(NSString *)word;
- (NSArray *)guessesForWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language inSpellDocumentWithTag:(NSInteger)tag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns an array of strings, in the order in which they should be presented, representing complete words that the user might be trying to type when starting by typing the partial word at the given range in the given string. */
- (NSArray *)completionsForPartialWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language inSpellDocumentWithTag:(NSInteger)tag AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* When a document closes, it should notify the NSSpellChecker via closeSpellDocumentWithTag: so that its ignored word list gets cleaned up. */
- (void)closeSpellDocumentWithTag:(NSInteger)tag;

/* Allows programmatic setting of the language to spell-check in (normally chosen by a pop-up-list in the spelling panel and defaulted to the user's preferred language, so call this with care).  Entries in the availableLanguages list are languages as described in the spellchecker's info dictionary, usually language abbreviations such as en_US.  setLanguage: accepts any of the language formats used by NSBundle, and tries to find the closest match among the available languages. */
- (NSString *)language;
- (BOOL)setLanguage:(NSString *)language;
- (NSArray *)availableLanguages AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (BOOL)automaticallyIdentifiesLanguages AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setAutomaticallyIdentifiesLanguages:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Allows programmatic setting of the misspelled word field. */
- (void)setWordFieldStringValue:(NSString *)aString;

/* These allow clients to programmatically instruct the spellchecker to learn and unlearn words, and to determine whether a word has been learned (and hence can potentially be unlearned). */
- (void)learnWord:(NSString *)word;
- (BOOL)hasLearnedWord:(NSString *)word AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)unlearnWord:(NSString *)word AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


@end

@interface NSSpellChecker(NSDeprecated)

/* This is the deprecated pre-10.5 equivalent of unlearnWord:. */
- (void)forgetWord:(NSString *)word;

@end
