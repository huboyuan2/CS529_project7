//------------------------------------------------------------------------------
//
// File Name:	Random.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 5
// Purpose:		This class is responsible for generating random numbers.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <random>

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	class Random
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Random(void);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Initialize the Psuedorandom Number Generator (PRNG).
		// @brief You may use the example code from the following:
		// @brief   https://learn.microsoft.com/en-us/cpp/standard-library/random
		// @brief   However, if you do so, then you must cite this source within the .cpp file.
		// @brief   [HINT: Consider using time() to initialize the random seed.]
		static void Initialize();

		// @brief Generate a random number in the interval [rangeMin, rangeMax] (inclusive).
		// @brief You may use the example code from the following:
		// @brief   https://learn.microsoft.com/en-us/cpp/standard-library/random
		// @brief   However, if you do so, then you must cite this source within the .cpp file.
		//
		// @param rangeMin = The lowest possible number generated.
		// @param rangeMax = The highest possible number generated.
		//
		// @return int = A random number in the interval [rangeMin, rangeMax] (inclusive).
		static int Range(int rangeMin, int RangeMax);

		// @brief Generate a random floating-point number in the interval [rangeMin, rangeMax] (inclusive).
		// @brief You may use the example code from the following:
		// @brief   https://learn.microsoft.com/en-us/cpp/standard-library/uniform-real-distribution-class
		//
		// @param rangeMin = The lowest possible number generated.
		// @param rangeMax = The highest possible number generated.
		//
		// @return float = A random number in the interval [rangeMin, rangeMax] (inclusive).
		static float Range(float rangeMin, float RangeMax);

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:
		// Static instance of the Mersenne Twister class.
		static std::mt19937 generator;

		// Private Variables:
	private:
	};

}	// namespace