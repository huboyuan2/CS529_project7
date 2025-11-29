//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.cpp
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
#include "BehaviorBullet.h"
#include "Stream.h"
#include "Collider.h"
#include "ColliderCircle.h"
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

	BehaviorBullet::BehaviorBullet(void)
		: Behavior()
	{
	}

	BehaviorBullet::BehaviorBullet(const BehaviorBullet* other)
		: Behavior(other)
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

	void BehaviorBullet::Read(Stream& stream)
	{
		stream.PushNode("BehaviorBullet");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		//Behavior::Read(stream);
		stream.Read("StateCurr", stateCurr);
		stream.Read("StateNext", stateNext);
		stream.Read("Timer", timer);
		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorBullet::onInit()
	{
		Collider* collider = this->Parent()->Get<ColliderCircle>();

		//Collider* col2 = e2->Get<Collider>();
		if (collider)
		{
			collider->RegisterHandler(CollisionHandler);
		}
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorBullet::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cIdle:
			timer -= dt;
			if(timer<0)
			{
				//Entity* parent = Parent();
				Parent()->Destroy();
				//parent = nullptr;
			}
			break;

		default:
			break;
		}
	}

	void BehaviorBullet::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}
	void BehaviorBullet::CollisionHandler(Entity* e1, const Entity* e2)
	{
		if (e1 && e2)
		{
			if (e2->Name() == "Asteroid")
			{
				e1->Destroy();
			}
		}
	}
#pragma endregion Private Functions

}	// namespace