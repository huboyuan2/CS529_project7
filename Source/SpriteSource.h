//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Class for managing sprite sources and textures.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string_view>

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

struct DGL_Texture;

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Stream;
	class Vector2D;

	// Typedefs:

	// Class Definition:
	class SpriteSource
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		SpriteSource(void);

		// All objects need a virtual destructor to have their destructor called 
		~SpriteSource(void);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Loads a texture or spritesheet resource from a file.
		//
		// @param numCols = The number of columns in a spritesheet (1 = simple texture).
		// @param numRows = The number of rows in a spritesheet (1 = simple texture).
		// @param textureName = The name of the texture file to load.
		void LoadTexture(unsigned numCols, unsigned numRows, std::string_view textureName);

		// @brief Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
		//
		// @return unsigned = The calculated frame count (numCols * numRows),
		unsigned GetFrameCount() const;

		// @brief Tells the DGL to use this texture resource when rendering a mesh.
		void UseTexture() const;

		// @brief Calculates the UV offset for the specified frame.
		// @brief [HINT: Refer to the "Sprite Sources" slide deck for implementation details.]
		//
		// @param frameIndex = The index of the frame within a spritesheet to be displayed.
		// @param uv = A structure to be filled with the calculated UV values.
		void CalculateTextureOffset(unsigned frameIndex, Vector2D& uv) const;

		// @brief Calculates the UV offset for the specified frame and passes it to the DGL.
		// @brief Specific Steps:
		// @brief   Create a Vector2D variable called 'uv'.
		// @brief   Call CalculateTextureOffset
		// @brief   Call DGL_Graphics_SetCB_TextureOffset
		//
		// @param frameIndex = The index of the frame within a spritesheet to be displayed.
		void SetTextureOffset(unsigned frameIndex) const;

		// @brief Reads the properties of a SpriteSource from a stream..
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "SpriteSource" object (PushNode).
		// @brief   Read the numCols and numRows values from the stream.
		// @brief   Read the name of the texture from the stream.
		// @brief   If the texture name is not "",
		// @brief     Call LoadTexture.
		// @brief  Return to the original location in the tree.
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

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
		// @brief The number of columns in a spritesheet (= 1 for a simple texture).
		unsigned numCols{ 1 };

		// @brief The number of rows in a spritesheet (= 1 for a simple texture).
		unsigned numRows{ 1 };

		// @brief Pointer to a DGL_Texture resource.
		const DGL_Texture* textureResource{ nullptr };
	};

}	// namespace