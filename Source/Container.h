//------------------------------------------------------------------------------
//
// File Name:	Container.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		Container for managing objects of any type.
// Notes:
//   This class provides an example of the Visitor software design pattern.
//     https://en.wikipedia.org/wiki/Visitor_pattern
//   The owner of the container passes functions (or lambda functions) to the
//   container to be run on each active object in the container, while the
//   contents of the container remain private.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <vector>
#include <cassert>

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	template <typename T>
	class Container // Are there any benefits to inheriting from Object?
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		~Container(void);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Add an object to the container.
		// 
		bool Add(T* object);

		void DestroyAll();

		// Update the component each frame.
		// Parameters:
		//	 dt = Delta time (in seconds) of the last frame.
		void Update(int visitorFunction, float dt) {}

		// Render the component each frame.
		// [NOTE: Modern engines handle rendering in a more complicated way.]
		// [NOTE: Some components are rendered only when debug drawing is enabled.]
		void Render(int visitorFunction) const {}

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Protected Variables:
	protected:
		std::vector<T*> objects;

		// Private Variables:
	private:
	};

	template<typename T>
	inline Container<T>::~Container(void)
	{
		DestroyAll();
	}

	template<typename T>
	inline bool Container<T>::Add(T* object)
	{
		assert(object);

		objects.push_back(object);
		return false;
	}

	template<typename T>
	inline void Container<T>::DestroyAll()
	{
		for (auto& object : objects)
		{
			delete object;
			object = nullptr;
		}
	}

}	// namespace