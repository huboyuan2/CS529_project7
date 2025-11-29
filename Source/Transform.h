//------------------------------------------------------------------------------
//
// File Name:	Transform.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		This component class stores an entity's position, orientation,
//   and scale within the world space.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Component.h"
#include "Matrix2D.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Stream;

	// Typedefs:

	// Class Definition:
	class Transform : public Component
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Transform(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		Transform(const Transform* other);

		~Transform(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Read the properties of a Transform component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "Transform" object (PushNode).
		// @brief   Read the translation value from the stream.
		// @brief   Read the scale value from the stream.
		// @brief   Read the rotation value from the stream.
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// @brief Calculates and returns the transformation matrix associated with
		//   the translation, scale, and rotation values.
		// @brief Specific Steps:
		// @brief if (isDirty)
		// @brief   Create a translation matrix (T).
		// @brief   Create a scale matrix (S).
		// @brief   Create a rotation matrix (R).
		// @brief   Set matrix = T * R * S
		// @brief   Set isDirty = false
		//
		// @return const Matrix2D& = The update transformation matrix.
		const Matrix2D& GetMatrix();

		// Getters:
		const Vector2D& Translation() const { return translation; }
		const Vector2D& Scale() const { return scale; }
		float Rotation() const { return rotation; }

		// Setters:
		void Translation(const Vector2D& translation);
		void Scale(const Vector2D& scale);
		void Rotation(float rotation);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		Transform* Clone() const override { return new Transform(this); }

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief The translation (or world position) of an entity.
		Vector2D translation{ 0.0f, 0.0f };

		// @brief The scale (or size) of an entity.
		// @brief [Hint: This should be initialized to (1, 1).]
		Vector2D scale{ 1.0f, 1.0f };

		// @brief The rotation (or orientation) of an entity (in radians).
		float rotation{ 0.0f };

		// @brief A flag to indicate whether or not the matrix is "dirty".
		// @brief [HINT: Set to true any time the three variables, above, are changed.]
		bool isDirty{ true };

		// @brief The matrix combining the Translation*Rotation*Scale transformations.
		Matrix2D matrix;
	};

}	// namespace