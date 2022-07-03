/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibNmeaParser.hpp
 * Module:			NMEA sentence parser for FunSAPE++ Embedded Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_NMEA_PARSER_HPP
#define __FUNSAPE_LIB_NMEA_PARSER_HPP			__BUILD_TO_REPLACE__

// =============================================================================
// System file dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "..\funsapeLibGlobalDefines.hpp"
#if __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error [funsapeLibNmeaParser.hpp] Error 101 - Global definitions file (funsapeLibGlobalDefines.hpp) must be build __BUILD_TO_REPLACE__.
#endif

#include "main.h"

void blinkLed();

// -----------------------------------------------------------------------------
// Other header files ----------------------------------------------------------

// NONE

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// Macro-function definitions
// *INDENT-OFF*
// =============================================================================

// NONE

// *INDENT-ON*

// =============================================================================
// New data types
// =============================================================================

// -----------------------------------------------------------------------------
// Single variables ------------------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (logic values) -------------------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (small and finite lists) ---------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (large or expansible lists) ------------------------------------

typedef enum nmeaTalkerId_e : uint8_t
{
    NMEA_TALKER_ID_UNKNOWN					= 0,	// NO TALKER DETECTED
    NMEA_TALKER_ID_AB						= 1,	// AB - Independent AIS Base Station
    NMEA_TALKER_ID_AD						= 2,	// AD - Dependent AIS Base Station
    NMEA_TALKER_ID_AG						= 3,	// AG - Heading Track Controller (Autopilot) - General
    NMEA_TALKER_ID_AI						= 4,	// AI - Mobile Class A or B AIS Station
    NMEA_TALKER_ID_AN						= 5,	// AN - AIS Aids to Navigation Station
    NMEA_TALKER_ID_AP						= 6,	// AP - Heading Track Controller (Autopilot) - Magnetic
    NMEA_TALKER_ID_AR						= 7,	// AR - AIS Receiving Station
    NMEA_TALKER_ID_AS						= 8,	// AS - AIS Station (ITU_R M1371, “Limited Base Station’)
    NMEA_TALKER_ID_AT						= 9,	// AT - AIS Transmitting Station
    NMEA_TALKER_ID_AX						= 10,	// AX - AIS Simplex Repeater Station
    NMEA_TALKER_ID_BI						= 11,	// BI - Bilge Systems
    NMEA_TALKER_ID_BN						= 12,	// BN - Bridge Navigational Watch Alarm System
    NMEA_TALKER_ID_CA						= 13,	// CA - Central Alarm Management
    NMEA_TALKER_ID_CD						= 14,	// CD - Communications - Digital Selective Calling (DSC)
    NMEA_TALKER_ID_CR						= 15,	// CR - Communications - Data Receiver
    NMEA_TALKER_ID_CS						= 16,	// CS - Communications - Satellite
    NMEA_TALKER_ID_CT						= 17,	// CT - Communications - Radio-Telephone (MF/HF)
    NMEA_TALKER_ID_CV						= 18,	// CV - Communications - Radio-Telephone (VHF)
    NMEA_TALKER_ID_CX						= 19,	// CX - Communications - Scanning Receiver
    NMEA_TALKER_ID_DE						= 20,	// DE - DECCA Navigator
    NMEA_TALKER_ID_DF						= 21,	// DF - Direction Finder
    NMEA_TALKER_ID_DP						= 22,	// DP - Dynamic Position
    NMEA_TALKER_ID_DU						= 23,	// DU - Duplex Repeater Station
    NMEA_TALKER_ID_EC						= 24,	// EC - Electronic Chart System (ECS)
    NMEA_TALKER_ID_EI						= 25,	// EI - Electronic Chart Display & Information System (ECDIS)
    NMEA_TALKER_ID_EP						= 26,	// EP - Emergency Position Indicating Beacon (EPIRB)
    NMEA_TALKER_ID_ER						= 27,	// ER - Engine Room Monitoring Systems
    NMEA_TALKER_ID_FD						= 28,	// FD - Fire Door Controller/Monitoring Point
    NMEA_TALKER_ID_FE						= 29,	// FE - Fire Extinguisher System
    NMEA_TALKER_ID_FR						= 30,	// FR - Fire Detection Point
    NMEA_TALKER_ID_FS						= 31,	// FS - Fire Sprinkler System
    NMEA_TALKER_ID_GA						= 32,	// GA - Navigation Sattelite System Receivers - Galileo Positioning System
    NMEA_TALKER_ID_GB						= 33,	// GB - Navigation Sattelite System Receivers - BDS (BeiDou System)
    NMEA_TALKER_ID_GI						= 34,	// GI - Navigation Sattelite System Receivers - NavIC (IRNSS)
    NMEA_TALKER_ID_GL						= 35,	// GL - Navigation Sattelite System Receivers - GLONASS Receiver
    NMEA_TALKER_ID_GN						= 36,	// GN - Navigation Sattelite System Receivers - Global Navigation Satellite System (GNSS)
    NMEA_TALKER_ID_GP						= 37,	// GP - Navigation Sattelite System Receivers - Global Positioning System (GPS)
    NMEA_TALKER_ID_GQ						= 38,	// GQ - Navigation Sattelite System Receivers - QZSS
    NMEA_TALKER_ID_HC						= 39,	// HC - Heading Sensors - Compass, Magnetic
    NMEA_TALKER_ID_HD						= 40,	// HD - Hull Door Controller/Monitoring Panel
    NMEA_TALKER_ID_HE						= 41,	// HE - Heading Sensors - Gyro, North Seeking
    NMEA_TALKER_ID_HF						= 42,	// HF - Heading Sensors - Fluxgate
    NMEA_TALKER_ID_HN						= 43,	// HN - Heading Sensors - Gyro, Non-North Seeking
    NMEA_TALKER_ID_HS						= 44,	// HS - Hull Stress Monitoring
    NMEA_TALKER_ID_II						= 45,	// II - Integrated Instrumentation
    NMEA_TALKER_ID_IN						= 46,	// IN - Integrated Navigation
    NMEA_TALKER_ID_JA						= 47,	// JA - Automation - Alarm and Monitoring System (reserved for future use)
    NMEA_TALKER_ID_JB						= 48,	// JB - Automation - Reefer Monitoring System (reserved for future use)
    NMEA_TALKER_ID_JC						= 49,	// JC - Automation - Power Management System (reserved for future use)
    NMEA_TALKER_ID_JD						= 50,	// JD - Automation - Propulsion Control System (reserved for future use)
    NMEA_TALKER_ID_JE						= 51,	// JE - Automation - Engine Control Console (reserved for future use)
    NMEA_TALKER_ID_JF						= 52,	// JF - Automation - Propulsion Boiler (reserved for future use)
    NMEA_TALKER_ID_JG						= 53,	// JG - Automation - Auxiliary Boiler (reserved for future use)
    NMEA_TALKER_ID_JH						= 54,	// JH - Automation - Electronic Governor System (reserved for future use)
    NMEA_TALKER_ID_LC						= 55,	// LC - Loran C
    NMEA_TALKER_ID_MX						= 56,	// MX - Multiplexer
    NMEA_TALKER_ID_NL						= 57,	// NL - Navigation Light Controller
    NMEA_TALKER_ID_NV						= 58,	// NV - Night Vision
    NMEA_TALKER_ID_RA						= 59,	// RA - Radar and/or Radar Plotting
    NMEA_TALKER_ID_RB						= 60,	// RB - Record Book (reserved for future use)
    NMEA_TALKER_ID_RC						= 61,	// RC - Propulsion Machinery Including Remote Control
    NMEA_TALKER_ID_RI						= 62,	// RI - Rudder Angle Indicator (reserved for future use)
    NMEA_TALKER_ID_SA						= 63,	// SA - Physical Shore AIS Station
    NMEA_TALKER_ID_SC						= 64,	// SC - Steering Control System/Device (reserved for future use)
    NMEA_TALKER_ID_SD						= 65,	// SD - Sounder, depth
    NMEA_TALKER_ID_SG						= 66,	// SG - Steering Gear/Steering Engine
    NMEA_TALKER_ID_SN						= 67,	// SN - Electronic Positioning System, other/general
    NMEA_TALKER_ID_SS						= 68,	// SS - Sounder, scanning
    NMEA_TALKER_ID_TC						= 69,	// TC - Track Control System (reserved for future use)
    NMEA_TALKER_ID_TI						= 70,	// TI - Turn Rate Indicator
    NMEA_TALKER_ID_U1						= 71,	// U1 - User configured talker identifier 1
    NMEA_TALKER_ID_U2						= 72,	// U2 - User configured talker identifier 2
    NMEA_TALKER_ID_U3						= 73,	// U3 - User configured talker identifier 3
    NMEA_TALKER_ID_U4						= 74,	// U4 - User configured talker identifier 4
    NMEA_TALKER_ID_U5						= 75,	// U5 - User configured talker identifier 5
    NMEA_TALKER_ID_U6						= 76,	// U6 - User configured talker identifier 6
    NMEA_TALKER_ID_U7						= 77,	// U7 - User configured talker identifier 7
    NMEA_TALKER_ID_U8						= 78,	// U8 - User configured talker identifier 8
    NMEA_TALKER_ID_U9						= 79,	// U9 - User configured talker identifier 9
    NMEA_TALKER_ID_UP						= 80,	// UP - Microprocessor  Controller
    NMEA_TALKER_ID_VA						= 81,	// VA - VHF Data Exchange Systems - ASM
    NMEA_TALKER_ID_VD						= 82,	// VD - Velocity Sensors - Doppler, other/general
    NMEA_TALKER_ID_VM						= 83,	// VM - Velocity Sensors - Speed Log, Water, Magnetic
    NMEA_TALKER_ID_VR						= 84,	// VR - Voyage Data Recorder
    NMEA_TALKER_ID_VS						= 85,	// VS - VHF Data Exchange Systems - Satellite
    NMEA_TALKER_ID_VT						= 86,	// VT - VHF Data Exchange Systems - Terrestrial
    NMEA_TALKER_ID_VW						= 87,	// VW - Velocity Sensors - Speed Log, Water Mechanical
    NMEA_TALKER_ID_WD						= 88,	// WD - Watertight Door Controller/Monitoring Panel
    NMEA_TALKER_ID_WI						= 89,	// WI - Weather Instruments
    NMEA_TALKER_ID_WL						= 90,	// WL - Water Level Detection Systems
    NMEA_TALKER_ID_YX						= 91,	// YX - Transducer
    NMEA_TALKER_ID_ZA						= 92,	// ZA - Timekeepers, Time/Date -Atomics Clock
    NMEA_TALKER_ID_ZC						= 93,	// ZC - Timekeepers, Time/Date -Chronometer
    NMEA_TALKER_ID_ZQ						= 94,	// ZQ - Timekeepers, Time/Date -Quartz
    NMEA_TALKER_ID_ZV						= 95,	// ZV - Timekeepers, Time/Date -Radio Update
    NMEA_TALKER_ID_PROPRIETARY				= 255	// P - Proprietary Code
} nmeaTalkerId_e;

typedef enum nmeaSentenceType_e : uint8_t
{
    NMEA_SENTENCE_TYPE_UNKNOWN			= 0,			// NO SENTENCE DETECTED
    NMEA_SENTENCE_TYPE_AAM				= 1,			// AAM - Waypoint Arrival Alarm
    NMEA_SENTENCE_TYPE_ALM				= 2,			// ALM - GPS Almanac Data
    NMEA_SENTENCE_TYPE_APA				= 3,			// APA - Autopilot Sentence "A"
    NMEA_SENTENCE_TYPE_APB				= 4,			// APB - Autopilot Sentence "B"
    NMEA_SENTENCE_TYPE_ASD				= 5,			// ASD - Autopilot System Data
    NMEA_SENTENCE_TYPE_BEC				= 6,			// BEC - Bearing & Distance to Waypoint, Dead Reckoning
    NMEA_SENTENCE_TYPE_BOD				= 7,			// BOD - Bearing, Origin to Destination
    NMEA_SENTENCE_TYPE_BWC				= 8,			// BWC - Bearing & Distance to Waypoint, Great Circle
    NMEA_SENTENCE_TYPE_BWR				= 9,			// BWR - Bearing & Distance to Waypoint, Rhumb Line
    NMEA_SENTENCE_TYPE_BWW				= 10,			// BWW - Bearing, Waypoint to Waypoint
    NMEA_SENTENCE_TYPE_DBT				= 11,			// DBT - Depth Below Transducer
    NMEA_SENTENCE_TYPE_DCN				= 12,			// DCN - Decca Position
    NMEA_SENTENCE_TYPE_DPT				= 13,			// DPT - Depth
    NMEA_SENTENCE_TYPE_DTM				= 14,			// DTM - Datum being used
    NMEA_SENTENCE_TYPE_FSI				= 15,			// FSI - Frequency Set Information
    NMEA_SENTENCE_TYPE_GGA				= 16,			// GGA - Global Positioning System Fix Data
    NMEA_SENTENCE_TYPE_GLC				= 17,			// GLC - Geographic Position, Loran-C
    NMEA_SENTENCE_TYPE_GLL				= 18,			// GLL - Geographic Position, Latitude/Longitude
    NMEA_SENTENCE_TYPE_GRS				= 19,			// GRS - GPS Range Residuals
    NMEA_SENTENCE_TYPE_GSA				= 20,			// GSA - GPS DOP and Active Satellites
    NMEA_SENTENCE_TYPE_GST				= 21,			// GST - GPS Pseudorange Noise Statistics
    NMEA_SENTENCE_TYPE_GSV				= 22,			// GSV - GPS Satellites in View
    NMEA_SENTENCE_TYPE_GXA				= 23,			// GXA - TRANSIT Position
    NMEA_SENTENCE_TYPE_HDG				= 24,			// HDG - Heading, Deviation & Variation
    NMEA_SENTENCE_TYPE_HDT				= 25,			// HDT - Heading, True
    NMEA_SENTENCE_TYPE_HSC				= 26,			// HSC - Heading Steering Command
    NMEA_SENTENCE_TYPE_LCD				= 27,			// LCD - Loran-C Signal Data
    NMEA_SENTENCE_TYPE_MSK				= 28,			// MSK - send control for a beacon receiver
    NMEA_SENTENCE_TYPE_MSS				= 29,			// MSS - Beacon receiver status information.
    NMEA_SENTENCE_TYPE_MTA				= 30,			// MTA - Air Temperature (to be phased out)
    NMEA_SENTENCE_TYPE_MTW				= 31,			// MTW - Water Temperature
    NMEA_SENTENCE_TYPE_MWD				= 32,			// MWD - Wind Direction
    NMEA_SENTENCE_TYPE_MWV				= 33,			// MWV - Wind Speed and Angle
    NMEA_SENTENCE_TYPE_OLN				= 34,			// OLN - Omega Lane Numbers
    NMEA_SENTENCE_TYPE_OSD				= 35,			// OSD - Own Ship Data
    NMEA_SENTENCE_TYPE_R00				= 36,			// R00 - Waypoint active route (not standard)
    NMEA_SENTENCE_TYPE_RMA				= 37,			// RMA - Recommended Minimum Specific Loran-C Data
    NMEA_SENTENCE_TYPE_RMB				= 38,			// RMB - Recommended Minimum Navigation Information
    NMEA_SENTENCE_TYPE_RMC				= 39,			// RMC - Recommended Minimum Specific GPS/TRANSIT Data
    NMEA_SENTENCE_TYPE_ROT				= 40,			// ROT - Rate of Turn
    NMEA_SENTENCE_TYPE_RPM				= 41,			// RPM - Revolutions
    NMEA_SENTENCE_TYPE_RSA				= 42,			// RSA - Rudder Sensor Angle
    NMEA_SENTENCE_TYPE_RSD				= 43,			// RSD - RADAR System Data
    NMEA_SENTENCE_TYPE_RTE				= 44,			// RTE - Routes
    NMEA_SENTENCE_TYPE_SFI				= 45,			// SFI - Scanning Frequency Information
    NMEA_SENTENCE_TYPE_STN				= 46,			// STN - Multiple Data ID
    NMEA_SENTENCE_TYPE_TRF				= 47,			// TRF - Transit Fix Data
    NMEA_SENTENCE_TYPE_TTM				= 48,			// TTM - Tracked Target Message
    NMEA_SENTENCE_TYPE_VBW				= 49,			// VBW - Dual Ground/Water Speed
    NMEA_SENTENCE_TYPE_VDR				= 50,			// VDR - Set and Drift
    NMEA_SENTENCE_TYPE_VHW				= 51,			// VHW - Water Speed and Heading
    NMEA_SENTENCE_TYPE_VLW				= 52,			// VLW - Distance Traveled through the Water
    NMEA_SENTENCE_TYPE_VPW				= 53,			// VPW - Speed, Measured Parallel to Wind
    NMEA_SENTENCE_TYPE_VTG				= 54,			// VTG - Track Made Good and Ground Speed
    NMEA_SENTENCE_TYPE_WCV				= 55,			// WCV - Waypoint Closure Velocity
    NMEA_SENTENCE_TYPE_WNC				= 56,			// WNC - Distance, Waypoint to Waypoint
    NMEA_SENTENCE_TYPE_WPL				= 57,			// WPL - Waypoint Location
    NMEA_SENTENCE_TYPE_XDR				= 58,			// XDR - Transducer Measurements
    NMEA_SENTENCE_TYPE_XTC				= 59,			// XTC - cross track error
    NMEA_SENTENCE_TYPE_XTE				= 60,			// XTE - Cross-Track Error, Measured
    NMEA_SENTENCE_TYPE_XTR				= 61,			// XTR - Cross-Track Error, Dead Reckoning
    NMEA_SENTENCE_TYPE_ZDA				= 62,			// ZDA - Time & Date
    NMEA_SENTENCE_TYPE_ZFO				= 63,			// ZFO - UTC & Time from Origin Waypoint
    NMEA_SENTENCE_TYPE_ZTG				= 64,			// ZTG - UTC & Time to Destination Waypoint
} nmeaSentenceType_e;

/*

class FloatingPoint
{
	// Constructor
public:
	FloatingPoint(char *asciiSequence);
	FloatingPoint(float floatNumber);
	FloatingPoint();
	~FloatingPoint();


	FloatingPoint operator+(const FloatingPoint &b) {
		FloatingPoint aux;
		box.length = this->length + b.length;
		box.breadth = this->breadth + b.breadth;
		box.height = this->height + b.height;
		return box;
	}



	// Methods
public:
	void set(char *asciiSequence);
	void set(float floatNumber);

	// Properties
private:
	uint64_t	_value;
	int8_t		_power					: 7;
	bool		_negative				: 1;
};
*/

typedef union nmeaFloat_s
{
    uint64_t		internalValue;
    struct
    {
        bool		signal					: 1;	// 0 to positive, 1 to negative
        uint64_t	shiftedValue			: 58;	// Float value shifted (base 10) until it becames an integer
        int8_t		pointPosition			: 5;	// Decimal point position
    };
} nmeaFloat_s;

typedef struct nmeaDate_s
{
    uint8_t		day						: 5;	// 1 to 31, 0 to undefined
    uint8_t		month					: 4;	// 1 to 12, 0 to undefined
    uint8_t		year					: 7;	// 0 to 99
} nmeaDate_s;

typedef struct nmeaTime_s
{
    uint8_t		hours					: 5;	// 0 to 23
    uint8_t		minutes					: 6;	// 0 to 59
    uint8_t		seconds					: 6;	// 0 to 59
    uint16_t	miliseconds				: 10;	// 0 to 999
} nmeaTime_s;

typedef struct nmeaLatitude_s
{
    uint8_t		degrees					: 7;	// 0 to 90
    uint8_t		minutesInteger			: 6;	// 0 to 59
    uint16_t	minutesDecimal			: 16;	// 0 to 99999
    bool		eastWest				: 1;	// 0 = East, 1 = West
} nmeaLatitude_s;

typedef struct nmeaMagDeclination_s
{
    uint16_t	degreesInteger			: 9;	// 0 to 360
    uint16_t	degreesDecimal			: 10;	// 0 to 999
    bool		eastWest				: 1;	// 0 = East, 1 = West
} nmeaMagDeclination_s;

typedef struct nmeaLongitude_s
{
    uint8_t		degreesInteger			: 8;	// 0 to 180
    uint8_t		minutesInteger			: 6;	// 0 to 59
    uint16_t	minutesDecimal			: 16;	// 0 to 99999
    bool		northSouth				: 1;	// 0 = North, 1 = South
} nmeaLongitude_s;

typedef struct nmeaSatInfo_s
{
    int			nr;
    int			elevation;
    int			azimuth;
    int			snr;
} nmeaSatInfo_s;

typedef enum nmeaModeFaa_e : char
{
    MINMEA_FAA_MODE_AUTONOMOUS			= 'A',
    MINMEA_FAA_MODE_DIFFERENTIAL		= 'D',
    MINMEA_FAA_MODE_ESTIMATED			= 'E',
    MINMEA_FAA_MODE_MANUAL				= 'M',
    MINMEA_FAA_MODE_SIMULATED			= 'S',
    MINMEA_FAA_MODE_NOT_VALID			= 'N',
    MINMEA_FAA_MODE_PRECISE				= 'P',
} nmeaModeFaa_e;

// typedef struct timespec {
// 	time_t tv_sec;
// 	long tv_nsec;
// };

typedef struct nmeaSentenceRmc_s
{
    char			course[15];
    char			date[15];
    char			latitudeValue[15];
    char			latitudeIndicator[15];
    char			longitudeValue[15];
    char			longitudeIndicator[15];
//    char			magDeclination[15];
    char			speed[15];
    char			time[15];
    char			valid[15];
    char			mode[15];
    /*
        nmeaFloat_s				course;
        nmeaDate_s				date;
        nmeaLatitude_s			latitude;
        nmeaLongitude_s			longitude;
        nmeaFloat_s				speed;
        nmeaTime_s				time;
        bool					valid;
        nmeaMagDeclination_s	magDeclination;
    */
} nmeaSentenceRmc_s;

typedef struct nmeaSentenceGga_s
{
    nmeaDate_s			date;
    nmeaTime_s			time;
    nmeaLatitude_s		latitude;
    nmeaLongitude_s		longitude;
    int					fix_quality;
    int					satellites_tracked;
    nmeaFloat_s			hdop;
    nmeaFloat_s			altitude;
    char				altitude_units;
    nmeaFloat_s			height;
    char				height_units;
    nmeaFloat_s			dgps_age;
} nmeaSentenceGga_s;

typedef struct nmeaSentenceGll_s
{
    nmeaLatitude_s		latitude;
    nmeaLongitude_s		longitude;
    nmeaTime_s			time;
    char				status;
    char				mode;
} nmeaSentenceGll_s;

typedef struct nmeaSentenceGst_s
{
    nmeaTime_s		time;
    nmeaFloat_s		rms_deviation;
    nmeaFloat_s		semi_major_deviation;
    nmeaFloat_s		semi_minor_deviation;
    nmeaFloat_s		semi_major_orientation;
    nmeaFloat_s		latitude_error_deviation;
    nmeaFloat_s		longitude_error_deviation;
    nmeaFloat_s		altitude_error_deviation;
} nmeaSentenceGst_s;

typedef struct nmeaSentenceGsa_s
{
    char			mode;
    int				fix_type;
    int				sats[12];
    nmeaFloat_s		pdop;
    nmeaFloat_s		hdop;
    nmeaFloat_s		vdop;
} nmeaSentenceGsa_s;

typedef struct nmeaSentenceGsv_s
{
    int				total_msgs;
    int				msg_nr;
    int				total_sats;
    nmeaSatInfo_s	sats[4];
} nmeaSentenceGsv_s;

typedef struct nmeaSentenceVtg_s
{
    nmeaFloat_s		true_track_degrees;
    nmeaFloat_s		magnetic_track_degrees;
    nmeaFloat_s		speed_knots;
    nmeaFloat_s		speed_kph;
    nmeaModeFaa_e	faa_mode;
} nmeaSentenceVtg_s;

typedef struct nmeaSentenceZda_s
{
    nmeaTime_s		time;
    nmeaDate_s		date;
    int				hour_offset;
    int				minute_offset;
} nmeaSentenceZda_s;

// -----------------------------------------------------------------------------
// Enumerations (algebraic operated list elements) -----------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (bitwise operated flags) ---------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Enumerations (bitwise operated flags) ---------------------------------------

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// NmeaParser - Class declaration
// =============================================================================

class NmeaParser
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

private:
    typedef enum nmeaDecoderState_e : uint16_t
    {
        NMEA_STATE_IDLE									= 0x0000,
        NMEA_STATE_GETTING_TALKER						= 0x0001,
        NMEA_STATE_GETTING_SENTENCE_TYPE				= 0x0002,
        NMEA_STATE_GETTING_DATA							= 0x0003,
        NMEA_STATE_GETTING_CHECKSUM						= 0x0004,
        NMEA_STATE_GETTING_TERMINATOR_CR				= 0x0005,
        NMEA_STATE_GETTING_TERMINATOR_LF				= 0x0006,
        NMEA_STATE_FRAME_COMPLETE						= 0x0007,
        NMEA_STATE_PROCESSING_DATA						= 0x0008,
        NMEA_STATE_DATA_READY							= 0x0009,

        NMEA_STATE_GETTING_GGA_UTC_TIME					= 0x0800,
        NMEA_STATE_GETTING_GGA_LATITUDE					= 0x0801,
        NMEA_STATE_GETTING_GGA_NS_INDICATOR				= 0x0802,
        NMEA_STATE_GETTING_GGA_LONGITUDE				= 0x0803,
        NMEA_STATE_GETTING_GGA_EW_INDICATOR				= 0x0804,
        NMEA_STATE_GETTING_GGA_POSITION_FIX_INDICATOR	= 0x0805,
        NMEA_STATE_GETTING_GGA_SATELLITES_USED			= 0x0806,
        NMEA_STATE_GETTING_GGA_HORIZ_DILU_PRECISION		= 0x0807,
        NMEA_STATE_GETTING_GGA_MSL_ALTITUDE				= 0x0808,
        NMEA_STATE_GETTING_GGA_MSL_ALTITUDE_UNITS		= 0x0809,
        NMEA_STATE_GETTING_GGA_GEOID_SEPARATION			= 0x080A,
        NMEA_STATE_GETTING_GGA_GEOID_SEPARATION_UNITS	= 0x080B,
        NMEA_STATE_GETTING_GGA_AGE_DIFF_CORR			= 0x080C,
        NMEA_STATE_GETTING_GGA_DIFF_REF_STATION_ID		= 0x080D,

        NMEA_STATE_GETTING_RMC_UTC_TIME					= 0x1200,
        NMEA_STATE_GETTING_RMC_STATUS					= 0x1201,
        NMEA_STATE_GETTING_RMC_LATITUDE					= 0x1202,
        NMEA_STATE_GETTING_RMC_NS_INDICATOR				= 0x1203,
        NMEA_STATE_GETTING_RMC_LONGITUDE				= 0x1204,
        NMEA_STATE_GETTING_RMC_EW_INDICATOR				= 0x1205,
        NMEA_STATE_GETTING_RMC_SPEED_OVER_GROUND		= 0x1206,
        NMEA_STATE_GETTING_RMC_COURSE_OVER_GROUND		= 0x1207,
        NMEA_STATE_GETTING_RMC_DATE						= 0x1208,
        NMEA_STATE_GETTING_RMC_MODE						= 0x1209,

    } nmeaDecoderState_e;

    // -------------------------------------------------------------------------
    // Operators overloading ---------------------------------------------------

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    NmeaParser(uint8_t maxSentenceSize = 100, bool checksumEnabled = true);
    ~NmeaParser(void);

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------

public:
    //     ////////////////////    CONFIGURATION	 ////////////////////     //
    //    	Configures callback function
    bool	setDataReadyCallback(void callbackFunction(void));

    //     /////////////////     PARSER OUTPUT DATA	 /////////////////     //
    nmeaTalkerId_e		getTalkerId(void);
    nmeaSentenceType_e	getSentenceType(void);

    //     /////////////////     STATUS AND CONTROL	 /////////////////     //

    //    	Prepare to read new data, flusing old data from last NMEA sentence
    bool	startToReceiveData(void);

    //    	Informs if the parser can receive data to append in the internal buffer
    bool	isClearToReceiveData(void);

    //    	Pushes data into internal buffer
    bool	pushData(uint8_t data);

    //    	Informs if a full sentence was read, so the sentence processing can be started
    bool	isReadyToProcessData(void);

    //    	Start to process the NMEA sentece stored in the internal buffer
    bool	startToDecodeData(void);

    //    	Informs if the process is finished, so new decoded data is available
    bool	isNewDataReady(void);

    //    	Cancel the entire process, flushing data and returning to IDLE STATE
    bool	cancelProcess(void);

    //     ///////////////////     ERROR HANDLING	 ///////////////////     //

    //    	Returns error state from last operation
    error_e	getLastError(void);

private:
    //     //////////////    SENTENCE PARSER FUNCTIONS	 //////////////     //
    bool	_getField(char * field);
    bool	_scanSentence(char *format);
    bool	_parseSentenceRmc(void);
    bool	_parseSentenceAam(void);			// TODO Implement  this function
    bool	_parseSentenceAlm(void);			// TODO Implement  this function
    bool	_parseSentenceApa(void);			// TODO Implement  this function
    bool	_parseSentenceApb(void);			// TODO Implement  this function
    bool	_parseSentenceAsd(void);			// TODO Implement  this function
    bool	_parseSentenceBec(void);			// TODO Implement  this function
    bool	_parseSentenceBod(void);			// TODO Implement  this function
    bool	_parseSentenceBwc(void);			// TODO Implement  this function
    bool	_parseSentenceBwr(void);			// TODO Implement  this function
    bool	_parseSentenceBww(void);			// TODO Implement  this function
    bool	_parseSentenceDbt(void);			// TODO Implement  this function
    bool	_parseSentenceDcn(void);			// TODO Implement  this function
    bool	_parseSentenceDpt(void);			// TODO Implement  this function
    bool	_parseSentenceDtm(void);			// TODO Implement  this function
    bool	_parseSentenceFsi(void);			// TODO Implement  this function
    bool	_parseSentenceGga(void);			// TODO Implement  this function
    bool	_parseSentenceGlc(void);			// TODO Implement  this function
    bool	_parseSentenceGll(void);			// TODO Implement  this function
    bool	_parseSentenceGrs(void);			// TODO Implement  this function
    bool	_parseSentenceGsa(void);			// TODO Implement  this function
    bool	_parseSentenceGst(void);			// TODO Implement  this function
    bool	_parseSentenceGsv(void);			// TODO Implement  this function
    bool	_parseSentenceGxa(void);			// TODO Implement  this function
    bool	_parseSentenceHdg(void);			// TODO Implement  this function
    bool	_parseSentenceHdt(void);			// TODO Implement  this function
    bool	_parseSentenceHsc(void);			// TODO Implement  this function
    bool	_parseSentenceLcd(void);			// TODO Implement  this function
    bool	_parseSentenceMsk(void);			// TODO Implement  this function
    bool	_parseSentenceMss(void);			// TODO Implement  this function
    bool	_parseSentenceMta(void);			// TODO Implement  this function
    bool	_parseSentenceMtw(void);			// TODO Implement  this function
    bool	_parseSentenceMwd(void);			// TODO Implement  this function
    bool	_parseSentenceMwv(void);			// TODO Implement  this function
    bool	_parseSentenceOln(void);			// TODO Implement  this function
    bool	_parseSentenceOsd(void);			// TODO Implement  this function
    bool	_parseSentenceR00(void);			// TODO Implement  this function
    bool	_parseSentenceRma(void);			// TODO Implement  this function
    bool	_parseSentenceRmb(void);			// TODO Implement  this function
    bool	_parseSentenceRot(void);			// TODO Implement  this function
    bool	_parseSentenceRpm(void);			// TODO Implement  this function
    bool	_parseSentenceRsa(void);			// TODO Implement  this function
    bool	_parseSentenceRsd(void);			// TODO Implement  this function
    bool	_parseSentenceRte(void);			// TODO Implement  this function
    bool	_parseSentenceSfi(void);			// TODO Implement  this function
    bool	_parseSentenceStn(void);			// TODO Implement  this function
    bool	_parseSentenceTrf(void);			// TODO Implement  this function
    bool	_parseSentenceTtm(void);			// TODO Implement  this function
    bool	_parseSentenceVbw(void);			// TODO Implement  this function
    bool	_parseSentenceVdr(void);			// TODO Implement  this function
    bool	_parseSentenceVhw(void);			// TODO Implement  this function
    bool	_parseSentenceVlw(void);			// TODO Implement  this function
    bool	_parseSentenceVpw(void);			// TODO Implement  this function
    bool	_parseSentenceVtg(void);			// TODO Implement  this function
    bool	_parseSentenceWcv(void);			// TODO Implement  this function
    bool	_parseSentenceWnc(void);			// TODO Implement  this function
    bool	_parseSentenceWpl(void);			// TODO Implement  this function
    bool	_parseSentenceXdr(void);			// TODO Implement  this function
    bool	_parseSentenceXtc(void);			// TODO Implement  this function
    bool	_parseSentenceXte(void);			// TODO Implement  this function
    bool	_parseSentenceXtr(void);			// TODO Implement  this function
    bool	_parseSentenceZda(void);			// TODO Implement  this function
    bool	_parseSentenceZfo(void);			// TODO Implement  this function
    bool	_parseSentenceZtg(void);			// TODO Implement  this function

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties  -------------------------------------------------------------

public:
    //     ///////////////////////     STATUS     ///////////////////////     //
    bool				_clearToReceiveData				: 1;
    bool				_initialized					: 1;
    error_e				_lastError;
    bool				_newDataAvailable				: 1;
    bool				_readyToProcessData				: 1;

    //     ////////////////////    CONFIGURATION	 ////////////////////     //
    bool				_callbackFunctionEnable			: 1;
    bool				_checksumEnabled				: 1;
    void	(* _dataReadyCallbackFunction)(void);

    //     /////////////////////    BUFFER DATA     /////////////////////     //
    uint8_t				*_sentenceData;
    uint8_t				_sentenceIndex;
    uint8_t				_sentenceLength;
    uint8_t				_sentenceMaxSize;

    //     ////////////////    DECODED SENTENCE DATA     ////////////////     //
    nmeaSentenceType_e	_decodedSentenceType;
    nmeaTalkerId_e		_decodedTalkerId;
    nmeaSentenceRmc_s	_sentenceRmc;
//    bool				_proprietarySentence					: 1;
//    bool				_locked							: 1;

    //     ///////////////////////    CONTROL     ///////////////////////     //
    uint8_t				_fieldLength;
    nmeaDecoderState_e	_state;

private:

}; // class NmeaParser

// =============================================================================
// NmeaParser - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// NmeaParser - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

/*
// Calculate raw sentence checksum. Does not check sentence integrity.
uint8_t minmea_checksum(const char *sentence);
// Check sentence validity and checksum. Returns true for valid sentences.
bool minmea_check(const char *sentence, bool strict);
// Determine talker identifier.
bool minmea_talker_id(char talker[3], const char *sentence);
// Determine sentence identifier.
nmeaSentenceType_e minmea_sentence_id(const char *sentence, bool strict);
// Scanf-like processor for NMEA sentences. Supports the following formats:
// c - single character (char *)
// d - direction, returned as 1/-1, default 0 (int *)
// f - fractional, returned as value + scale (int *, int *)
// i - decimal, default zero (int *)
// s - string (char *)
// t - talker identifier and type (char *)
// T - date/time stamp (int *, int *, int *)
// Returns true on success. See library source code for details.
bool minmea_scan(const char *sentence, const char *format, ...);
// Parse a specific type of sentence. Return true on success.
bool minmea_parse_rmc(nmeaSentenceRmc_s *frame, const char *sentence);
bool minmea_parse_gga(nmeaSentenceGga_s *frame, const char *sentence);
bool minmea_parse_gsa(nmeaSentenceGsa_s *frame, const char *sentence);
bool minmea_parse_gll(nmeaSentenceGll_s *frame, const char *sentence);
bool minmea_parse_gst(nmeaSentenceGst_s *frame, const char *sentence);
bool minmea_parse_gsv(nmeaSentenceGsv_s *frame, const char *sentence);
bool minmea_parse_vtg(nmeaSentenceVtg_s *frame, const char *sentence);
bool minmea_parse_zda(nmeaSentenceZda_s *frame, const char *sentence);
// Convert GPS UTC date/time representation to a UNIX timestamp.
// int minmea_gettime(struct timespec *ts, const nmeaDate_s *date, const nmeaTime_s *time_);

// =============================================================================
// General inline functions definitions
// =============================================================================

// Rescale a fixed-point value to a different scale. Rounds towards zero.
static inline int32_t minmea_rescale(nmeaFloat_s *f, int32_t new_scale)
{
	if (f->scale == 0) {
		return 0;
	}
	if (f->scale == new_scale) {
		return f->value;
	}
	if (f->scale > new_scale) {
		return (f->value + ((f->value > 0) - (f->value < 0)) * f->scale / new_scale / 2) / (f->scale / new_scale);
	} else {
		return f->value * (new_scale / f->scale);
	}
}

// Convert a fixed-point value to a floating-point value.
// Returns NaN for "unknown" values.
// static inline float minmea_tofloat(nmeaFloat_s *f)
// {
// 	if (f->scale == 0) {
// 		return NAN;
// 	}
// 	return (float) f->value / (float) f->scale;
// }

// Convert a raw coordinate to a floating point DD.DDD... value.
// Returns NaN for "unknown" values.
// static inline float minmea_tocoord(nmeaFloat_s *f)
// {
// 	if (f->scale == 0) {
// 		return NAN;
// 	}
// 	int_least32_t degrees = f->value / (f->scale * 100);
// 	int_least32_t minutes = f->value % (f->scale * 100);
// 	return (float) degrees + (float) minutes / (60 * f->scale);
// }
*/
#endif // __FUNSAPE_LIB_NMEA_PARSER_HPP
