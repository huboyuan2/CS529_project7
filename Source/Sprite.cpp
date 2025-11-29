//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	Boyuan HU
// Course:		CS529F25
// Project:		Project 2
// Purpose:		This component class is responsible for ...
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Sprite.h"
#include "Component.h"
#include "DGL.h"
#include <string>
#include <string_view>
#include "Stream.h"
#include "Transform.h"
#include "Entity.h"
#include "SpriteSource.h" 
#include "Mesh.h"
#include "MeshLibrary.h"
#include "SpriteSourceLibrary.h"
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

	Sprite::Sprite(void)
		: Component()
	{

	}
	Sprite::Sprite(const Sprite* other)
	{
		this->frameIndex = other->frameIndex;
		this->alpha = other->alpha;
		this->tintColor = other->tintColor;
		this->mesh = other->mesh;
		this->spriteSource = other->spriteSource;
		this->text = other->text;
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
			// @brief Set a new frame index to be displayed by the sprite.
		// @brief Specific Steps:
		// @brief   Call LoggingSystem::Verbose, passing the format string "Sprite::SetFrame: frame index = {}" and the passed 'frame' value.
		// @brief     [NOTE: This must be done even if the passed 'frame' value is invalid.]
		// @brief   If a sprite source exists,
		// @brief     Get the frameCount from the sprite source.
		// @brief     if frame < frameCount
		// @brief       Set frameIndex = frame
		//
		// @param frame = the new frame index to be displayed.
	void Sprite::SetFrame(unsigned frame)
	{
		LoggingSystem::Verbose("Sprite::SetFrame: frame index = {}", frame);
		if (spriteSource)
		{
			unsigned frameCount = spriteSource->GetFrameCount();
			if (frame < frameCount)
			{
				frameIndex = frame;
			}
		}
	}

	// @brief Read the properties of a Sprite component from a stream.
	// @brief Specific Steps:
	// @brief   Check for valid stream (optional).
	// @brief   Traverse down the tree to the "Sprite" object (PushNode).
	// @brief   Read the frameIndex value from the stream.
	// @brief   Read the alpha value from the stream.
	// @brief   Read the "Mesh" name from the stream.
	// @brief   If the mesh name is not "",
	// @brief     Call MeshLibrary::Build.
	// @brief   Read the "SpriteSource" name from the stream.
	// @brief   If the sprite source name is not "",
	// @brief     Call SpriteSourceLibrary::Build.
	// @brief   Return to the original location in the tree (PopObject).
	//
	// @param stream = The data stream used for reading.
	void Sprite::Read(Stream& stream)
	{
		if (!stream.IsValid())
			return;
		stream.PushNode("Sprite");
		if(!stream.Read("Alpha", alpha))
			alpha = 1.0f;
		std::string meshname;
		stream.Read("Mesh", meshname);
		if (meshname != "")
		{
			mesh = MeshLibrary::Build(meshname);
		}
		std::string spritesourcename;
		stream.Read("SpriteSource", spritesourcename);
		if (spritesourcename  != "")
		{
			spriteSource = SpriteSourceLibrary::Build(spritesourcename);
		}
		if(!stream.Read("FrameIndex", frameIndex))
			frameIndex = 1;
		//std::string meshname;
		//if (stream.Read("Mesh", meshname))
		//{
		//	mesh = MeshLibrary::Build(meshname);
		//	/*if (mesh)
		//		const_cast<Mesh*>(mesh)->Read(stream);*/
		//}
		stream.PopNode();
	}
	// @brief Sets a text string to be displayed, instead of a single sprite.
		// @brief [NOTE: Empty string ("") mean display the sprite normally.]
		//
		// @param newText = The text string to be displayed.
	//void Sprite::SetText(std::string_view newText)
	//{	
	//	
	//}

		// @brief Render the component each frame.
		// @brief [NOTE: Modern engines handle rendering in a more complicated way.]
		// @brief Specific Steps:
		// @brief   Get the transform component from the parent entity.
		// @brief   If a transform component exists,
		// @brief     If the sprite has a valid SpriteSource,
		// @brief       Set the DGL shader mode to 'TEXTURE'.
		// @brief       Bind the sprite source's texture using UseTexture.
		// @brief       Set the sprite source's texture offset.
		// @brief     else
		// @brief       Set the DGL shader mode to 'COLOR'.
		// @brief     Pass the alpha value to the DGL.
		// @brief     Pass the tint color to the DGL.
		// @brief     if (text == "")
		// @brief       Get the transform matrix.
		// @brief       Call DGL_Graphics_SetCB_TransformMatrix.
		// @brief       Render the mesh.
		// @brief     else
		// @brief       Get a copy of the transform matrix.
		// @brief       Create an translation matrix that shifts the next character by scale.x.
		// @brief       For each character in text.
		// @brief         Zero-base the character by subtracting ' '.
		// @brief         Set the sprite source's texture offset.
		// @brief         Call DGL_Graphics_SetCB_TransformMatrix.
		// @brief         Render the mesh.
		// @brief         Concatenate the offset matrix with the transformation matrix.
	
	void Sprite::Render() const
	{
		Transform* transform = Parent() ? Parent()->Get<Transform>() : nullptr;
		if (transform)
		{
			if (spriteSource)
			{
				DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE,DGL_VSM_DEFAULT);
				spriteSource->UseTexture();
				spriteSource->SetTextureOffset(frameIndex);
				//DGL_Graphics_SetTextureOffset(spriteSource->GetOffset());
			}
			else
			{
				DGL_Graphics_SetShaderMode(DGL_PSM_COLOR,DGL_VSM_DEFAULT);
				
			}
			if (text == "")
			{
				DGL_Graphics_SetCB_Alpha(alpha);
				DGL_Graphics_SetCB_TintColor(&tintColor);
				DGL_Graphics_SetCB_TransformMatrix(&transform->GetMatrix());

				if (mesh)
					mesh->Render();
			}
			else
			{
					// @brief       Get a copy of the transform matrix.
					// @brief       Create an translation matrix that shifts the next character by scale.x.
					// @brief       For each character in text.
					// @brief         Zero-base the character by subtracting ' '.
					// @brief         Set the sprite source's texture offset.
					// @brief         Call DGL_Graphics_SetCB_TransformMatrix.
					// @brief         Render the mesh.
				Matrix2D matrix = transform->GetMatrix();
				Matrix2D offset;
				//offset.Translate(transform->Scale().x, 0);
				offset.Translate(1.0f, 0);
				for (char c : text)
				{
					unsigned charIndex = static_cast<unsigned>(c - ' ');
					if (spriteSource)
						spriteSource->SetTextureOffset(charIndex);

					DGL_Graphics_SetCB_TransformMatrix(&matrix);
					if (mesh)
						mesh->Render();

					matrix = matrix * offset;
				}
			}
			/*DGL_Graphics_SetAlpha(alpha);
			DGL_Graphics_SetTintColor(tintColor);
			DGL_Graphics_SetTransformData(*transform);
			DGL_Graphics_RenderMesh(*mesh);*/
		}
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace