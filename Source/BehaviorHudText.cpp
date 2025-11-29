//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "template" entity.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "Precompiled.h"
#include "Entity.h"
#include "Behavior.h"
#include "BehaviorHudText.h"
#include "Stream.h"
#include "ScoreSystem.h"
#include "Component.h"
#include "Sprite.h"

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

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	BehaviorHudText::BehaviorHudText(void)
		: Behavior()
	{
	}

	BehaviorHudText::BehaviorHudText(const BehaviorHudText* other)
		: Behavior(other)
		, scoreSystemId(other->scoreSystemId)
		, displayValue(other->displayValue)
		, labelString(other->labelString)
		, displayString(other->displayString)
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

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	void BehaviorHudText::Read(Stream& stream)
	{
		stream.PushNode("BehaviorHudText");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		/*stream.Read("StateCurr", stateCurr);
		stream.Read("StateNext", stateNext);
		stream.Read("Timer", timer);*/
		stream.Read("ScoreSystemId", scoreSystemId);
		stream.Read("LabelString", labelString);
		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorHudText::onInit()
	{
		UpdateText();
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorHudText::onUpdate(float dt)
	{
		unsigned systemval = ScoreSystem::Instance().GetValue(static_cast<ScoreSystem::ScoreSystemId>(scoreSystemId));
		if (systemval != displayValue)
		{
			UpdateText();
		}

		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}
	void BehaviorHudText::UpdateText()
	{
		displayValue= ScoreSystem::Instance().GetValue(static_cast<ScoreSystem::ScoreSystemId>(scoreSystemId));
		displayString = std::format("{} {}", labelString, displayValue);
  		Parent()->Get<Sprite>()->SetText(displayString);
	}
	/*void BehaviorHudText::UpdateText()
	{
		displayValue = ScoreSystem::Instance().GetValue(static_cast<ScoreSystem::ScoreSystemId>(scoreSystemId));
		displayString = labelString + " " + std::to_string(displayValue);
		Parent()->Get<Sprite>()->SetText(displayString);
	}*/
	void BehaviorHudText::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

#pragma endregion Private Functions

}	// namespace