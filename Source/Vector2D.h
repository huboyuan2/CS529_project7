//------------------------------------------------------------------------------
//
// File Name:	Vector2D.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Class for managing 2D points and vectors.
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
	class Vector2D : public DGL_Vec2
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(DGL_Vec2 v) : Vector2D(v.x, v.y) {};

		Vector2D(const Vector2D& other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief This function sets the coordinates of the 2D vector to 0.
		void Zero();

		// @brief This function sets the coordinates of the 2D vector to x & y
		//
		// @param x = The new x-coordinate.
		// @param y = The new y-coordinate.
		void Set(float x, float y);

		// @brief This function negates the coordinates of the 2D vector (e.g. x = -x & y = -y).
		void Negate();

		// @brief This function adds two vectors together (vector += offset).
		// 
		// @param offset = The offset to be added to the 2D vector.
		void Add(const Vector2D& offset);

		// @brief This function subtracts one vector from another (vector -= offset)
		// 
		// @param offset = The offset to be subtracted from the 2D vector.
		void Sub(const Vector2D& offset);

		// @brief This function normalizes the 2D vector (vector = vector / length(vector)).
		void Normalize();

		// @brief This function scales a vector by 'scale' (vector *= scale).
		//
		// @param scale = The value by which to scale the vector.
		void Scale(float scale);

		// @brief This function adds (scale * offset) to the 2D vector.
		//
		// @param scale = The value by which to scale the offset.
		// @param offset = The offset to be added to the 2D vector.
		void ScaleAdd(float scale, const Vector2D& offset);

		// @brief This function subtracts (scale * offset) from the 2D vector.
		//
		// @param scale = The value by which to scale the offset.
		// @param offset = The offset to be subtracted from the 2D vector.
		void ScaleSub(float scale, const Vector2D& offset);

		// @brief This function calculates the length of the 2D vector.
		//
		// @return float = The length of the 2D vector.
		float Length() const;

		// @brief This function calculates the squared length of the 2D vector.
		// @brief [NOTE: The square root function must NOT be called during this function.]
		//
		// @return float = The squared length of the 2D vector.
		float SquareLength() const;

		// @brief This function calculates the distance between two points (||p2 - this||).
		//
		// @return float = The distance between the two points.
		float Distance(const Vector2D& point2) const;

		// @brief This function calculates the squared distance between two points.
		// @brief [NOTE: The square root function must NOT be called during this function.]
		//
		// @return float = The squared distance between the two points.
		float SquareDistance(const Vector2D& point2) const;

		// @brief This function returns the dot product between two vectors.
		//
		// @return The dot product result (this 'dot' vector2).
		float DotProduct(const Vector2D& vector2) const;

		// @brief This function computes the coordinates of the unit vector represented by the angle "angle", which is in Degrees.
		// @brief Converting from degrees to radians can be performed as follows:
		// @brief   #include <numbers>
		// @brief   radians = (angle * std::numbers::pi) / 180.0f
		void FromAngleDeg(float angle);

		// @brief This function computes the coordinates of the unit vector represented by the angle "angle", which is in Radians.
		// @brief HINT: x = std::cosf(angle), y = std::sinf(angle).
		void FromAngleRad(float angle);

		// @brief This function computes the angle, in radians, of the specified vector.
		// @brief HINT: Angle (radians) = std::atan2f(y, x).
		float ToAngleRad() const;

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
	};

}	// namespace