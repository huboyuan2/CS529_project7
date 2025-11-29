//------------------------------------------------------------------------------
//
// File Name:	Physics.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This component class is responsible for an entity's movement.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Component.h"
#include "Vector2D.h"

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
	class Physics : public Component
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Physics(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		Physics(const Physics* other);

		~Physics(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Initialize the component.
		// @brief [NOTE: This is done to avoid potential collision issues in the future.]
		// @brief Specific Steps:
		// @brief   Get the Transform component attached to the sprite's parent entity.
		// @brief   If a transform component exists,
		// @brief     Set the oldTranslation equal to the Transform's translation.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the component each frame.
		// @brief [NOTE: The semi-implicit Euler method is used to update velocity and translation.]
		// @brief Specific Steps:
		// @brief   Get the transform component from the parent entity.
		// @brief   If the transform exists,
		// @brief     Get translation from the transform component.
		// @brief     Set oldTranslation = translation
		// @brief     Use the Vector2D::ScaleAdd function to perform the following calculation:
		// @brief       velocity += acceleration * dt
		// @brief     OPTIONAL FEATURE: Scale velocity by drag.
		// @brief       [NOTE: The spaceship can be given a drag of 0.99f.  All other entities should have a drag of 1.0f.]
		// @brief     Use the Vector2D::ScaleAdd function to perform the following calculation:
		// @brief       translation += velocity * dt
		// @brief     Store the new translation in the transform component.
		// @brief [NOTE: A grade penalty will be applied if you do not use the ScaleAdd function, as stated above.]
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// Read the properties of a Physics component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "Physics" object (PushNode).
		// @brief   Read the Acceleration and Velocity values from the stream.
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// @brief Get the velocity value from the component.
		const Vector2D& Velocity() const { return velocity; }

		// @brief Get the acceleration value from the component.
		const Vector2D& Acceleration() const { return acceleration; }

		// @brief Get the rotational velocity value from the component.
		float RotationalVelocity() const { return rotationalVelocity; }

		// @brief Change the velocity value on the component.
		void Velocity(const Vector2D& velocity) { this->velocity = velocity; }

		// @brief Change the acceleration value on the component.
		void Acceleration(const Vector2D & acceleration) { this->acceleration = acceleration; }

		// @brief Get the old translation value stored during Physics::Update.
		//
		// @return Vector2D& = The entity's previous translation value.
		const Vector2D& OldTranslation() const { return oldTranslation; }

		// @brief Change the rotational velocity of the component.
		void RotationalVelocity(float newRotationalVelocity) { this->rotationalVelocity = newRotationalVelocity; }

		// @brief Set a new drag value.
		// @brief [NOTE: The use of drag is optional, but should be used ONLY for the spaceship entity.]
		void Drag(float newDrag) { drag = newDrag; }

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		Physics* Clone() const override { return new Physics(this); }

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief The component's current velocity.
		Vector2D velocity;

		// @brief The component's current acceleration.
		Vector2D acceleration;

		// @brief The entity's previous translation, used later for collision detection.
		Vector2D oldTranslation;

		// @brief The rotational velocity applied to the entity's transform ever frame.
		// @brief [HINT: transform->rotation += rotationalVelocity * dt.]
		float rotationalVelocity{ 0.0f };

		// @brief Optional variable to simulate drag.
		// @brief [NOTE: A drag of 1.0f means no drag.  A drag of 0.0f will halt all movement.]
		// @brief [NOTE: To use, multiply velocity by drag in Physics::Update.]
		float drag{ 1.0f };
	};

}	// namespace