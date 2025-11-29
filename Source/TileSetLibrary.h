//------------------------------------------------------------------------------
//
// File Name:	TileSetLibrary.h
// Author(s):	21222
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template class for a new object.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Object.h"
#include "TileSet.h"
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
	class TileSetLibrary : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		TileSetLibrary(void);

		// All objects need a virtual destructor to have their destructor called 
		virtual ~TileSetLibrary(void) override;

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		//// @brief Initialize the Object.
		//// @brief [NOTE: Some Objects may note require this step; others might.]  
		////
		//// @return bool = true if initialization successful, otherwise false.
		//bool Initialize() override { return true; };

		//// @brief Update the Object each frame.
		////
		//// @param dt = Delta time (in seconds) of the last frame.
		//void Update(float dt) override {};

		//// @brief Render the Object each frame.
		//// @brief [NOTE: Modern engines handle rendering in a more complicated way.]
		//// @brief [NOTE: Some Objects are rendered only when debug drawing is enabled.]
		//void Render() const override {};


		// 构建或获取 TileSet
		static const TileSet* Build(const std::string& tileSetName);

		// 查找 TileSet
		static const TileSet* Find(const std::string& tileSetName);

		// 删除所有 TileSet
		static void DeleteAll();
		// Public Event Handlers
	public:
		// Windows message event handler.
		//virtual bool HandleMessage(const Message& message) = 0;

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		static std::unordered_map<std::string, const TileSet*> tileSets;

	};

}	// namespace