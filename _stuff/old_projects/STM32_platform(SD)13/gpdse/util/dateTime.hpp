/* =============================================================================
 * Project:		GPSDE++ AVR Library
 * File name:	dateTime.hpp
 * Module:		Date and Time definitions for GPDSE++ Library project
 * Authors:		Leandro Schwarz
 *				Hazael dos Santos Batista
 * Build:		1002
 * Date:		June 06, 2018
 * ========================================================================== */

#ifndef __DATE_TIME_HPP
#define __DATE_TIME_HPP 1002

// =============================================================================
// Dependencies
// =============================================================================

// Global definitions file
#include "..\globalDefines.hpp"
#if __GLOBAL_DEFINES_HPP != 1002
#	error	[dateTime.hpp] Error 101 - Global definitions file (globalDefines.hpp) must be build 1002.
#endif

// Header files
/* NONE */

// =============================================================================
// Undefining previous definitions
// =============================================================================

/* NONE */

// =============================================================================
// Constants
// =============================================================================

/* NONE */

// =============================================================================
// Macro-functions
// =============================================================================

/* NONE */

// =============================================================================
// New data types
// =============================================================================

typedef enum month_t {
	MONTH_UNDEFINED	= 0,
	MONTH_JANUARY	= 1,
	MONTH_FEBRUARY	= 2,
	MONTH_MARCH		= 3,
	MONTH_APRIL		= 4,
	MONTH_MAY		= 5,
	MONTH_JUNE		= 6,
	MONTH_JULY		= 7,
	MONTH_AUGUST	= 8,
	MONTH_SEPTEMBER	= 9,
	MONTH_OCTOBER	= 10,
	MONTH_NOVEMBER	= 11,
	MONTH_DECEMBER	= 12
} month_t;

typedef enum utcTimeZone_e {
	UTC_UNDEFINED		= 0,	// UNDEFINED, used to test if the variables was previously seted.
	UTC_MINUS_1200		= 1,	// USA (Baker Island, Howland Island)
	UTC_MINUS_1100		= 2,	// New Zealand (Niu), USA (Jarvis Island, Kingman Reef, Midway Atoll, Palmyra Atoll)
	UTC_MINUS_1000		= 3,	// France (French Poynesia), New Zealand (Cook Islands), USA (Hawaii, Johnston Atoll)
	UTC_MINUS_0930		= 4,	// France (Marquesas Islands)
	UTC_MINUS_0900		= 5,	// France (Gambier Islands), USA (Alaska)
	UTC_MINUS_0800		= 6,	// Canada (British Columbia, Yukon), France (Clipperton Island), USA (Pacific Time Zone)
	UTC_MINUS_0700		= 7,	// Canada (Alberta, Nortwest Territories), Mexico (Chinhuahua, Nayarit, Sinaloa, Sonora), USA (Mountain Time Zone)
	UTC_MINUS_0600		= 8,	// Belize, Canada (Central Time Zone), Chile (Easter Island), Costa Rica, El Salvador, Guatemala, Honduras, Mexico, USA (Central Time Zone)
	UTC_MINUS_0500		= 9,	// Bahamas, Brazil (Acre, Amazonas - western part), Colombia, Cuba, Ecuador, Haiti, Jamaica, Panama, Peru, USA (Esatern Time Zone)
	UTC_MINUS_0400		= 10,	// Antigua e Barbuda, Barbados, Bolivia, Brazil (Amazonas, Mato Grosso, Mato Grosso do Sul, Rondonia, Roraima), Canada (Atlantic Time Zone), Chile, Dominica, Guyana, Paraguay, Venezuela
	UTC_MINUS_0330		= 11,	// Canada (Newfoundland)
	UTC_MINUS_0300		= 12,	// Argentina, Brasil (Brazilia Official Timezone), Suriname, Uruguay
	UTC_MINUS_0230		= 13,	// St. John's
	UTC_MINUS_0200		= 14,	// Brazil (Fernando de Noronha), United Kingdom (South Georgia, South Sandwich Islands)
	UTC_MINUS_0100		= 15,	// Cape Verde, Portugal (Azores)
	UTC_EQUAL_0000		= 16,	// Burkina Faso, Cote d'Ivoire, Gambia, Ghana, Guinea, Guinea-Bissau, Iceland, Ireland, Liberia, Mali, Mauritania, Marocco, Portugal, Senegal, Sierra Leone, Togo, United Kingdom, Western Sahara
	UTC_PLUS_0100		= 17,	// Albania, Algeria, Andorra, Angola, Austria, Belgium, Benin, Bosnia and Herzegovina, Cameroon, Central African Republic, Chad, Congo, Croatia, Czech Republic, Denmark, France, Gabon, Gemany, Hungary, Italy, Kosovo, Liechtenstein, Luxembourg, Macedonia, Malta, Monaco, Montenegro, Netherlands, Niger, Nigeria, Poland, San Marino, Serbia,  Slovakia, Slovenia, Spain, Sweeden, Switzerland, Tunisia, Vatican City
	UTC_PLUS_0200		= 18,	// Botswana, Bulgaria, Burundi, Cyprus, Egypt, Estonia, Finland, Greece, Israel, Jordan, Latvia, Lebanon, Lesotho, Lithuania, Libya, Malawi, Moldova, Mozambique, Namibia, State of Palestine, Romania, Rwanda, South Africa, Sudan, Swaziland, Syria, Ukraine, Zambia, Zimbabwe
	UTC_PLUS_0300		= 19,	// Bahrain, Belarus, Comoros, Djibouti, Eritrea, Iraq, Kenya, Kuwait, Madagascar, Qatar, Russia (Moscow Time), Saudi Arabia, Somalia, South Sudan, Tanzania, Turkey, Uganda, Yemen
	UTC_PLUS_0330		= 20,	// Iran
	UTC_PLUS_0400		= 21,	// Armenia, Azerbaijan, Mauritius, Oman, Russia (Samara Time), Seychelles, United Arab Emirates
	UTC_PLUS_0430		= 22,	// Afghanistan
	UTC_PLUS_0500		= 23,	// Maldives, Pakistan, Russia (Yekaterinburg Time), Tajikistan, Turkmenistan, Uzbekistan
	UTC_PLUS_0530		= 24,	// India, Sri Lanka
	UTC_PLUS_0545		= 25,	// Nepal
	UTC_PLUS_0600		= 26,	// Bangladesh, Bhutan, Kazakhstan, Kyrgyzstan, Russia (Omsk Time), United Kingdom (British Indian Ocean Territory)
	UTC_PLUS_0630		= 27,	// Myanmar
	UTC_PLUS_0700		= 28,	// Cambodia, Laos, Mongolia, Russia (Krasnoyarsk Time), Thailand, Vietnam
	UTC_PLUS_0800		= 29,	// Brunei, China, Malaysia, Philippines, Russia (Irkutsk Time), Singapore, Taiwan
	UTC_PLUS_0830		= 30,	// North Korea
	UTC_PLUS_0845		= 31,	// Australia (Eucla)
	UTC_PLUS_0900		= 32,	// Japan, South Korea, Palau, Russia (Amur, Siberia), Timor-Leste
	UTC_PLUS_0930		= 33,	// Australia (Broken Hill, New South Wales, Northern Territory, South Australia)
	UTC_PLUS_1000		= 34,	// Australia (Australian Capital Territory), Papua New Guinea, Russia (Vladivostok Time)
	UTC_PLUS_1030		= 35,	// Australia (Lord Howe Island)
	UTC_PLUS_1100		= 36,	// Russia (Srednekolymsk Time), Salomon Islands, Vanuatu
	UTC_PLUS_1200		= 37,	// Fiji, Kiribati (Gilbert Islands), Marshall Islands, Nauru, New Zealand, Russia (Kamchatka Time), Tuvalu
	UTC_PLUS_1245		= 38,	// New Zealand (Chatham Islands)
	UTC_PLUS_1300		= 39,	// Kiribati (Phoenix Islands), New Zealand (Tokelau), Samoa, Tonga
	UTC_PLUS_1400		= 40,	// Kiribati (Line Islands)
	UTC_OUT_OF_RANGE	= 41,	// OUT OF RANGE
} utcTimeZone_e;

typedef enum weekDay_t {
	WEEKDAY_UNDEFINED	= 0,
	WEEKDAY_SUNDAY		= 1,
	WEEKDAY_MONDAY		= 2,
	WEEKDAY_TUESDAY		= 3,
	WEEKDAY_WEDNESDAY	= 4,
	WEEKDAY_THURSDAY	= 5,
	WEEKDAY_FRIDAY		= 6,
	WEEKDAY_SATURDAY	= 7
} weekDay_t;

// =============================================================================
// DateTime - Class declaration
// =============================================================================

class DateTime
{
public:
	DateTime();
	bool getDate(uint8_t *day, month_t *month = NULL, uint16_t *year = NULL);
	bool getTime(uint8_t *hour, uint8_t *minute = NULL, uint8_t *second = NULL, uint16_t *millisecond = NULL);
	bool setDate(uint8_t day, month_t month, uint16_t year);
	bool setTime(uint8_t hour, uint8_t minute, uint8_t second);
	bool setTime(uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond);
	bool setTime(uint8_t hour, uint8_t minute, uint8_t second, utcTimeZone_e timeZone);
	bool setTime(uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, utcTimeZone_e timeZone);
	bool getWeekDay(weekDay_t *weekDay);

private:
	bool isLeapYear(uint16_t year);
	void evaluateDayOfWeek(void);

private:
	uint8_t			year_			: 7;		// Year in four two digits format valid values in range [0 to 99], 127 is reserved for NOT DEFINED
	month_t			month_			: 4;		// Month number; valid values in range [1 to 12], 0 is reserved for NOT DEFINED
	uint8_t			day_			: 5;		// Month day number; valid values in range [1 to 31], 0 is reserved for NOT DEFINED
	weekDay_t		weekDay_		: 3;		// Week day number; valid values in range [1 to 7], 0 is reserved for NOT DEFINED
	uint8_t			hour_			: 5;		// Hour in 24-hours format; valid values in range [0 to 24], 25 is reserved for NOT DEFINED
	uint8_t			minute_			: 6;		// Minutes; valid values in range [0 to 59], 60 is reserved for NOT DEFINED
	uint8_t			second_			: 6;		// Seconds; valid values in range [0 to 59], 60 is reserved for NOT DEFINED
	uint16_t		millisecond_	: 10;		// Milliseconds; valid values in range [0 to 999], 1000 is reserved for NOT DEFINED
	bool			leapYear_		: 1;		// If the year is a leap year
	bool			summerTime_		: 1;		// If summer time is active
	utcTimeZone_e	timeZone_		: 6;		// Current time zone
	error_e			lastError_;
	bool			initialized		: 1;
	// 7 Bytes (54 used bits + 1 unused bits) + 1 byte (error_e)
};

// =============================================================================
// DateTime - Class inline function definitions
// =============================================================================

/* NONE */

// =============================================================================
// Extern global variables
// =============================================================================

/* NONE */

// =============================================================================
// General public functions declarations
// =============================================================================

/* NONE */

// =============================================================================
// General inline functions definitions
// =============================================================================

/* NONE */

#endif // __DATE_TIME_HPP
