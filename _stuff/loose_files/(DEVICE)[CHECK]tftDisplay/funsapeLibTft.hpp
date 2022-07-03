/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibTft.hpp
 * Module:			TFT Display interface for FunSAPE++ Embedded Library project
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * Notes:			The code is based on UTFT Library from Rinky-Dink
 * 					Electronics, Henning Karlsen, available at
 * 					http://www.RinkyDinkElectronics.com/.
 * ========================================================================== */

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_TFT_HPP
#define __FUNSAPE_LIB_TFT_HPP					__BUILD_TO_REPLACE__

// =============================================================================
// Dependencies
// =============================================================================

// -----------------------------------------------------------------------------
// Global definitions file -----------------------------------------------------

#include "..\funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#	error	[funsapeLibTft.hpp] Error 10 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibTft.hpp] Error 11 - Build mismatch between (funsapeLibTft.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif

// -----------------------------------------------------------------------------
// Header files - Basic header for all files -----------------------------------

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
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// -----------------------------------------------------------------------------
// Single variables => shortening the name of single data types ----------------

// NONE

// -----------------------------------------------------------------------------
// Single variables => enumerations understood as logic values -----------------

typedef enum tftOrientation_t : bool {
	TFT_PORTRAIT						= false,
	TFT_LANDSCAPE						= true
} tftOrientation_t;

typedef enum tftDisplayState_t : bool {
	TFT_DISPLAY_OFF						= false,
	TFT_DISPLAY_ON						= true
} tftDisplayState_t;

// -----------------------------------------------------------------------------
// Single variables => small enumerations that can be understood as a single variable

// NONE

// -----------------------------------------------------------------------------
// Enumerations => large enumerations or enumerations with expansible number of element

typedef enum tftDisplayModel_t : uint32_t {
	TFT_MODEL_										,
	TFT_MODEL_CTE22									,
	TFT_MODEL_CTE28									,
	TFT_MODEL_CTE32									,
	TFT_MODEL_CTE32_R2									,
	TFT_MODEL_CTE32HR									,
	TFT_MODEL_CTE32W									,
	TFT_MODEL_CTE35IPS									,
	TFT_MODEL_CTE40									,
	TFT_MODEL_CTE50									,
	TFT_MODEL_CTE50CPLD									,
	TFT_MODEL_CTE70									,
	TFT_MODEL_CTE70CPLD									,
	TFT_MODEL_DMTFT18101									,
	TFT_MODEL_DMTFT22102									,
	TFT_MODEL_DMTFT24104									,
	TFT_MODEL_DMTFT28103									,
	TFT_MODEL_DMTFT28105									,
	TFT_MODEL_EHOUSE50									,
	TFT_MODEL_EHOUSE50CPLD									,
	TFT_MODEL_EHOUSE70									,
	TFT_MODEL_ELEE32_REVA									,
	TFT_MODEL_ELEE32_REVB									,
	TFT_MODEL_INFINIT32									,


	TFT_MODEL_ITDB02_V18_SP								,
	TFT_MODEL_ITDB02_V22									,
	TFT_MODEL_ITDB02_V22_SP									,
	TFT_MODEL_ITDB02_V24									,
	TFT_MODEL_ITDB02_V24D									,
	TFT_MODEL_ITDB02_V24DWOT								,
	TFT_MODEL_ITDB02_V24E_16									,
	TFT_MODEL_ITDB02_V24E_8									,
	TFT_MODEL_ITDB02_V24EV2_16									,
	TFT_MODEL_ITDB02_V24EV2_8									,
	TFT_MODEL_ITDB02_V25H									,
	TFT_MODEL_ITDB02_V28									,
	TFT_MODEL_ITDB02_V28V2_16									,
	TFT_MODEL_ITDB02_V28V2_8									,
	TFT_MODEL_ITDB02_V32									,
	TFT_MODEL_ITDB02_V32S									,
	TFT_MODEL_ITDB02_V32SV2									,
	TFT_MODEL_ITDB02_V32WC									,
	TFT_MODEL_ITDB02_V32WD									,
	TFT_MODEL_ITDB02_V43									,
	TFT_MODEL_ITDB02_V50									,
	TFT_MODEL_LPH9135									,


	TFT_MODEL_ITDB25H									,
	TFT_MODEL_ITDB28									,
	TFT_MODEL_ITDB28_V2									,
	TFT_MODEL_ITDB28_V2_ALT									,
	TFT_MODEL_ITDB32									,
	TFT_MODEL_ITDB32S									,
	TFT_MODEL_ITDB32S_V2									,
	TFT_MODEL_ITDB32WC									,
	TFT_MODEL_ITDB32WD									,
	TFT_MODEL_ITDB43									,
	TFT_MODEL_ITDB50									,
	TFT_MODEL_LPH9135									,
	TFT_MODEL_MI0283QT9									,


} tftDisplayModel_t;

// -----------------------------------------------------------------------------
// New Data Type - Enumerations => parametric table that doesn't maintain value equivalence with datasheet's values

// NONE

// -----------------------------------------------------------------------------
// New Data Type - Flags => enumerations that can be combined in the form of flags

// NONE

// -----------------------------------------------------------------------------
// New Data Type - Structures, Unions and Bit Fields ---------------------------

// NONE

// -----------------------------------------------------------------------------
// New Data Type - Classes -----------------------------------------------------

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Tft - Class declaration
// =============================================================================

class Tft
{
	// -------------------------------------------------------------------------
	// New data types
	// -------------------------------------------------------------------------

public:

	// -------------------------------------------------------------------------
	// Operators overloading
	// -------------------------------------------------------------------------

	// NONE

	// -------------------------------------------------------------------------
	// Constructors
	// -------------------------------------------------------------------------

public:
	Tft(tftDisplayModel_t model);				// TODO: Implement function
	~Tft(void);									// TODO: Implement function

	// -------------------------------------------------------------------------
	// Methods
	// -------------------------------------------------------------------------

	// Methods - Public
public:
	//     ///////////////////     INITIALIZATION     ///////////////////     //
	bool	initialize(
		tftOrientation_t byteOrientation = TFT_LANDSCAPE
	);
	bool	setInterface(
		ioPin_t rsPin,
		ioPin_t rdPin,
		ioPin_t wrPin,
		ioPin_t rstPin,
		ioPin_t csPin
	);

	//     /////////////////     CONTROL AND STATUS     /////////////////     //
	bool	clrScr(void
	);
	error_e	getLastError(void
	);
	bool	setDisplayState(
		tftDisplayState_t displayState = TFT_DISPLAY_ON
	);
	bool	setContrastLevel(
		uint8_t contrastLevel
	);
	bool	getDisplayXSize(
		uint16_t *sizeX
	);
	bool	getDisplayYSize(
		uint16_t *sizeY
	);

	//     ///////////////////////     COLORS     ///////////////////////     //
	bool	setColor(
		uint8_t red,
		uint8_t green,
		uint8_t blue
	);
	bool	setColor(
		uint32_t color
	);
	bool	getColor(
		uint32_t *color
	);
	bool	setBackColor(
		uint8_t red,
		uint8_t green,
		uint8_t blue
	);
	bool	setBackColor(
		uint32_t color
	);
	bool	getBackColor(
		uint32_t *color
	);

	//     ///////////////////     BASIC DRAWINGS     ///////////////////     //
	void	drawPixel(
		uint16_t xPos,
		uint16_t yPos
	);
	void	drawLine(
		uint16_t xPos1,
		uint16_t yPos1,
		uint16_t xPos2,
		uint16_t yPos2
	);
	void	drawRect(
		uint16_t xPos1,
		uint16_t yPos1,
		uint16_t xPos2,
		uint16_t yPos2
	);
	void	fillRect(
		uint16_t xPos1,
		uint16_t yPos1,
		uint16_t xPos2,
		uint16_t yPos2
	);
	void	drawRoundRect(
		uint16_t xPos1,
		uint16_t yPos1,
		uint16_t xPos2,
		uint16_t yPos2
	);
	void	fillRoundRect(
		uint16_t xPos1,
		uint16_t yPos1,
		uint16_t xPos2,
		uint16_t yPos2
	);
	void	drawCircle(
		uint16_t xCenter,
		uint16_t yCenter,
		uint16_t radius
	);
	void	fillCircle(
		uint16_t xCenter,
		uint16_t yCenter,
		uint16_t radius
	);
	void	fillScr(
		uint8_t red,
		uint8_t green,
		uint8_t blue
	);
	void	fillScr(
		uint32_t color
	);
	void	drawBitmap(
		uint16_t xPos,
		uint16_t yPos,
		uint16_t width,
		uint16_t length,
		bitmapdatatype data,
		uint16_t scale = 1
	);
	void	drawBitmap(
		uint16_t xPos,
		uint16_t yPos,
		uint16_t width,
		uint16_t length,
		bitmapdatatype data,
		uint16_t deg,
		uint16_t rox,
		uint16_t roy
	);

	//     ////////////////////////     TEXT     ////////////////////////     //
	bool	setFont(
		uint8_t *font
	);
	bool	getFont(
		uint8_t *font
	);
	bool	getFontXSize(
		uint8_t *sizeX
	);
	bool	getFontYSize(
		uint8_t *sizeY
	);
	void	print(
		char *string,
		uint8_t x,
		uint8_t y,
		uint8_t deg = 0
	);


	void	setBrightness(byte br);
	void	setDisplayPage(byte page);
	void	setWritePage(byte page);



	// NONE

	// Methods - Private
private:

	// NONE

	// -------------------------------------------------------------------------
	// Properties
	// -------------------------------------------------------------------------

	// Data members - Private
private:

	// NONE

}; // class Tft

// =============================================================================
// Tft - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// Tft - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

// NONE

#endif // __FUNSAPE_LIB_TFT_HPP
