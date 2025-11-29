//------------------------------------------------------------------------------
//
// File Name:	Random.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
// Cite: https://learn.microsoft.com/en-us/cpp/standard-library/random
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include <random>
#include <iostream>
#include "Precompiled.h"
#include "Random.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Public Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------
	std::mt19937 Random::generator;
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	Random::Random(void)
	{
	}

	////--------------------------------------------------------------------------

	//Random::~Random(void)
	//{
	//}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions
			// @brief Initialize the Psuedorandom Number Generator (PRNG).
		// @brief You may use the example code from the following:
		// @brief   https://learn.microsoft.com/en-us/cpp/standard-library/random
		// @brief   However, if you do so, then you must cite this source within the .cpp file.
		// @brief   [HINT: Consider using time() to initialize the random seed.]
	void Random::Initialize()
	{
		std::random_device rd;
		Random::generator = std::mt19937(rd());
		//mt19937 gen(rd());
		//generator = gen(rd());
		//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}

	// @brief Generate a random number in the interval [rangeMin, rangeMax] (inclusive).
	// @brief You may use the example code from the following:
	// @brief   https://learn.microsoft.com/en-us/cpp/standard-library/random
	// @brief   However, if you do so, then you must cite this source within the .cpp file.
	//
	// @param rangeMin = The lowest possible number generated.
	// @param rangeMax = The highest possible number generated.
	//
	// @return int = A random number in the interval [rangeMin, rangeMax] (inclusive).
	int Random::Range(int rangeMin, int RangeMax)
	{
		std::uniform_int_distribution<int> distribution(rangeMin, RangeMax);
		return distribution(Random::generator);
	}


	// @brief Generate a random floating-point number in the interval [rangeMin, rangeMax] (inclusive).
	// @brief You may use the example code from the following:
	// @brief   https://learn.microsoft.com/en-us/cpp/standard-library/uniform-real-distribution-class
	//
	// @param rangeMin = The lowest possible number generated.
	// @param rangeMax = The highest possible number generated.
	//
	// @return float = A random number in the interval [rangeMin, rangeMax] (inclusive).
	float Random::Range(float rangeMin, float rangeMax)
	{
		std::uniform_real_distribution<float> distribution(rangeMin, rangeMax);
		return distribution(Random::generator);
	}
#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace