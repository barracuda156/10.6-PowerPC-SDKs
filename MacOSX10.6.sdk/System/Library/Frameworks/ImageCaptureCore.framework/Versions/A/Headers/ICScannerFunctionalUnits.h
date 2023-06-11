//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerFunctionalUnits.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------
/*!
	@header ICScannerFunctionalUnit
    @abstract ICScannerFunctionalUnit is an abstract class that represents a scanner functiona unit. ImageCaptureCore defines three concrete subclasses of ICScannerFunctionalUnit: ICScannerFunctionalUnitFlatbed, ICScannerFunctionalUnitTransparency and ICScannerFunctionalUnitDocumentFeeder. ICScannerDevice creates instances of these concrete subclasses.
*/

//-------------------------------------------------------------------------------------------------------------------- Constants
/*!
  @enum ICScannerFunctionalUnitType
  @abstract Scanner Functional Unit Types
  @constant ICScannerFunctionalUnitTypeFlatbed Flatbed functional unit.
  @constant ICScannerFunctionalUnitTypeFlatbed Transparency functional unit.
  @constant ICScannerFunctionalUnitTypeFlatbed Document feeder functional unit.
*/

enum
{
    ICScannerFunctionalUnitTypeFlatbed         = 0,
    ICScannerFunctionalUnitTypeTransparency    = 1,
    ICScannerFunctionalUnitTypeDocumentFeeder  = 2
};
typedef NSUInteger ICScannerFunctionalUnitType;

/*!
  @enum ICScannerMeasurementUnit
  @abstract Unit of measurement used by the scanner. This corresponds to values used for ICAP_UNITS as defined in the TWAIN Specification.
  @constant ICScannerMeasurementUnitInches      1 inch  = 2.54         cm
  @constant ICScannerMeasurementUnitCentimeters 1 cm    = 1.00         cm or 1/2.54 inches
  @constant ICScannerMeasurementUnitPicas       1 pica  = .42333333    cm or 1/6    inches
  @constant ICScannerMeasurementUnitPoints      1 point = .0352777775  cm or 1/72   inches
  @constant ICScannerMeasurementUnitTwips       1 twip  = .0001763888  cm or 1/1440 inches
  @constant ICScannerMeasurementUnitPixels      
*/

enum
{
    ICScannerMeasurementUnitInches      = 0,
    ICScannerMeasurementUnitCentimeters = 1,
    ICScannerMeasurementUnitPicas       = 2,
    ICScannerMeasurementUnitPoints      = 3,
    ICScannerMeasurementUnitTwips       = 4,
    ICScannerMeasurementUnitPixels      = 5
};
typedef NSUInteger ICScannerMeasurementUnit;

/*!
  @enum ICScannerBitDepth
  @abstract Bits per channel in the scanned image.
  @constant ICScannerBitDepth1Bit 1-bit image.
  @constant ICScannerBitDepth8Bits Image with 8 bits per channel.
  @constant ICScannerBitDepth16Bits Image with 16 bits per channel.
*/

enum
{
    ICScannerBitDepth1Bit	= 1,
    ICScannerBitDepth8Bits  = 8,
	ICScannerBitDepth16Bits	= 16
};
typedef NSUInteger ICScannerBitDepth;

/*!
  @enum ICScannerColorDataFormatType
  @abstract Identifies color data formats. Only relevant for multi-channel data. Corresponds to "ICAP_PLANARCHUNKY" of the TWAIN Specification.
  @constant ICScannerColorDataFormatTypeChunky For multi-channel data (e.g., RGB) data from all channels are interleaved.
  @constant ICScannerColorDataFormatTypePlanar For multi-channel data (e.g., RGB) each channel is transferred sequentially.
*/

enum
{
    ICScannerColorDataFormatTypeChunky  = 0,
    ICScannerColorDataFormatTypePlanar  = 1
};
typedef NSUInteger ICScannerColorDataFormatType;

/*!
  @enum ICScannerPixelDataType
  @abstract Pixel data types. Corresponds to "ICAP_PIXELTYPE" of the TWAIN Specification.
  @constant ICScannerPixelDataTypeBW Monochrome 1 bit pixel image.
  @constant ICScannerPixelDataTypeRGB Color image RGB color space.
  @constant ICScannerPixelDataTypePalette Indexed Color image.
  @constant ICScannerPixelDataTypeCMY Color image in CMY color space.
  @constant ICScannerPixelDataTypeCMYK Color image in CMYK color space.
  @constant ICScannerPixelDataTypeYUV Color image in YUV color space.
  @constant ICScannerPixelDataTypeYUVK Color image in YUVK color space.
  @constant ICScannerPixelDataTypeCIEXYZ Color image in CIEXYZ color space.
*/

enum
{
    ICScannerPixelDataTypeBW      = 0,
    ICScannerPixelDataTypeGray    = 1,
    ICScannerPixelDataTypeRGB     = 2,
    ICScannerPixelDataTypePalette = 3,
    ICScannerPixelDataTypeCMY     = 4,
    ICScannerPixelDataTypeCMYK    = 5,
    ICScannerPixelDataTypeYUV     = 6,
    ICScannerPixelDataTypeYUVK    = 7,
    ICScannerPixelDataTypeCIEXYZ  = 8
};
typedef NSUInteger ICScannerPixelDataType;

/*!
  @enum ICScannerFilmType
  @abstract Film types. Corresponds to "ICAP_FILMTYPE" used by the Image Catpure scanner modules.
  @constant ICScannerFilmTypePositive Positive film.
  @constant ICScannerFilmTypeNegative Negative film.
*/

enum
{
    ICScannerFilmTypePositive = 0,
    ICScannerFilmTypeNegative = 1
};
typedef NSUInteger ICScannerFilmType;

/*!
  @enum ICScannerDocumentSizeType
  @abstract Document size types. Corresponds to "ICAP_SUPPORTEDSIZES" used by the Image Catpure scanner modules. Also refer to TWAIN 1.9 Specification, page 9-483.
  @constant ICScannerDocumentSizeTypeDefault This is the platten size. Not valid for scanners without a platten.
  @constant ICScannerDocumentSizeTypeA4             A4,                               210mm x  297mm
  @constant ICScannerDocumentSizeTypeB5             B5/JIS B5,                        182mm x  257mm
  @constant ICScannerDocumentSizeTypeUSLetter       US Letter,        8.5” x 11.0”,   216mm x  280mm
  @constant ICScannerDocumentSizeTypeUSLegal        US Legal,         8.5” x 14.0”,   216mm x  356mm
  @constant ICScannerDocumentSizeTypeA5             A5,                               148mm x  210mm
  @constant ICScannerDocumentSizeTypeISOB4          B4/ISO B4,                        250mm x  353mm
  @constant ICScannerDocumentSizeTypeISOB6          B6/ISO B6,                        125mm x  176mm
  @constant ICScannerDocumentSizeTypeUSLedger       US Ledger,         11” x 17.0”,   280mm x  432mm
  @constant ICScannerDocumentSizeTypeUSExecutive    US Executive,    7.25" x 10.5",   184mm x  267mm
  @constant ICScannerDocumentSizeTypeA3             A3,                               297mm x  420mm
  @constant ICScannerDocumentSizeTypeISOB3          B3/ISO B3,                        353mm x  500mm
  @constant ICScannerDocumentSizeTypeA6             A6,                               105mm x  148mm
  @constant ICScannerDocumentSizeTypeC4             C4,                               229mm x  324mm
  @constant ICScannerDocumentSizeTypeC5             C5,                               162mm x  229mm
  @constant ICScannerDocumentSizeTypeC6             C6,                               114mm x  162mm
  @constant ICScannerDocumentSizeType4A0            4A0,                             1682mm x 2378mm
  @constant ICScannerDocumentSizeType2A0            2A0,                             1189mm x 1682mm
  @constant ICScannerDocumentSizeTypeA0             A0,                               841mm x 1189mm
  @constant ICScannerDocumentSizeTypeA1             A1,                               594mm x  841mm
  @constant ICScannerDocumentSizeTypeA2             A2,                               420mm x  594mm
  @constant ICScannerDocumentSizeTypeA7             A7,                                74mm x  105mm
  @constant ICScannerDocumentSizeTypeA8             A8,                                52mm x   74mm
  @constant ICScannerDocumentSizeTypeA9             A9,                                37mm x   52mm
  @constant ICScannerDocumentSizeType10             A10,                               26mm x   37mm
  @constant ICScannerDocumentSizeTypeISOB0          ISO B0,                          1000mm x 1414mm
  @constant ICScannerDocumentSizeTypeISOB1          ISO B1,                           707mm x 1000mm
  @constant ICScannerDocumentSizeTypeISOB2          ISO B2,                           500mm x  707mm
  @constant ICScannerDocumentSizeTypeISOB5          ISO B5,                           176mm x  250mm
  @constant ICScannerDocumentSizeTypeISOB7          ISO B7,                            88mm x  125mm
  @constant ICScannerDocumentSizeTypeISOB8          ISO B8,                            62mm x   88mm     
  @constant ICScannerDocumentSizeTypeISOB9          ISO B9,                            44mm x   62mm
  @constant ICScannerDocumentSizeTypeISOB10         ISO B10,                           31mm x   44mm
  @constant ICScannerDocumentSizeTypeJISB0          JIS B0,                          1030mm x 1456mm
  @constant ICScannerDocumentSizeTypeJISB1          JIS B1,                           728mm x 1030mm
  @constant ICScannerDocumentSizeTypeJISB2          JIS B2,                           515mm x  728mm
  @constant ICScannerDocumentSizeTypeJISB3          JIS B3,                           364mm x  515mm
  @constant ICScannerDocumentSizeTypeJISB4          JIS B4,                           257mm x  364mm
  @constant ICScannerDocumentSizeTypeJISB6          JIS B6,                           128mm x  182mm
  @constant ICScannerDocumentSizeTypeJISB7          JIS B7,                            91mm x  128mm 
  @constant ICScannerDocumentSizeTypeJISB8          JIS B8,                            64mm x   91mm
  @constant ICScannerDocumentSizeTypeJISB9          JIS B9,                            45mm x   64mm
  @constant ICScannerDocumentSizeTypeJISB10         JIS B10,                           32mm x   45mm
  @constant ICScannerDocumentSizeTypeC0             C0,                               917mm x 1297mm
  @constant ICScannerDocumentSizeTypeC1             C1,                               648mm x  917mm
  @constant ICScannerDocumentSizeTypeC2             C2,                               458mm x  648mm 
  @constant ICScannerDocumentSizeTypeC3             C3,                               324mm x  458mm 
  @constant ICScannerDocumentSizeTypeC7             C7,                                81mm x  114mm
  @constant ICScannerDocumentSizeTypeC8             C8,                                57mm x   81mm 
  @constant ICScannerDocumentSizeTypeC9             C9,                                40mm x   57mm
  @constant ICScannerDocumentSizeTypeC10            C10,                               28mm x   40mm
  @constant ICScannerDocumentSizeTypeUSStatement    US Statement,     5.5” x  8.5”,   140mm x  216mm
  @constant ICScannerDocumentSizeTypeBusinessCard   Business Card,                     90mm x   55mm 
*/

enum
{
    ICScannerDocumentSizeTypeDefault      = 0,
    ICScannerDocumentSizeTypeA4           = 1,
    ICScannerDocumentSizeTypeB5           = 2,
    ICScannerDocumentSizeTypeUSLetter     = 3,
    ICScannerDocumentSizeTypeUSLegal      = 4,
    ICScannerDocumentSizeTypeA5           = 5,
    ICScannerDocumentSizeTypeISOB4        = 6,
    ICScannerDocumentSizeTypeISOB6        = 7,
    ICScannerDocumentSizeTypeUSLedger     = 9,
    ICScannerDocumentSizeTypeUSExecutive  = 10,
    ICScannerDocumentSizeTypeA3           = 11,
    ICScannerDocumentSizeTypeISOB3        = 12,
    ICScannerDocumentSizeTypeA6           = 13,
    ICScannerDocumentSizeTypeC4           = 14,
    ICScannerDocumentSizeTypeC5           = 15,
    ICScannerDocumentSizeTypeC6           = 16,
    ICScannerDocumentSizeType4A0          = 17,
    ICScannerDocumentSizeType2A0          = 18,
    ICScannerDocumentSizeTypeA0           = 19,
    ICScannerDocumentSizeTypeA1           = 20,
    ICScannerDocumentSizeTypeA2           = 21,
    ICScannerDocumentSizeTypeA7           = 22,
    ICScannerDocumentSizeTypeA8           = 23,
    ICScannerDocumentSizeTypeA9           = 24,
    ICScannerDocumentSizeType10           = 25,
    ICScannerDocumentSizeTypeISOB0        = 26,
    ICScannerDocumentSizeTypeISOB1        = 27,
    ICScannerDocumentSizeTypeISOB2        = 28,
    ICScannerDocumentSizeTypeISOB5        = 29,
    ICScannerDocumentSizeTypeISOB7        = 30,
    ICScannerDocumentSizeTypeISOB8        = 31,
    ICScannerDocumentSizeTypeISOB9        = 32,
    ICScannerDocumentSizeTypeISOB10       = 33,
    ICScannerDocumentSizeTypeJISB0        = 34,
    ICScannerDocumentSizeTypeJISB1        = 35,
    ICScannerDocumentSizeTypeJISB2        = 36,
    ICScannerDocumentSizeTypeJISB3        = 37,
    ICScannerDocumentSizeTypeJISB4        = 38,
    ICScannerDocumentSizeTypeJISB6        = 39,
    ICScannerDocumentSizeTypeJISB7        = 40,
    ICScannerDocumentSizeTypeJISB8        = 41,
    ICScannerDocumentSizeTypeJISB9        = 42,
    ICScannerDocumentSizeTypeJISB10       = 43,
    ICScannerDocumentSizeTypeC0           = 44,
    ICScannerDocumentSizeTypeC1           = 45,
    ICScannerDocumentSizeTypeC2           = 46,
    ICScannerDocumentSizeTypeC3           = 47,
    ICScannerDocumentSizeTypeC7           = 48,
    ICScannerDocumentSizeTypeC8           = 49,
    ICScannerDocumentSizeTypeC9           = 50,
    ICScannerDocumentSizeTypeC10          = 51,
    ICScannerDocumentSizeTypeUSStatement  = 52,
    ICScannerDocumentSizeTypeBusinessCard = 53
};
typedef NSUInteger ICScannerDocumentSizeType;

/*!
  @enum ICScannerFunctionalUnitState
  @abstract A flag to indicate the scanner functional unit's state
  @constant ICScannerStateReady The scanner functional unit is ready for operation.
  @constant ICScannerStateScanInProgress The scanner functional unit is performing a scan.
  @constant ICScannerStateOverviewScanInProgress The scanner functional unit is performing an overview scan.
*/

enum
{
    ICScannerFunctionalUnitStateReady                  = (1 << 0),
    ICScannerFunctionalUnitStateScanInProgress         = (1 << 1),
    ICScannerFunctionalUnitStateOverviewScanInProgress = (1 << 2)
};
typedef unsigned int  ICScannerFunctionalUnitState;

/*!
  @enum ICScannerFeatureType
  @abstract Scanner Feature Types
  @constant ICScannerFeatureTypeEnumeration This feature can have one of several discrete values, strings or numbers.
  @constant ICScannerFeatureTypeRange This value of this feature lies within a range.
  @constant ICScannerFeatureTypeBoolean The value of this feature can be YES or NO.
*/

enum
{
    ICScannerFeatureTypeEnumeration = 0,
    ICScannerFeatureTypeRange       = 1,
    ICScannerFeatureTypeBoolean     = 2
};
typedef NSUInteger ICScannerFeatureType;

//------------------------------------------------------------------------------------------------------------- ICScannerFeature
/*!
	@class ICScannerFeature
    @abstract ICScannerFeature class is an abstract base class used to describe a scanner feature. ImageCaptureCore defines three concrete subclasses of ICScannerFeature: ICScannerFeatureEnumeration, ICScannerFeatureRange and ICScannerFeatureBoolean.
    @discussion The scanner functional units may have one or more instances of these classes to allow users to choose scanner-specific settings or operations before performing a scan.
*/

@interface ICScannerFeature : NSObject
{
@private
    id _sfProps;
}

/*!
    @property type
    @abstract ￼Scanner feature type.

*/
@property(readonly)   ICScannerFeatureType      type;

/*!
    @property internalName
    @abstract ￼The internal name of this feature.

*/
@property(readonly)   NSString*                 internalName;

/*!
    @property humanReadableName
    @abstract The human readable name of this feature.

*/
@property(readonly)   NSString*                 humanReadableName;

/*!
    @property tooltip
    @abstract ￼Tooltip text describing the feature.

*/
@property(readonly)   NSString*                 tooltip;
@end

//-------------------------------------------------------------------------------------------------- ICScannerFeatureEnumeration
/*!
	@class ICScannerFeatureEnumeration
    @abstract ICScannerFeatureEnumeration  object is used to represent a feature of a scanner functional unit that can have one of several discrete values.
    @discussion 
*/

@interface ICScannerFeatureEnumeration : ICScannerFeature
{
@private
    id _evProps;
}

/*!
    @property currentValue
    @abstract The current value. The current value can be set to one of the possible values in the "values" property below￼.

*/
@property(assign)     id        currentValue;

/*!
    @property defaultValue
    @abstract ￼The default value. The default value can be set to one of the possible values in the "values" property below.

*/
@property(readonly)   id        defaultValue;

/*!
    @property values
    @abstract An array of possible values. All items in this array must be of same type￼.

*/
@property(readonly)   NSArray*  values;

/*!
    @property menuItemLabels
    @abstract ￼The human readable menu item labels to be used in a menu to allow the user to select the current value from an array of possible values.

*/
@property(readonly)   NSArray*  menuItemLabels;

/*!
    @property menuItemLabelsTooltips
    @abstract ￼Tooltip text associated with the menu items.

*/
@property(readonly)   NSArray*  menuItemLabelsTooltips;
@end

//-------------------------------------------------------------------------------------------------------- ICScannerFeatureRange
/*!
	@class ICScannerFeatureRange
    @abstract ICScannerFeatureRange object is used to represent a property of a scanner functional unit whose value lies within a range.
    @discussion 
*/

@interface ICScannerFeatureRange : ICScannerFeature
{
@private
    id _rvProps;
}

/*!
    @property currentValue
    @abstract ￼The current value. Attempting to set the current value to a value that is not coincident with a step will result in a value corresponding to the nearest step being assigned to the current value.

*/
@property(assign)     CGFloat currentValue;

/*!
    @property defaultValue
    @abstract The default value￼. Attempting to set the default value to a value that is not coincident with a step will result in a value corresponding to the nearest step being assigned to the default value.

*/
@property(readonly)   CGFloat defaultValue;

/*!
    @property minValue
    @abstract The minimum value.

*/
@property(readonly)   CGFloat minValue;

/*!
    @property maxValue
    @abstract ￼The maximum value.

*/
@property(readonly)   CGFloat maxValue;

/*!
    @property stepSize
    @abstract ￼The step size.

*/
@property(readonly)   CGFloat stepSize;
@end

//----------------------------------------------------------------------------------------------------- ICScannerFeatureBoolean
/*!
	@class ICScannerFeatureBoolean
    @abstract ICScannerFeatureBoolean object is used to represent a property of a scanner functional unit whose value can be YES or NO.
    @discussion 
*/

@interface ICScannerFeatureBoolean : ICScannerFeature
{
@private
    id _bvProps;
}

/*!
    @property value
    @abstract ￼The value of this feature.

*/
@property(readwrite)  BOOL    value;
@end

//------------------------------------------------------------------------------------------------------ ICScannerFunctionalUnit
/*!
	@class ICScannerFunctionalUnit
    @abstract ICScannerFunctionalUnit is an abstract class that represents a scanner functiona unit. ImageCaptureCore defines three concrete subclasses of ICScannerFunctionalUnit: ICScannerFunctionalUnitFlatbed, ICScannerFunctionalUnitTransparency and ICScannerFunctionalUnitDocumentFeeder. ICScannerDevice creates instances of these concrete subclasses.
*/

@interface ICScannerFunctionalUnit : NSObject
{
@private
    id _fuProps;
}

/*!
    @property type
    @abstract ￼Functional unit type.

*/
@property(readonly)   ICScannerFunctionalUnitType   type;

/*!
    @property pixelDataType
    @abstract ￼The pixel data type.

*/
@property(readwrite)  ICScannerPixelDataType        pixelDataType;

/*!
    @property supportedBitDepths
    @abstract ￼Supported bit depths. The values in this set are valid values defined by ICScannerBitDepth.

*/
@property(readonly)	  NSIndexSet*                   supportedBitDepths;

/*!
    @property bitDepth
    @abstract ￼The bit depth to use when performing the final scan. This will always be one of the supported bit depths.

*/
@property(readwrite)  ICScannerBitDepth             bitDepth;

/*!
    @property supportedMeasurementUnits
    @abstract ￼Supported measurement units. The values in this set are valid values defined by ICScannerMeasurementUnit.

*/
@property(readonly)	  NSIndexSet*                   supportedMeasurementUnits;

/*!
    @property measurementUnit
    @abstract ￼Current measurement unit. This will always be one of the supported measurement units.

*/
@property(readwrite)  ICScannerMeasurementUnit      measurementUnit;

/*!
    @property supportedResolutions
    @abstract ￼Supported scan resolutions in DPI.

*/
@property(readonly)   NSIndexSet*                   supportedResolutions;

/*!
    @property preferredResolutions
    @abstract ￼Preferred scan resolutions in DPI.

*/
@property(readonly)   NSIndexSet*                   preferredResolutions;

/*!
    @property resolution
    @abstract ￼Current scan resolution. This will always be one of the supported resolution values.

*/
@property(readwrite)  NSUInteger                    resolution;

/*!
    @property supportedScaleFactors
    @abstract ￼Supported scale factors in percentage.

*/
@property(readonly)   NSIndexSet*                   supportedScaleFactors;

/*!
    @property preferredScaleFactors
    @abstract ￼Preferred scale factors in percentage.

*/
@property(readonly)   NSIndexSet*                   preferredScaleFactors;

/*!
    @property scaleFactor
    @abstract ￼Current scale factor. This will always be one of the supported scale factor values.

*/
@property(readwrite)  NSUInteger                    scaleFactor;

/*!
    @property vendorFeatures
    @abstract An array of objects of type ICScannerFeature.

*/
@property(readonly)   NSArray*                      vendorFeatures;

/*!
    @property scanArea
    @abstract ￼This property along with the scanAreaRotationAngle describes the area to be scanned.

*/
@property(readwrite)  NSRect                        scanArea;

/*!
    @property state
    @abstract ￼Indicates the current state of the functional unit.

*/
@property(readonly)   ICScannerFunctionalUnitState  state;

/*!
    @property scanInProgress
    @abstract ￼Indicates if a scan is in progress.

*/
@property(readonly)   BOOL                          scanInProgress;

/*!
    @property scanProgressPercentDone
    @abstract ￼Indicates percentage of scan completed.

*/
@property(readonly)   CGFloat                       scanProgressPercentDone;

/*!
    @property canPerformOverviewScan
    @abstract ￼Indicates if this functional unit can perfrom an overview scan. Not all functional units can perform an overview scan. For example, a document feeder or a sheet feeder unit cannot perform an overview scan.

*/
@property(readonly)   BOOL                          canPerformOverviewScan;

/*!
    @property overviewScanInProgress
    @abstract ￼Indicates if an overview scan is in progress.

*/
@property(readonly)   BOOL                          overviewScanInProgress;

/*!
    @property overviewImage
    @abstract ￼Overview scan image. This property will be NULL for functional units that do not support overview scans.

*/
@property(readonly)   CGImageRef                    overviewImage;

/*!
    @property overviewResolution
    @abstract ￼Overview image resolution. Value assigned to this will be contrained by resolutions allowed by the device.

*/
@property(readwrite)  NSUInteger                    overviewResolution;
@end

//----------------------------------------------------------------------------------------------- ICScannerFunctionalUnitFlatbed
/*!
	@class ICScannerFunctionalUnitFlatbed
    @abstract ICScannerFunctionalUnitFlatbed is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
    @discussion This represents the flatbed  unit on the scanner.
*/

@interface ICScannerFunctionalUnitFlatbed : ICScannerFunctionalUnit
{
@private
    id _fbProps;
}

/*!
    @property physicalSize
    @abstract ￼Physical size of the scan area in current measurement unit.

*/
@property(readonly) NSSize                          physicalSize;
@end

//------------------------------------------------------------------------------------------ ICScannerFunctionalUnitTransparency
/*!
	@class ICScannerFunctionalUnitTransparency
    @abstract ICScannerFunctionalUnitTransparency is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
    @discussion This represents the transparency unit on the scanner.
*/

@interface ICScannerFunctionalUnitTransparency : ICScannerFunctionalUnit
{
@private
    id _trProps;
}

/*!
    @property supportedFilmTypes
    @abstract ￼Supported fim types. The values in this set are valid values defined by ICScannerFilmType.

*/
@property(readonly)   NSIndexSet*                   supportedFilmTypes;

/*!
    @property filmType
    @abstract ￼Current film type. This will always be one of the supported film types.

*/
@property(readwrite)  ICScannerFilmType             filmType;

/*!
    @property physicalSize
    @abstract ￼Physical size of the scan area in current measurement unit.

*/
@property(readonly)   NSSize                        physicalSize;
@end

//---------------------------------------------------------------------------------------- ICScannerFunctionalUnitDocumentFeeder
/*!
	@class ICScannerFunctionalUnitDocumentFeeder
    @abstract ICScannerFunctionalUnitDocumentFeeder is a concrete subclass of ICScannerFunctionalUnit class. ICScannerDevice creates instances of this class.
    @discussion This represents the document feeder unit on the scanner.
*/

@interface ICScannerFunctionalUnitDocumentFeeder : ICScannerFunctionalUnit
{
@private
    id _dfProps;
}

/*!
    @property supportedSizes
    @abstract ￼Supported scan sizes.The values in this set are valid values defined by ICScannerDocumentSizeType.

*/
@property(readonly)   NSIndexSet*                   supportedSizes;

/*!
    @property preferredSizes
    @abstract ￼Preferred scan sizes.The values in this set are valid values defined by ICScannerDocumentSizeType.

*/
@property(readonly)   NSIndexSet*                   preferredSizes;

/*!
    @property size
    @abstract ￼Current scan size. This will always be one of the supported sizes.

*/
@property(readwrite)  ICScannerDocumentSizeType     size;

/*!
    @property supportsDuplexScanning
    @abstract ￼Indicates whether duplex scanning is supported.

*/
@property(readonly)   BOOL                          supportsDuplexScanning;

/*!
    @property duplexScanningEnabled
    @abstract ￼Indicates whether duplex scanning is enabled.

*/
@property(readwrite)  BOOL                          duplexScanningEnabled;
@end

//------------------------------------------------------------------------------------------------------------------------------
