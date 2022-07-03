/* =============================================================================
 * Project:         FunSAPE++ Embedded Library
 * File name:       funsapeLibCec.cpp
 * Module:          CEC Peripheral Module for FunSAPE++ Embedded Library
 *                      project
 * Authors:         __AUTHORS_LIST__
 * Build:           __BUILD_NUMBER__
 * Last edition:    __CURRENT_DATE__
 * ========================================================================== */

// =============================================================================
// Dependencies
// =============================================================================

#include "funsapeLibCec.hpp"
#ifndef __FUNSAPE_LIB_CEC_HPP
#   error [funsapeLibCec.cpp] Error - Header file (funsapeLibCec.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_CEC_HPP != __BUILD_NUMBER__
#   error [funsapeLibCec.cpp] Error - Build mismatch between source (funsapeLibCec.cpp) and header (funsapeLibCec.hpp) files!
#endif

// =============================================================================
// Platform verification - Begin
// =============================================================================

#if defined(_FUNSAPE_PLATFORM_ARM_STM32)
#   if defined(USE_HAL_DRIVER)
#      if defined(HAL_CEC_MODULE_ENABLED)

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Global variables
// =============================================================================

// NONE

// =============================================================================
// Static functions declarations
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

/**
 * @brief Construct a new Cec:: Cec object
 *
 * Detailed description of this element.
 *
 */
Cec::Cec(void)
{
    // Mark passage for debugging purpose
    debugMark("Cec::Cec(void)", Debug::CodeIndex::CEC_MODULE);

    // Resets data members

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE);
    return;
}

/**
 * @brief Destroy the Cec:: Cec object
 *
 * Detailed description of this element.
 *
 */
Cec::~Cec(void)
{
    // Mark passage for debugging purpose
    debugMark("Cec::~Cec(void)", Debug::CodeIndex::CEC_MODULE);

    // Returns successfully
    debugMessage(Error::NONE);
    return;
}

// =============================================================================
// Class own methods - Public
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

/**
 * @brief
 *
 * Detailed description of this element.
 *
 * @return Error
 */
Error Cec::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

// =============================================================================
// Class own methods - Private
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

/**
 * @brief
 *
 * Detailed description of this element.
 *
 * @return true
 * @return false
 */
bool_t Cec::_isInitialized(void)
{
    // Mark passage for debugging purpose
    debugMark("Cec::_isInitialized(void)", Debug::CodeIndex::CEC_MODULE);

    // Checks initialization
    if (!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE);
    return true;
}

// =============================================================================
// Class own methods - Protected
// =============================================================================

// NONE

// =============================================================================
// Platform verification - End
// =============================================================================

#       endif   // defined(HAL_CEC_MODULE_ENABLED)
#   endif   // defined(USE_HAL_DRIVER)
#endif  // defined(_FUNSAPE_PLATFORM_ARM_STM32)

// =============================================================================
// END OF FILE - funsapeLibCec.cpp
// =============================================================================
