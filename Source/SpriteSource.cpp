//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Boyuan HU
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
#include "SpriteSource.h"
#include "Vector2D.h"
#include <string_view>
#include "Stream.h"
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

	SpriteSource::SpriteSource(void)
	{
	}

	//--------------------------------------------------------------------------

	SpriteSource::~SpriteSource(void)
	{
		DGL_Texture* tmp = const_cast<DGL_Texture*>(textureResource);
		DGL_Graphics_FreeTexture(&tmp);
		textureResource = nullptr;
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
	// @brief Loads a texture or spritesheet resource from a file.
		//
		// @param numCols = The number of columns in a spritesheet (1 = simple texture).
		// @param numRows = The number of rows in a spritesheet (1 = simple texture).
		// @param textureName = The name of the texture file to load.
	void SpriteSource::LoadTexture(unsigned numCols, unsigned numRows, std::string_view textureName)
	{
		this->numCols = numCols;
		this->numRows = numRows;
		this->textureResource = DGL_Graphics_LoadTexture(textureName.data());
	}

	// @brief Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
	//
	// @return unsigned = The calculated frame count (numCols * numRows),
	unsigned SpriteSource::GetFrameCount() const
	{
		return numCols*numRows;
	}

	// @brief Tells the DGL to use this texture resource when rendering a mesh.
	void SpriteSource::UseTexture() const
	{
		if (!textureResource) return;
		DGL_Graphics_SetTexture(textureResource);
	}

	// @brief Calculates the UV offset for the specified frame.
	// @brief [HINT: Refer to the "Sprite Sources" slide deck for implementation details.]
	//
	// @param frameIndex = The index of the frame within a spritesheet to be displayed.
	// @param uv = A structure to be filled with the calculated UV values.
	void SpriteSource::CalculateTextureOffset(unsigned frameIndex, Vector2D& uv) const
	{

		unsigned col = frameIndex % numCols;
		unsigned row = frameIndex / numCols;
		float uSize = 1.0f / (numCols);
		float vSize = 1.0f / (numRows);
		uv.x = col * uSize;
		uv.y = row * vSize;
	}

	// @brief Calculates the UV offset for the specified frame and passes it to the DGL.
	// @brief Specific Steps:
	// @brief   Create a Vector2D variable called 'uv'.
	// @brief   Call CalculateTextureOffset
	// @brief   Call DGL_Graphics_SetCB_TextureOffset
	//
	// @param frameIndex = The index of the frame within a spritesheet to be displayed.
	void SpriteSource::SetTextureOffset(unsigned frameIndex) const
	{
		Vector2D uv;                       
		CalculateTextureOffset(frameIndex, uv);
		DGL_Graphics_SetCB_TextureOffset(&uv); 
	}
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
	void SpriteSource::Read(Stream& stream)
	{
		if (!stream.IsValid())
			return;
		stream.PushNode("SpriteSource");
		stream.Read("NumCols",numCols);
		stream.Read("NumRows",numRows);
		std::string_view name;
		stream.Read("Name",name);
		if (name != "")
		{
			std::string texture;
			stream.Read("Texture", texture);
			//spriteSourceFontSheet->LoadTexture(16, 8, "Assets/Roboto_Mono_black.png");
			LoadTexture(numCols, numRows, std::string_view("Assets/"+texture));
		}
		stream.PopNode();
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace