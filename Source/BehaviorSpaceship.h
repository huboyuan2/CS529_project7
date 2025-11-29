//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "spaceship" entity.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Behavior.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Stream;

	// Typedefs:

	// Class Definition:
	class BehaviorSpaceship : public Behavior
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		BehaviorSpaceship(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		BehaviorSpaceship(const BehaviorSpaceship* other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// Read the properties of a BehaviorSpaceship component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "BehaviorSpaceship" object (PushNode).
		// @brief   Read component-specific data here.
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		BehaviorSpaceship* Clone() const override { return new BehaviorSpaceship(this); }

		// Behavior Finite-State Machine (FSM) functions.
		void onInit() override;
		void onUpdate(float dt) override;
		void onExit() override;
		
		// @brief Update the rotation of the spaceship, based upon keyboard input.
		void UpdateRotation() const;

		// @brief Update the velocity, applying an acceleration in the direction of the ship.
		void UpdateVelocity(float dt) const;

		// @brief Update the weapon firing, based upon keyboard input.
		void UpdateWeapon(float dt);

		void SpawnBullet() const;
		static void CollisionHandler(Entity*, const Entity*);
		// Private Constants:
	private:
		typedef enum
		{
			cSpaceshipInvalid = -1,	// Spaceship has not yet been initialized.
			cSpaceshipIdle,			// Spaceship is drifting in space.
			cSpaceshipThrust,		// Spaceship is accelerating.
			cSpaceshipReverse,		// Spaceship is decelerating.
			cSpaceshipDead,			// Spaceship is dead and lifeless, drifting in space
			cSpaceshipRespawn,		// Spaceship is being respawned.

		} States;

		// Private Static Variables:
	private:
		static const float spaceshipAcceleration;
		static const float spaceshipSpeedMax;
		static const float spaceshipTurnRateMax;
		static const float spaceshipWeaponCooldownTime;
		static const float spaceshipWeaponBulletSpeed;
		static const float spaceshipDeathDuration;
		// Private Variables:
	private:
	};

}	// namespace