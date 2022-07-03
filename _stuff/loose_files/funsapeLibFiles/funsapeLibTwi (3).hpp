/* =============================================================================
 * Project:         FunSAPE++ Embedded Library
 * File name:       funsapeLibTwi.hpp
 * Module:          TWI Peripheral Module for FunSAPE++ Embedded Library project
 * Authors:         __AUTHORS_LIST__
 * Build:           __BUILD_NUMBER__
 * Last edition:    __CURRENT_DATE__
 * ========================================================================== */

// =============================================================================
// Include guard - Begin
// =============================================================================

#ifndef __FUNSAPE_LIB_TWI_HPP
#define __FUNSAPE_LIB_TWI_HPP                   __BUILD_NUMBER__

// =============================================================================
// Dependencies - Global definitions
// =============================================================================

#include "funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#   error [funsapeLibTwi.hpp] Error - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_NUMBER__
#   error [funsapeLibTwi.hpp] Error - Build mismatch between global definitions file (funsapeLibGlobalDefines.hpp) and current header file (funsapeLibTwi.hpp)!
#endif

// =============================================================================
// Platform verification - Begin
// =============================================================================

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
#   if defined(USE_HAL_DRIVER)
#      if defined(HAL_I2C_MODULE_ENABLED)

// =============================================================================
// Dependencies - FunSAPE Library header files
// =============================================================================

#include "src/funsapeLibDebug.hpp"
#ifndef __FUNSAPE_LIB_DEBUG_HPP
#   error [funsapeLibTwi.hpp] Error - Required module (funsapeLibDebug.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_DEBUG_HPP != __BUILD_NUMBER__
#   error [funsapeLibTwi.hpp] Error - Build mismatch between required module (funsapeLibDebug.hpp) and current header file (funsapeLibTwi.hpp)!
#endif

#include "src/funsapeLibBus.hpp"
#ifndef __FUNSAPE_LIB_BUS_HPP
#   error [funsapeLibTwi.hpp] Error - Required module (funsapeLibBus.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_BUS_HPP != __BUILD_NUMBER__
#   error [funsapeLibTwi.hpp] Error - Build mismatch between required module (funsapeLibBus.hpp) and current header file (funsapeLibTwi.hpp)!
#endif

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

// NONE

// =============================================================================
// Extern global variables
// =============================================================================

// NONE

// =============================================================================
// Twi - Class declaration
// =============================================================================

/**
 * @brief
 *
 * Detailed description of this element.
 *
 */
class Twi : public Bus
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    // NONE

private:
    /**
     * @brief
     *
     * Detailed description of this element.
     *
     */
    enum class TwiOperation : bool_t {
        READ                            = 0,
        WRITE                           = 1,
    };

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Operator overloading ----------------------------------------------------

public:
    // NONE

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    Twi(
            void
    );
    ~Twi(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    //     ////////////////////    DATA TRANSFER     ////////////////////     //
    bool_t readReg(
            uint8_t reg_p,
            uint8_t *buffData_p,
            uint16_t buffSize_p = 1
    );
    bool_t writeReg(
            cuint8_t reg_p,
            cuint8_t *buffData_p,
            cuint16_t buffSize_p = 1
    );

    //     //////////////////    PROTOCOL SPECIFIC     //////////////////     //
    bool_t setDevice(
            cuint16_t address_p,
            cbool_t useLongAddress_p = false
    );

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Bus::BusType getBusType(
            void
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Error getLastError(
            void
    );
    bool_t init(
            I2C_HandleTypeDef *busHandler_p,
            cuint16_t bufSize_p = 20
    );
    bool_t setTimeout(
            cuint16_t timeout_p
    );

private:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    void _clearData(
            void
    );
    void _deinitialize(
            void
    );
    bool_t _initialize(
            void
    );
    bool_t _isInitialized(
            void
    );
    bool_t _transmit(
            void
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

public:
    // NONE

private:
    //     /////////////////    PERIPHERAL HANDLER     //////////////////     //
    I2C_HandleTypeDef   *_busHandler;

    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t              _busy                   : 1;
    uint16_t            _devAddress             : 10;
    bool_t              _devAddressSet          : 1;
    bool_t              _initialized            : 1;
    Error               _lastError;
    TwiOperation        _operation;
    uint8_t             _regAddress;
    uint16_t            _timeout;

    //     /////////////     HAL DATA STRUCT VARIABLES     //////////////     //
    uint32_t            _clockSpeed             : 22;
    uint16_t            _ownAddress1            : 10;
    uint16_t            _ownAddress2            : 10;
    bool_t              _useDualAddress         : 1;
    bool_t              _useDutyCycle16_9       : 1;
    bool_t              _useGeneralCall         : 1;
    bool_t              _useLongAddress         : 1;
    bool_t              _useNoStretchMode       : 1;

    //     ////////////////////    DATA BUFFERS      ////////////////////     //
    uint8_t             *_bufferData;
    uint16_t            _bufferIndex;
    uint16_t            _bufferLength;
    uint16_t            _bufferMaxSize;

protected:
    // NONE

}; // class Twi

// =============================================================================
// Twi - Class overloading operators
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// -----------------------------------------------------------------------------
// Externally defined global variables -----------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Internally defined global variables -----------------------------------------

// NONE

// =============================================================================
// Twi - Class inline function definitions
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

// =============================================================================
// Platform verification - End
// =============================================================================

#       else
#           warning I2C HAL module is not enabled, therefore, I2C module will not be compiled.
#       endif   // defined(HAL_I2C_MODULE_ENABLED)
#   else
#       warning HAL driver is not in use, therefore, I2C module will not be compiled.
#   endif   // defined(USE_HAL_DRIVER)
#else
#   warning Platform unsupported, therefore, I2C module will not be compiled.
#endif  // defined(_FUNSAPE_PLATFORM_ARM_STM32)

// =============================================================================
// Include guard - End
// =============================================================================

#endif // __FUNSAPE_LIB_TWI_HPP

// =============================================================================
// END OF FILE - funsapeLibTwi.hpp
// =============================================================================
