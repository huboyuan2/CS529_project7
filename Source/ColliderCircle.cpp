//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
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
#include "ColliderCircle.h"
#include "Stream.h"
#include "Transform.h"
#include "Entity.h"
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

	ColliderCircle::ColliderCircle(void)
	{
	}
	ColliderCircle::ColliderCircle(const ColliderCircle* other)
	{
		this->radius = other->radius;
	}
	//--------------------------------------------------------------------------

	/*ColliderCircle::~ColliderCircle(void)
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


#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions
		// @brief Read the properties of a ColliderCircle component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "ColliderCircle" object (PushNode).
		// @brief   Read the radius value from the stream.
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
	void ColliderCircle::Read(Stream& stream)
	{
		if (stream.IsValid() && stream.Contains("ColliderCircle"))
		{
			stream.PushNode("ColliderCircle");
			stream.Read("Radius", radius);
			stream.PopNode();
		}
	}


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
	// @return bool = True if the two colliders are intersecting, otherwise false.
	bool ColliderCircle::IsColliding(const Collider* other) const
	{
		const ColliderCircle* otherCircle = dynamic_cast<const ColliderCircle*>(other);
		if (otherCircle)
		{
			Transform* myt = Parent()->Get<Transform>();
			Transform* othert = other->Parent()->Get<Transform>();
			float squareddistance = myt->Translation().SquareDistance(othert->Translation());
			if (squareddistance <= (radius+otherCircle->Radius())* (radius + otherCircle->Radius()))
			{
				if(squareddistance>0.01)
				return true;
			}
		}
		return false;
	}
#pragma endregion Private Functions

}	// namespace