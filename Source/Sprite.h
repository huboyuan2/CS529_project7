//------------------------------------------------------------------------------
//
// File Name:	Sprite.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		This component class is responsible for an entity's sprite information.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string>
#include <string_view>

#include "DGL.h"

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
	class Mesh;
	class SpriteSource;
	class Stream;

	// Typedefs:

	// Class Definition:
	class Sprite : public Component
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Sprite(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		Sprite(const Sprite* other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
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
		void Render() const override;

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
		void Read(Stream& stream);

		// @brief Get the alpha value from the component.
		float Alpha() const { return alpha; }

		// @brief Change the alpha value on the component.
		void Alpha(float alpha) { this->alpha = alpha; }

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
		void SetFrame(unsigned frame);

		// @brief Attach a mesh to the component.
		void SetMesh(const Mesh* mesh) { this->mesh = mesh; }

		// @brief Attach a sprite source to the component.
		void SetSpriteSource(const SpriteSource* spriteSource) { this->spriteSource = spriteSource; }

		// @brief Sets a text string to be displayed, instead of a single sprite.
		// @brief [NOTE: Empty string ("") mean display the sprite normally.]
		//
		// @param newText = The text string to be displayed.
		void SetText(std::string_view newText) { text = newText; }

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		Sprite* Clone() const override { return new Sprite(this); }

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief The frame currently being displayed on a spritesheet.
		unsigned frameIndex{ 0 };

		// @brief The sprite's transparency (alpha) value.
		float alpha{ 1.0f };

		// @brief The tint color to apply to a rendered mesh.
		// @brief [NOTE: The components are RGB + (Blend %).]
		DGL_Color tintColor{ 0.0f, 0.0f, 0.0f, 0.0f };

		// @brief The sprite's mesh used for rendering.
		const Mesh* mesh{ nullptr };

		// @brief The sprite's texture (SpriteSource) used for rendering.
		// @brief [NOTE: When set to nullptr, the sprite will be rendered untextured.]
		const SpriteSource* spriteSource{ nullptr };

		// @brief A sequence of text to be displayed, instead of a single sprite.
		// @brief [NOTE: Empty string ("") mean display the sprite normally.]
		std::string text{ "" };
	};

}	// namespace