//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 5
// Purpose:		This component class is responsible for detecting collisions
//   between two entities.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Component.h"

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
	typedef void(*CollisionEventHandler)(Entity* entityA, const Entity* entityB);

	// Class Definition:
	class Collider : public Component
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Collider(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		Collider(const Collider* other);

		~Collider(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Register an event handler to be invoked when a collision occurs.
		// @brief [HINT: This is a simple setter function.]
		//
		// @param newHandler = Pointer to the event invoked to be called.
		void RegisterHandler(CollisionEventHandler newHandler);

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
		bool CheckCollision(const Collider* other) const;

		// Protected Functions:
	protected:
		// @brief Check for a collision with another entity.
		//
		// @param other = Pointer to the collider associated with the other entity.
		//
		// @return bool = True if the two colliders are intersecting, otherwise false.
		virtual bool IsColliding(const Collider* other) const = 0;

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief A handler to be invoked when a collision is detected.
		// @brief [NOTE: This is a very basic example of event/message handling.]
		// @brief [NOTE: In future projects, this could be changed into a std::vector,
		// @brief   allowing multiple components to register handlers.]
		CollisionEventHandler handler{ nullptr };
	};

}	// namespace