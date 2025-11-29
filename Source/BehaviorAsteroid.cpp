//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.cpp
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
#include "BehaviorAsteroid.h"
#include "Stream.h"
#include "Random.h"
#include "Transform.h"
#include "Physics.h"
#include "DGL.h"
#include "Vector2D.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "Entity.h"
#include "Component.h"
#include "ScoreSystem.h"

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
	const unsigned BehaviorAsteroid::asteroidScore = 20;
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	BehaviorAsteroid::BehaviorAsteroid(void)
		: Behavior(), origin(cAsteroidOriginTlc)
	{
	}

	BehaviorAsteroid::BehaviorAsteroid(const BehaviorAsteroid* other)
		: Behavior(other), origin(other ? other->origin : cAsteroidOriginTlc)
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

	void BehaviorAsteroid::Read(Stream& stream)
	{
		stream.PushNode("BehaviorAsteroid");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		//Behavior::Read(stream);
		//stream.Read("StateCurr", stateCurr);
		stream.Read("StateNext", stateNext);
		//stream.Read("Timer", timer);
		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorAsteroid::onInit()
	{
		Collider* collider = this->Parent()->Get<ColliderCircle>();

		//Collider* col2 = e2->Get<Collider>();
		if (collider)
		{
			collider->RegisterHandler(CollisionHandler);
		}
		origin = static_cast<AsteroidOrigin>(Random::Range(0, 3));
		//
		SetPosition();
		SetVelocity();
		/*switch (stateCurr)
		{
		case cAsteroidOriginTlc:
			break;
		case cAsteroidOriginTrc:
			break;
		case cAsteroidOriginBlc:
			break;
		case cAsteroidOriginBrc:


		default:
			break;
		}*/
	}

	void BehaviorAsteroid::onUpdate(float dt)
	{/*
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}*/
	}

	void BehaviorAsteroid::onExit()
	{
		//switch (stateCurr)
		//{
		///*case cIdle:
		//	break;*/

		//default:
		//	break;
		//}
	}
	void BehaviorAsteroid::SetPosition()
	{
		Transform* t = Parent()->Get<Transform>();
		
		if(!t)
			return;	
		Vector2D windowsize = DGL_Window_GetSize();
		windowsize.Scale(0.5);
		Vector2D TopRight = Vector2D(windowsize);
		Vector2D BottomLeft = Vector2D(windowsize);
		BottomLeft.Negate();
		Vector2D TopLeft = Vector2D(BottomLeft.x, TopRight.y);
		Vector2D BottomRight = Vector2D(TopRight.x, BottomLeft.y);
		switch (origin)
		{
		case cAsteroidOriginTlc:
			t->Translation(TopLeft);
			//p->OldTranslation(TopLeft);
			t->Rotation(Random::Range(static_cast<float>(-80.0 / 57.3), static_cast<float>(-10.0 / 57.3)));
			break;
		case cAsteroidOriginTrc:
			t->Translation(TopRight);
			t->Rotation(Random::Range(static_cast<float>(-170.0 / 57.3), static_cast<float>(-100.0 / 57.3)));
			break;
		case cAsteroidOriginBlc:
			t->Translation(BottomLeft);
			t->Rotation(Random::Range(static_cast<float>(10.0 / 57.3), static_cast<float>(80.0 / 57.3)));
			break;
		case cAsteroidOriginBrc:
			t->Translation(BottomRight);
			t->Rotation(Random::Range(static_cast<float>(100.0 / 57.3), static_cast<float>(170.0 / 57.3)));
			break;
		default:
			break;
		}
		Physics* p = Parent()->Get<Physics>();
		if (p)
		{
			p->Initialize();
		}
	}
	void BehaviorAsteroid::SetVelocity()
	{
		Transform* t = Parent()->Get<Transform>();
		Physics* p = Parent()->Get<Physics>();
		if(!(t&&p))
			return;
		float speed = Random::Range(asteroidSpeedMin, asteroidSpeedMax);
		Vector2D vel = Vector2D(speed * cosf(t->Rotation()), speed * sinf(t->Rotation()));

		p->Velocity(vel);
	}
	void BehaviorAsteroid::CollisionHandler(Entity* e1, const Entity* e2)
	{
		if (e1 && e2)
		{
			if (e2->Name() == "Bullet" || e2->Name() == "Spaceship")
			{
				e1->Destroy();
				ScoreSystem::Instance().IncreaseScore(asteroidScore);
			}
		}
	}
#pragma endregion Private Functions

}	// namespace