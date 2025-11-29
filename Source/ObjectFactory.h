//------------------------------------------------------------------------------
//
// File Name:	ObjectFactory.h
// Author(s):	dschilling, Dvanrensburg
// Course:		CS529F25
// Project:		Project 3
// Purpose:		To convert object names into instances of that object.
// Notes:
//	 This class is based upon the Abstract Factory software design pattern.
//     https://en.wikipedia.org/wiki/Abstract_factory_pattern
//   This facilitates the conversion of data files (e.g. JSON files) into
//   instances of the objects specified by the data (e.g. deserialization).
//     https://en.wikipedia.org/wiki/Serialization
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <functional>
#include <string>
#include <unordered_map>

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Object;

	// Class Definition:
	class ObjectFactory
	{
		// Typedefs:
	private:
		typedef std::function<Object* ()> objectConstructor;

		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	private:
		// @brief Register all objects to be created by the object factory.
		// @brief This includes:
		// @brief   Transform, Sprite, Physics, Animation,
		// @brief   BehaviorSpaceship, & BehaviorBullet
		// @brief [NOTE: Additional objects will be added in later projects.]
		ObjectFactory(void);

		~ObjectFactory(void);

		// Public Static Functions:
	public:

		// Singleton access.
		static ObjectFactory& GetInstance()
		{
			static ObjectFactory instance;
			return instance;
		}

		// Public Functions:
	public:
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
		bool Register(const std::string& objectName, objectConstructor constructor);

		// @brief Create the specified object.
		// @brief [NOTE: An object is constructed only if the name matches a registered constructor.]
		// @brief [HINT: Use the find() method.]
		//
		// @param objectName = Name of the object to be constructed.
		//
		// @return Object* = Pointer to the object, if constructed, otherwise nullptr.
		Object* Create(const std::string& objectName) const;

		// @brief Check if a specific object constructor has been registered.
		//
		// @param objectName = Name of the object constructor to checked.
		//
		// @return bool = true if the name is found in the registry, otherwise false.
		bool IsRegistered(const std::string& objectName) const
		{
			return registry.find(objectName) != registry.end();
		}

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
		// Registry of all object constructors, accessible by name.
		std::unordered_map<std::string, objectConstructor> registry;
	};

}	// namespace