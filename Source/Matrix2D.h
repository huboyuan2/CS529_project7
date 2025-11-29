//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 3
// Purpose:		Class for managing 2D transformation matrices and their operations.
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
	class Vector2D;

	// Typedefs:

	// Class Definition:
	class Matrix2D : public DGL_Mat4
	{
		// Private Static Constants:
	private:
		// @brief A static const instance of an identity matrix.
		// @brief [HINT: This can be used to make Identity() a 1-line function.]
		static const Matrix2D identity;

		// Constructors/Destructors:
	public:
		// @brief Creates an instance of a 2D transformation matrix.
		// @brief [NOTE: Ideally, the matrix is initialized as an identity matrix.]
		// @brief [HINT: This can be done using "DGL_Mat4{}" in the initializer list.]
		// @brief [HINT: The body of the constructor should be empty.]
		Matrix2D(void);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Sets the matrix equal to the identity matrix.
		// @brief [Hint: This function must initialize all matrix values.]
		void Identity();

		// @brief Creates a translation matrix from a 2D vector.
		// @brief [Hint: This function must initialize all matrix values.]
		//
		// @param v = The vector containing the translation x & y values.
		void Translate(const Vector2D& v);

		// @brief Creates a translation matrix from x & y.
		// @brief [Hint: This function must initialize all matrix values.]
		//
		// @params x, y = The translation x & y values.
		void Translate(float x, float y);

		// @brief Creates a scaling matrix from a 2D vector.
		// @brief [Hint: This function must initialize all matrix values.]
		//
		// @param v = The vector containing the scale x & y values.
		void Scale(const Vector2D& v);

		// @brief Creates a scaling matrix from x & y.
		// @brief [Hint: This function must initialize all matrix values.]
		//
		// @params x, y = The scale x & y values.
		void Scale(float x, float y);

		// @brief Creates a rotation matrix from 'angle', whose value is in degrees.
		// @brief [HINT: This function must initialize all matrix values.]
		// @brief [HINT: The conversion from degrees to radians was performed in Vector2D.cpp]
		//
		// @params angle = The rotation angle in degrees.
		void RotationDeg(float angle);

		// @brief This matrix creates a rotation matrix from 'angle', whose value is in radians.
		// @brief [Hint: This function must initialize all matrix values.]
		//
		// @params angle = The rotation angle in radians.
		void RotationRad(float angle);

		// @brief Concatenate this matrix with the matrix, 'other', resulting in a new matrix.
		Matrix2D operator*(const Matrix2D& other) const;

		// @brief Apply this transformation to the vector, 'v', resulting in a new vector.
		// @brief (NOTE: Remember to treat the implied w component as 1.)
		Vector2D operator*(const Vector2D& v) const;

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
	};

}	// namespace