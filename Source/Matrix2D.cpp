//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.cpp
// Author(s):	Boyuan Hu
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
#include "Matrix2D.h"
#include "Vector2D.h"
#include <cmath>
#include "DGL.h"
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

	Matrix2D::Matrix2D(void)
	{
	}

	//--------------------------------------------------------------------------

	//Matrix2D::~Matrix2D(void)
	//{
	//}

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
			// @brief Sets the matrix equal to the identity matrix.
		// @brief [Hint: This function must initialize all matrix values.]
	void Matrix2D::Identity()
	{
		for( int row=0 ;row<4; row++)
		{
			for(int column=0; column<4; column++)
			{
				if(row==column)
					m[row][column]=1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
	}

	// @brief Creates a translation matrix from a 2D vector.
	// @brief [Hint: This function must initialize all matrix values.]
	//
	// @param v = The vector containing the translation x & y values.
	void Matrix2D::Translate(const Vector2D& v)
	{
		for( int row=0 ;row<4; row++)
		{
			for(int column=0; column<4; column++)
			{
				if(row==column)
					m[row][column]=1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
		m[0][3] = v.x;
		m[1][3] = v.y;
	}

	// @brief Creates a translation matrix from x & y.
	// @brief [Hint: This function must initialize all matrix values.]
	//
	// @params x, y = The translation x & y values.
	void Matrix2D::Translate(float x, float y)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (row == column)
					m[row][column] = 1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
		m[0][3] = x;
		m[1][3] = y;
	}
	// @brief Creates a scaling matrix from a 2D vector.
	// @brief [Hint: This function must initialize all matrix values.]
	//
	// @param v = The vector containing the scale x & y values.
	void Matrix2D::Scale(const Vector2D& v)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (row == column)
					m[row][column] = 1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
		m[0][0] = v.x;
		m[1][1] = v.y;
	}
	// @brief Creates a scaling matrix from x & y.
	// @brief [Hint: This function must initialize all matrix values.]
	//
	// @params x, y = The scale x & y values.
	void Matrix2D::Scale(float x, float y)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (row == column)
					m[row][column] = 1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
		m[0][0] = x;
		m[1][1] = y;
	}
	// @brief Creates a rotation matrix from 'angle', whose value is in degrees.
	// @brief [HINT: This function must initialize all matrix values.]
	// @brief [HINT: The conversion from degrees to radians was performed in Vector2D.cpp]
	//
	// @params angle = The rotation angle in degrees.
	void Matrix2D::RotationDeg(float angle)
	{
				float rad = angle * (3.14159f / 180.0f);
        // Add this at the top of the file, after the other includes

		float cos = cosf(rad);
		float sin = sinf(rad);

		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (row == column)
					m[row][column] = 1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
		m[0][0] = cos;
		m[0][1] = -sin;
		m[1][0] = sin;
		m[1][1] = cos;
	}

	// @brief This matrix creates a rotation matrix from 'angle', whose value is in radians.
	// @brief [Hint: This function must initialize all matrix values.]
	//
	// @params angle = The rotation angle in radians.
	void Matrix2D::RotationRad(float angle)
	{
				float cos = cosf(angle);
		float sin = sinf(angle);

		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (row == column)
					m[row][column] = 1.0f;
				else
					m[row][column] = 0.0f;
			}
		}
		m[0][0] = cos;
		m[0][1] = -sin;
		m[1][0] = sin;
		m[1][1] = cos;
	}

	// @brief Concatenate this matrix with the matrix, 'other', resulting in a new matrix.
	Matrix2D Matrix2D::operator*(const Matrix2D& other) const
	{
		Matrix2D result;
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				result.m[row][column] = 0.0f;
				for (int k = 0; k < 4; k++)
				{
					result.m[row][column] += m[row][k] * other.m[k][column];
				}
			}
		}
		return result;
	}

	// @brief Apply this transformation to the vector, 'v', resulting in a new vector.
	// @brief (NOTE: Remember to treat the implied w component as 1.)
	Vector2D Matrix2D::operator*(const Vector2D& v) const
	{
		Vector2D result;
		result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][3];
		result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][3];
		return result;
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace