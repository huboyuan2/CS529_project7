//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template class for a new system.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <cassert>

#include "ScoreSystem.h"
#include "System.h"

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

	//------------------------------------------------------------------------------
	// Private Static Variables:
	//------------------------------------------------------------------------------

	ScoreSystem* ScoreSystem::instance = nullptr;

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	ScoreSystem::ScoreSystem(void)
		: System("ScoreSystem")
	{
		// Raise an assert if this system has already been created.
		assert(instance == nullptr);

		// Store this system's instance for use by static functions.
		instance = this;
	}

	//--------------------------------------------------------------------------

	ScoreSystem::~ScoreSystem(void)
	{
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions


#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions
			// @brief Start a new game by clearing the score system values.
		// @brief [NOTE: Set the score, highScore, and waveCount values to 0.]
	void ScoreSystem::NewGame()
	{
		score = 0;
		highScore = 0;
		waveCount = 0;
	}

	// @brief Reset the score system values when restarting an existing game.
	// @brief [NOTE: Set highScore to the maximum of either score or highScore.]
	// @brief [NOTE: Set score and waveCount values to 0.
	void ScoreSystem::Reset()
	{
		
		if (score > highScore)
		{
			highScore = score;
		}
		score = 0;
		waveCount = 0;
	}

	// @brief Get the requested value from the score system.
	// @brief [NOTE: There many different ways to handle this.  Two options include:
	// @brief   - Use a switch-statement to access the correct variable.
	// @brief   - Store the Score System variables in an array and use this index
	// @brief     to access into the array.]
	//
	// @param id = Identifier associated with the requested value.
	unsigned ScoreSystem::GetValue(ScoreSystemId id) const
	{
		switch (id)
		{
		case SsiScore:
			return score;
			break;
		case SsiHighScore:
			return highScore;
			break;
		case SsiWaveCount:
			return waveCount;
			break;
		case SsiMax:
			return -1;
			break;
		default:
			return -1;
			break;
		}
	}

	// @brief Increase the current score by a specified amount.
	// 
	// @param amount = The amount to be added to the score.
	void ScoreSystem::IncreaseScore(unsigned amount)
	{
		score += amount;
	}

	// @brief Increase the current wave count by 1.
	void ScoreSystem::IncreaseWave(void)
	{
		waveCount += 1;
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	//bool ScoreSystem::Initialize()
	//{
	//	// Add system-specific initialization code here.

	//	// Return true if the initialization completed successfully.
	//	return true;
	//}

#pragma endregion Private Functions

}	// namespace