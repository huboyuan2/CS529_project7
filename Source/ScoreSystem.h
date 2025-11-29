//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 5
// Purpose:		This system is responsible for tracking scores, high scores, and wave counts.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "System.h"

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
	class ScoreSystem : public System
	{
		// Public Constants and Enums:
	public:
		typedef enum
		{
			SsiInvalid = -1,
			SsiScore = 0,
			SsiHighScore,
			SsiWaveCount,
			SsiMax,
		} ScoreSystemId;

		// Constructors/Destructors:
	public:
		ScoreSystem(void);

		// All systems need a virtual destructor to have their destructor called 
		~ScoreSystem(void) override;

		// Public Static Functions:
	public:
		static ScoreSystem& Instance() { return *instance; }

		// Public Functions:
	public:
		// @brief Start a new game by clearing the score system values.
		// @brief [NOTE: Set the score, highScore, and waveCount values to 0.]
		void NewGame();

		// @brief Reset the score system values when restarting an existing game.
		// @brief [NOTE: Set highScore to the maximum of either score or highScore.]
		// @brief [NOTE: Set score and waveCount values to 0.
		void Reset();

		// @brief Get the requested value from the score system.
		// @brief [NOTE: There many different ways to handle this.  Two options include:
		// @brief   - Use a switch-statement to access the correct variable.
		// @brief   - Store the Score System variables in an array and use this index
		// @brief     to access into the array.]
		//
		// @param id = Identifier associated with the requested value.
		unsigned GetValue(ScoreSystemId id) const;

		// @brief Increase the current score by a specified amount.
		// 
		// @param amount = The amount to be added to the score.
		void IncreaseScore(unsigned amount);

		// @brief Increase the current wave count by 1.
		void IncreaseWave(void);

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Static Constants:
	private:

		// Private Static Variables:
	private:
		static ScoreSystem* instance;

		// Private Variables:
	private:
		// [NOTE: You may change these individual variables into an array, if you wish.]
	
		// @brief The existing score for the current game.
		unsigned score{ 0 };

		// @brief The existing high score for the current game.
		unsigned highScore{ 0 };

		// @brief The existing wave count for the current game.
		unsigned waveCount{ 0 };
	};

}	// namespace