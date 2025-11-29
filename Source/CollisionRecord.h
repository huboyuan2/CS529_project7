//------------------------------------------------------------------------------
//
// File Name:	CollisionRecord.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 6
// Purpose:		This class is responsible for tracking the information asssociated
//   with a collision.  May be used as a payload for a collision event/message.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <limits>

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
	class Collider;
	class Entity;

	// Typedefs:

	// Class Definition:
	class CollisionRecord
	{
		// Public Constants and Enums:
	public:
		const float NoCollision = std::numeric_limits<float>::infinity();

		// Constructors/Destructors:
	public:
		CollisionRecord(const Entity* _entityA, const Entity* _entityB, const Vector2D& _Bs, const Vector2D& _Be)
			: entityA(_entityA)
			, entityB(_entityB)
			, Bs(_Bs)
			, Be(_Be)
		{
		}

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		void Reset() { ti = NoCollision; };

		// @brief Update the collision record with a new, potential point of intersection.
		//
		// @param _ti = New time of intersection.
		// @param _Bi = New point of intersection.
		// @param _n = New normal at the point of intersection.
		void Update(float _ti, const Vector2D& _Bi, const Vector2D& _n)
		{
			// If the new time of intersection is less than the previously stored value,
			if (_ti <= ti)
			{
				// Update the collision record with new, valid data.
				ti = _ti;
				Bi = _Bi;
				n = _n;
			}
		}

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Public Variables:
	public:
		float ti{ NoCollision };
		Vector2D Bs{};
		Vector2D Be{};
		Vector2D Bi{};
		Vector2D n{};

		// @brief Pointer to the first entity involved in the collision.
		// @brief [NOTE: In this implementation, this would be the moving (circle) entity.]
		const Entity* entityA{ nullptr };

		// @brief Pointer to the second entity involved in the collision.
		// @brief [NOTE: Technically, theis pointer is not required for the existing implementation.
		// @brief   However, in a more advanced implementation, this information would be necessary
		// @brief   in order to obtain velocity and mass properties.]
		const Entity* entityB{ nullptr };

		// Private Static Variables:
	private:

		// Private Variables:
	private:
	};

}	// namespace