//------------------------------------------------------------------------------
//
// File Name:	Color.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 5
// Purpose:		This class is responsible for defining and managing colors.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "DGL.h"

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
	class Color : public DGL_Color
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		// @brief Construct a new color object, set to white.
		// @brief [NOTE: Initialize the RGBA values to 1.0f.]
		Color();

		// @brief Construct a new color object, set to specific RGBA values.
		Color(float _r, float _g, float _b, float _a);

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Public Static Constants:
	public:
		// The following color values can be used for setting the background color in scenes.
		static const Color Black;  // RGBA = (0, 0, 0, 1)
		static const Color White;  // RGBA = (1, 1, 1, 1)

		// The following color values are OPTIONAL.
		// [NOTE: You are permitted to add these or other color values.]
		//static const Color Red;
		//static const Color Green;
		//static const Color Blue;
		//static const Color Cyan;
		//static const Color Yellow;
		//static const Color Magenta;

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
	};

}	// namespace