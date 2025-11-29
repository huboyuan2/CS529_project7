//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 5
// Purpose:		This component class is responsible for detecting collisions
//   between two circle colliders.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Collider.h"

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
	class ColliderCircle : public Collider
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		ColliderCircle(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		ColliderCircle(const ColliderCircle* other);

		~ColliderCircle(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Get the radius of the circle collider.
		//
		// @return float = The radius of the circle collider.
		float Radius() const { return radius; }

		// @brief Get the radius (squared) of the circle collider.
		//
		// @return float = The radius (squared) of the circle collider.
		float RadiusSquared() const { return radius * radius; }

		// @brief Set the radius of the circle collider.
		//
		// @param float = The radius of the circle collider.
		void Radius(float newRadius) { radius = newRadius; }

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		ColliderCircle* Clone() const override { return new ColliderCircle(this); }

		// @brief Read the properties of a ColliderCircle component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "ColliderCircle" object (PushNode).
		// @brief   Read the radius value from the stream.
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// @brief Check for a collision with another entity.
		// @brief Specific Steps:
		// @brief   Cast the other pointer to a ColliderCircle*.
		// @brief   if the cast was successful,
		// @brief     Get the transforms associated with the two colliders.
		// @brief     Get the translation values associated with the two colliders.
		// @brief     Calculate the distance (squared) between the two colliders.
		// @brief     If the distance (squared) is <= radius (squared),
		// @brief       Return true.
		// @brief   Return false.
		//
		// @param other = Pointer to the collider associated with the other entity.
		//
		// @return bool = True if the two colliders are intersecting, otherwise false.
		bool IsColliding(const Collider* other) const override;

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief The radius of the circle collider.
		// @brief [NOTE: The default radius is 0.5, which gives a "unit"-sized circle (diameter = 1).]
		float radius{ 0.5f };
	};

}	// namespace