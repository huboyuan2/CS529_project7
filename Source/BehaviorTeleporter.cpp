//------------------------------------------------------------------------------
//
// File Name:	BehaviorTeleporter.cpp
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
#include "BehaviorTeleporter.h"
#include "DGL.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"

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

	BehaviorTeleporter::BehaviorTeleporter(void)
		: Behavior()
	{
	}

	BehaviorTeleporter::BehaviorTeleporter(const BehaviorTeleporter* other)
		: Behavior(other)
		, windowsize(other ? other->windowsize : Vector2D(0.0f, 0.0f))
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

	void BehaviorTeleporter::Read(Stream& stream)
	{
		stream.PushNode("BehaviorTeleporter");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		//Behavior::Read(stream);
		stream.Read("StateNext", stateNext);
		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorTeleporter::onInit()
	{
		this->windowsize = DGL_Window_GetSize();
		this->windowsize.Scale(0.5);
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorTeleporter::onUpdate(float dt)
	{
		UpdateTransform();
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorTeleporter::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}
	void BehaviorTeleporter::UpdateTransform()
	{
		return;
		/*this->windowsize = DGL_Window_GetSize();
		this->windowsize.Scale(0.5);*/

		Transform* t = Parent()->Get<Transform>();


		if (!t)
		{
			return;
		}

		const Vector2D& pos =t->Translation();
		

		if (pos.x > windowsize.x)
		{

   			t->Translation(Vector2D(-windowsize.x + 0.01f, pos.y));
		}

		if (pos.y > windowsize.y)
		{

			t->Translation(Vector2D(pos.x, -windowsize.y + 0.01f));
		}

		if (pos.x < -windowsize.x)
		{

			t->Translation(Vector2D(windowsize.x - 0.01f, pos.y));
		}

		if (pos.y < -windowsize.y)
		{

			t->Translation(Vector2D(pos.x, windowsize.y - 0.01f));
		}
	}
#pragma endregion Private Functions

}	// namespace