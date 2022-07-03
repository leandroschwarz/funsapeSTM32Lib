/* =============================================================================
 * Project:			FunSAPE++ Embedded Library
 * File name:		funsapeLibFixedPoint.hpp
 * Module:			Fixed point arithmetic using Q types
 * Authors:			__AUTHORS_TO_REPLACE__
 * Build:			__BUILD_TO_REPLACE__
 * Last edition:	__DATE_TO_REPLACE__
 * ========================================================================== */

#ifndef __FUNSAPE_LIB_FIXED_POINT_HPP
#define __FUNSAPE_LIB_FIXED_POINT_HPP			__BUILD_TO_REPLACE__

#include "../funsapeLibGlobalDefines.hpp"
#ifndef __FUNSAPE_LIB_GLOBAL_DEFINES_HPP
#	error	[funsapeLibFixedPoint.hpp] Error 9 - Global definitions file (funsapeLibGlobalDefines.hpp) is missing or corrupted!
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __BUILD_TO_REPLACE__
#	error	[funsapeLibFixedPoint.hpp] Error 10 - Build mismatch between (funsapeLibFixedPoint.hpp) and global definitions file (funsapeLibGlobalDefines.hpp)!
#endif
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>

class int16q4_t
{
	// Constructors
public:
	int16q4_t(void);
	int16q4_t(float value);

	// Methods
public:
	int16_t getRawValue(void);

	// Typecast overloading
	operator int() {
		return (this->_value >> 4);
	}
	operator float() {
		float auxValue = (float)(this->_value);
		auxValue /= 16;
		return auxValue;
	}
	// Operator overloading
	int16q4_t &operator=(const uint16_t a) {
		this->_value = a;
		return *this;
	}
	int16q4_t &operator+=(const int16q4_t &a) {
		_value += a._value;
		return *this;
	}
	int16q4_t &operator-=(const int16q4_t &a) {
		_value -= a._value;
		return *this;
	}
// int16q4_t &operator*=(const int16q4_t &a)
// int16q4_t &operator/=(const int16q4_t &a)
// int16q4_t &operator%=(const int16q4_t &a)

	friend int16q4_t operator+(int16q4_t a, const int16q4_t &b) {
		a += b;
		return a;
	}
	friend int16q4_t operator+(int16q4_t a, const int16_t &b) {
		a += b;
		return a;
	}
	friend int16q4_t operator-(int16q4_t a, const int16q4_t &b) {
		a -= b;
		return a;
	}
// friend int16q4_t operator*(int16q4_t a, const int16q4_t &b)
// friend int16q4_t operator/(int16q4_t a, const int16q4_t &b)
// friend int16q4_t operator%(int16q4_t a, const int16q4_t &b)

	friend bool operator<(int16q4_t a, const int16q4_t &b) {
		return (a._value < b._value) ? true : false;
	}

	friend bool operator<=(int16q4_t a, const int16q4_t &b) {
		return (a._value <= b._value) ? true : false;
	}

	friend bool operator>(int16q4_t a, const int16q4_t &b) {
		return (a._value > b._value) ? true : false;
	}

	friend bool operator>=(int16q4_t a, const int16q4_t &b) {
		return (a._value >= b._value) ? true : false;
	}

	friend bool operator==(int16q4_t a, const int16q4_t &b) {
		return (a._value == b._value) ? true : false;
	}

	friend bool operator!=(int16q4_t a, const int16q4_t &b) {
		return (a._value != b._value) ? true : false;
	}

private:
	int16_t _value;
};

int16q4_t::int16q4_t(void)
{
	this->_value = 0;
}

int16q4_t::int16q4_t(float value_p)
{
	this->_value = 0;

	if(value_p < 0) {
		value_p = -value_p;
		this->_value |= (1 << 15);
	}
	this->_value |= int(value_p * 16) & ~(1 << 15);
}

int16_t int16q4_t::getRawValue()
{
	return this->_value;
}

#endif // __FUNSAPE_LIB_FIXED_POINT_HPP
