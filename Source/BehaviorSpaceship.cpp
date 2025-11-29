//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.cpp
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
#include "BehaviorSpaceship.h"
#include "Stream.h"
#include "Transform.h"
#include "Physics.h"
#include "EntityFactory.h"
#include "SceneSystem.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include <numbers>

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
	const float BehaviorSpaceship::spaceshipAcceleration = 150.0f;
	const float BehaviorSpaceship::spaceshipSpeedMax = 500.0f;
	const float BehaviorSpaceship::spaceshipTurnRateMax = (float)std::numbers::pi / 1.5f;
	const float BehaviorSpaceship::spaceshipWeaponCooldownTime = 0.25f;
	const float BehaviorSpaceship::spaceshipWeaponBulletSpeed = 750.0f;
	const float BehaviorSpaceship::spaceshipDeathDuration = 3.0f;
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	BehaviorSpaceship::BehaviorSpaceship(void)
		: Behavior()
	{
	}

	BehaviorSpaceship::BehaviorSpaceship(const BehaviorSpaceship* other)
		: Behavior(other)
	{
	}
	Behavior::Behavior(const Behavior* other)
		: Component(other)
	{
		if (other)
		{
			stateCurr = other->stateCurr;
			stateNext = other->stateNext;
			timer = other->timer;
		}
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


	void BehaviorSpaceship::Read(Stream& stream)
	{
		stream.PushNode("BehaviorSpaceship");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		//Behavior::Read(stream);
		stream.Read("StateCurr", stateCurr);
		stream.Read("StateNext", stateNext);
		stream.Read("Timer", timer);
		// Read the derived class Behavior variables, if any.

		stream.PopNode();
		//static float respawnCountDown = spaceshipDeathDuration;
	}

	void BehaviorSpaceship::onInit()
	{
		Collider* collider = this->Parent()->Get<ColliderCircle>();
		Physics* p = Parent()->Get<Physics>();
		//Collider* col2 = e2->Get<Collider>();
		if (collider)
		{
			//static float respawnCountDown = spaceshipDeathDuration;
			collider->RegisterHandler(CollisionHandler);
		}
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			
			if (p)
			{
				p->Drag(0.99f);
			}
			break;

		default:
			break;
		}
	}

	void BehaviorSpaceship::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			UpdateRotation();
			UpdateWeapon(dt);
			if (DGL_Input_KeyTriggered(VK_UP))
			{
				stateNext = cSpaceshipThrust;
			}
			if (DGL_Input_KeyTriggered(VK_DOWN))
			{
				stateNext = cSpaceshipReverse;
			}
			break;
		case cSpaceshipThrust:
			UpdateRotation();
			UpdateVelocity(dt);
			UpdateWeapon(dt);
			if (!DGL_Input_KeyDown(VK_UP))
			{
				stateNext = cSpaceshipIdle;
			}
			break;
		case cSpaceshipReverse:
			UpdateRotation();
			UpdateVelocity(-dt);
			UpdateWeapon(dt);
			if (!DGL_Input_KeyDown(VK_DOWN))
			{
				stateNext = cSpaceshipIdle;
			}
			break;
			break;
		case cSpaceshipDead:
			//only called one time?
			if (timer > 0)
			{
				Transform* t = Parent()->Get<Transform>();
				if (t)
				{
					t->Scale(Vector2D(t->Scale().x * timer / 3, t->Scale().y * timer / 3));
					t->Rotation(timer*20);


				}
				Physics* p = Parent()->Get<Physics>();
				if(p)
				{
					p->Velocity(Vector2D(0.0f,0.0f));
				}
				timer -= dt;
			}
			else
			{
				if (timer > -100)
				{

					SceneSystem::Restart();
					timer = -1000;
				}
			}
				break;
		default:
			break;
		}
	}

	void BehaviorSpaceship::onExit()
	{
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			break;

		default:
			break;
		}
	}

	// @brief Update the rotation of the spaceship, based upon keyboard input.
	void BehaviorSpaceship::UpdateRotation() const
	{
		//Transform* t=Parent()->Get<Transform>();
		Physics* p = Parent()->Get<Physics>();
		if((DGL_Input_KeyDown(VK_LEFT)))
		{
			p->RotationalVelocity(spaceshipTurnRateMax);
			//t->Rotation(t->Rotation() - spaceshipTurnRateMax);
		}
		else if ((DGL_Input_KeyDown(VK_RIGHT)))
		{
			p->RotationalVelocity(-spaceshipTurnRateMax);
			//t->Rotation(t->Rotation() + spaceshipTurnRateMax);
		}
		else 
		{
			p->RotationalVelocity(0.0f);
		}

	}

	// @brief Update the velocity, applying an acceleration in the direction of the ship.
	void BehaviorSpaceship::UpdateVelocity(float dt) const
	{
		Transform* t = Parent()->Get<Transform>();
		Physics* p = Parent()->Get<Physics>();
		if (t && p)
		{
			Vector2D direction = { std::cos(t->Rotation()), std::sin(t->Rotation()) };
			direction.Normalize();
			direction.Scale(spaceshipAcceleration);
			Vector2D newVelocity = Vector2D(p->Velocity().x + direction.x * dt, p->Velocity().y + direction.y * dt);
			if (newVelocity.Length() > spaceshipSpeedMax)
			{
				newVelocity.Normalize();
				newVelocity.Scale(spaceshipSpeedMax);
			}
			p->Velocity(newVelocity);
		}
	}

	// @brief Update the weapon firing, based upon keyboard input.
	void BehaviorSpaceship::UpdateWeapon(float dt)
	{
		static float weaponCooldownTimer = 0.0f;
		weaponCooldownTimer -= dt;
		if (DGL_Input_KeyDown(VK_SPACE) && weaponCooldownTimer <= 0.0f)
		{
 			SpawnBullet();
			weaponCooldownTimer = spaceshipWeaponCooldownTime;
		}
	}

	void BehaviorSpaceship::SpawnBullet() const
	{
		Entity* entitybullet = EntityFactory::Build("Bullet");
		if (entitybullet)
		{
			Transform* t = Parent()->Get<Transform>();
			//Physics* p = Parent()->Get<Physics>();
			if (t)
			{
				Transform* bt = entitybullet->Get<Transform>();
				Physics* bp = entitybullet->Get<Physics>();
				if (bt)
				{
					bt->Translation(t->Translation());
					bt->Rotation(t->Rotation());
				}
				Vector2D direction = { std::cos(t->Rotation()), std::sin(t->Rotation()) };
				direction.Normalize();
				direction.Scale(spaceshipWeaponBulletSpeed);
				if (bp)
				{
					bp->Velocity(direction);
				}
			}
			SceneSystem::AddEntity(entitybullet);
		}
	}
	void BehaviorSpaceship::CollisionHandler(Entity* e1, const Entity* e2)
	{ 
		if (e1 && e2)
		
			if (e2->Name() == "Asteroid")
			{
				BehaviorSpaceship* s = e1->Get<BehaviorSpaceship>();
				//s->stateCurr = cSpaceshipDead;
				s->stateNext = cSpaceshipDead;
				s->timer = BehaviorSpaceship::spaceshipDeathDuration;
				//this->stateCurr = cSpaceshipDead;
			}
		}
}
#pragma endregion Private Functions

	// namespace
/*entitybullet->Add(new Transform(t));
				entitybullet->Add(new Physics(p));*/