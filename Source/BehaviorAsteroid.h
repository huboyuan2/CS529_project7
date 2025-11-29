//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.h
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "template" entity.
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
	class BehaviorAsteroid : public Behavior
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		BehaviorAsteroid(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		BehaviorAsteroid(const BehaviorAsteroid* other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Read the properties of a BehaviorAsteroid component from a stream.
		// @brief [NOTE: The base Behavior variables must be read using Behavior::Read().]
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		BehaviorAsteroid* Clone() const override { return new BehaviorAsteroid(this); }

		// Behavior Finite-State Machine (FSM) functions.
		void onInit() override;
		void onUpdate(float dt) override;
		void onExit() override;
		void SetPosition();
		void SetVelocity();
		static void CollisionHandler(Entity*, const Entity*);
		// Private Constants:
	private:
		//typedef enum
		//{
		//	cInvalid = -1,	// Default state for the behavior FSM.
		//	cIdle,			// Starting state for the behavior FSM.

		//} States;
		typedef enum
		{
			cAsteroidOriginTlc,
			cAsteroidOriginTrc,
			cAsteroidOriginBlc,
			cAsteroidOriginBrc,
			cAsteroidOriginCount,

		} AsteroidOrigin;
		// Private Static Variables:
	private:
		const float asteroidSpeedMin = 50.0f;
		const float asteroidSpeedMax = 100.0f;
		static const unsigned asteroidScore;
		// Private Variables:
	private:
		AsteroidOrigin origin;
	};

}	// namespace