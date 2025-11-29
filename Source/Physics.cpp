//------------------------------------------------------------------------------
//
// File Name:	Physics.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Physics.h"
#include "Component.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Transform.h"
#include "Entity.h"
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

	Physics::Physics(void)
	{

	}
	//shallow copy
	Physics::Physics(const Physics* other)
	{
		this->velocity = other->velocity;
		this->acceleration = other->acceleration;
		this->oldTranslation = other->oldTranslation;
		this->rotationalVelocity = other->rotationalVelocity;

	}
	//--------------------------------------------------------------------------

	//Physics::~Physics(void)
	//{
	//}

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
	// @brief Initialize the component.
		// @brief [NOTE: This is done to avoid potential collision issues in the future.]
		// @brief Specific Steps:
		// @brief   Get the Transform component attached to the sprite's parent entity.
		// @brief   If a transform component exists,
		// @brief     Set the oldTranslation equal to the Transform's translation.
		//
		// @return bool = true if initialization successful, otherwise false.
	bool Physics::Initialize()
	{	
		Transform* transform = Parent() ? Parent()->Get<Transform>() : nullptr;
		if (transform)
		{
			oldTranslation = transform->Translation();
		}
		return true;
	}

	// @brief Update the component each frame.
	// @brief [NOTE: The semi-implicit Euler method is used to update velocity and translation.]
	// @brief Specific Steps:
	// @brief   Get the transform component from the parent entity.
	// @brief   If the transform exists,
	// @brief     Get translation from the transform component.
	// @brief     Set oldTranslation = translation
	// @brief     Use the Vector2D::ScaleAdd function to perform the following calculation:
	// @brief       velocity += acceleration * dt
	// @brief     Use the Vector2D::ScaleAdd function to perform the following calculation:
	// @brief       translation += velocity * dt
	// @brief     Store the new translation in the transform component.
	// @brief [NOTE: A grade penalty will be applied if you do not use the ScaleAdd function, as stated above.]
	//
	// @param dt = Delta time (in seconds) of the last frame.
	void Physics::Update(float dt)
	{
		if (dt <= 0.0f) return;

		Transform* t = Parent() ? Parent()->Get<Transform>() : nullptr;
		if (!t) return;

		Vector2D translation = t->Translation();
		
		oldTranslation = translation;

		//velocity.ScaleAdd(dt, acceleration); // v += a*dt
		//translation.ScaleAdd(dt, velocity);  // x += v*dt
		
		velocity.x += acceleration.x * dt;
		velocity.y += acceleration.y * dt;
		velocity.Scale(drag);
		translation.x += velocity.x * dt;
		translation.y += velocity.y * dt;
		t->Rotation(t->Rotation() + rotationalVelocity * dt);
		t->Translation(translation);
		LoggingSystem::Verbose("Translation: {} {}", translation.x, translation.y);
	}

	// Read the properties of a Physics component from a stream.
	// @brief Specific Steps:
	// @brief   Check for valid stream (optional).
	// @brief   Traverse down the tree to the "Physics" object (PushNode).
	// @brief   Read component-specific data here.
	// @brief   Return to the original location in the tree (PopObject).
	//
	// @param stream = The data stream used for reading.
	void Physics::Read(Stream& stream)
	{
		if (!stream.IsValid())
		{
			return;
		}
		stream.PushNode("Physics");
		// Read the velocity value from the stream.
		if(!stream.ReadVector2D("Velocity", velocity))
		{
			velocity.Zero();
		}
		// Read the acceleration value from the stream.
		if(!stream.ReadVector2D("Acceleration", acceleration))
		{
			acceleration.Zero();
		}
		// Return to the previous location in the tree.
		stream.PopNode();
	}

	//// @brief Get the velocity value from the component.
	//const Vector2D& Physics::Velocity() const { return velocity; }

	//// @brief Get the acceleration value from the component.
	//const Vector2D& Physics::Acceleration() const { return acceleration; }

	//// @brief Change the velocity value on the component.
	//void Physics::Velocity(const Vector2D& velocity) { this->velocity = velocity; }

	//// @brief Change the acceleration value on the component.
	//void Physics::Acceleration(const Vector2D& acceleration) { this->acceleration = acceleration; }

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace