//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Collider.h"

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

	Collider::Collider(void)
	{
	}

	//--------------------------------------------------------------------------

	/*Collider::~Collider(void)
	{
	}*/

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
	// @brief Register an event handler to be invoked when a collision occurs.
		// @brief [HINT: This is a simple setter function.]
		//
		// @param newHandler = Pointer to the event invoked to be called.
	void Collider::RegisterHandler(CollisionEventHandler newHandler)
	{
		handler = newHandler;
	}

	// @brief Check for a collision with another entity.
	// @brief Specific Steps:
	// @brief   If the two objects are colliding (HINT: isColliding),
	// @brief     If the first collider has a registered handler,
	// @brief       Invoke the first collider's registered handler.
	// @brief       [NOTE: Pass the FIRST entity, then the SECOND entity.]
	// @brief     If the second collider has a registered handler,
	// @brief       Invoke the second collider's registered handler.
	// @brief       [NOTE: Pass the SECOND entity, then the FIRST entity.]
	//
	// @param other = Pointer to the collider associated with the other entity.
	//
	// @return bool = True if the two colliders are intersecting, otherwise false.
	bool Collider::CheckCollision(const Collider* other) const
	{
		if (IsColliding(other))
		{
			if (handler != nullptr)
			{
				handler(Parent(), other->Parent());
			}

			if (other->handler != nullptr)
			{
				other->handler(other->Parent(), Parent());
			}
			return true;
		}

		return false;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace