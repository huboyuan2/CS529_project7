//------------------------------------------------------------------------------
//
// File Name:	ObjectFactory.cpp
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
#include "ObjectFactory.h"
#include "LoggingSystem.h"
#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Animation.h"
#include "BehaviorBullet.h"
#include "BehaviorSpaceship.h"
#include "BehaviorTeleporter.h"
#include "BehaviorAsteroid.h"
#include "ColliderCircle.h"
#include "BehaviorHudText.h"
#include "ColliderLine.h"
#include "TileMap.h"

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

	ObjectFactory::ObjectFactory(void)
	{
		Register("Transform", []() -> Object* { return new Transform(); });
		Register("Sprite", []() -> Object* { return new Sprite(); });
		Register("Physics", []() -> Object* { return new Physics(); });
		Register("Animation", []() -> Object* { return new Animation(); });
		Register("BehaviorBullet", []() -> Object* { return new BehaviorBullet(); });
		Register("BehaviorSpaceship", []() -> Object* { return new BehaviorSpaceship(); });
		Register("BehaviorTeleporter", []() -> Object* { return new BehaviorTeleporter(); });
		Register("BehaviorAsteroid", []() -> Object* { return new BehaviorAsteroid(); });
		Register("ColliderCircle", []() -> Object* { return new ColliderCircle(); });
		Register("BehaviorHudText", []() -> Object* { return new BehaviorHudText(); });
		Register("ColliderLine", []() -> Object* { return new ColliderLine(); });
		Register("TileMap", []() -> Object* { return new TileMap(); });	
	}

	//--------------------------------------------------------------------------

	ObjectFactory::~ObjectFactory(void)
	{
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
	// @brief Register an object constructor.
		// @brief Specific Steps:
		// @brief   If the object name has already been registered,
		// @brief     Log a warning with the exact following content:
		// @brief       "ObjectFactory::Register: Attempted to register duplicate object name: {}", objectName
		// @brief       [NOTE: The output in the log file must exactly match this text, after formatting.]
		// @brief     Return false.
		// @brief   Add the object name and constructor to the registry.
		// @brief   Return true.
		//
		// @param objectName = Name of the object associated with the provided constructor.
		// @param constructor = Function that creates an instance of the associated object.
		//
		// @return True if the object was registered successfully, otherwise false.
	bool ObjectFactory::Register(const std::string& objectName, objectConstructor constructor)
	{
		if (IsRegistered(objectName))
		{
			LoggingSystem::Warning("ObjectFactory::Register: Attempted to register duplicate object name: {}", objectName);
			return false;
		}
		registry[objectName] = constructor;
		return true;
	}

	// @brief Create the specified object.
	// @brief [NOTE: An object is constructed only if the name matches a registered constructor.]
	// @brief [HINT: Use the find() method.]
	//
	// @param objectName = Name of the object to be constructed.
	//
	// @return Object* = Pointer to the object, if constructed, otherwise nullptr.
	Object* ObjectFactory::Create(const std::string& objectName) const
	{
		auto it = registry.find(objectName);
		if (it != registry.end())
		{
			return it->second();
		}
		return nullptr;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace