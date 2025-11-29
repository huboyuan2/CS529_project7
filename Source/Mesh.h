//------------------------------------------------------------------------------
//
// File Name:	Mesh.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Class for managing mesh resources.
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
	class Mesh
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Mesh(void);

		// @brief Destructor for a Mesh object.
		// @brief [NOTE: The DGL_Mesh resource is owned by this object.]
		// @brief [NOTE: The DGL_Mesh resource must be freed using DGL_Graphics_FreeMesh.]
		// @brief [HINT: Use const_cast to resolve the compiler error.]     
		~Mesh(void);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Create a "unit"-sized quad (rectangular) mesh.
		// @brief [NOTE: A unit-sized mesh extends from (-0.5,-0.5) to (0.5,0.5).]
		// @brief [HINT: Refer to the "simple, textured mesh" in DemoScene for specific information.]
		//
		// @param uSize = The width of a spritesheet cell (ranges between 0.0 and 1.0).
		// @param vSize = The height of a spritesheet cell (ranges between 0.0 and 1.0).
		// @param name = The name given to identify the mesh.
		void BuildQuad(float uSize, float vSize, std::string_view name);

		// @brief Create a "unit"-sized triangular "Spaceship" mesh.
		// @brief [NOTE: A unit-sized mesh extends from (-0.5,-0.5) to (0.5,0.5).]
		// @brief [HINT: Refer to the "Spaceship" mesh in DemoScene for specific information.]
		void BuildSpaceship();

		// @brief Render the Mesh.
		// @brief [NOTE: This function is just one step in a multi-step rendering process.]
		// @brief [HINT: This is a one-line function.]
		void Render() const;

		// @brief Read the properties associated with a mesh from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "Mesh" object (PushNode).
		// @brief   Read the mesh name from the stream.
		// @brief   If the mesh name is "Spaceship",
		// @brief     Call BuildSpaceship.
		// @brief   Else if the stream contains "Vertices",
		// @brief     Create a lambda expression for reading a single vertex from the stream.
		// @brief     https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp
		// @brief       Read the vertex position (Vector2D) from the stream.
		// @brief       Read the vertex color from the stream.
		// @brief       [HINT: Read a std::vector and initialize the color values from that.]
		// @brief       Read the vertex UV offsets (Vector2D) from the stream.
		// @brief       Added the vertex using DGL_Graphics_AddVertex.
		// @brief     Call DGL_Graphics_StartMesh.
		// @brief     Call stream.ReadArray, passing "Vertices" and the lambda expression.
		// @brief     Call DGL_Graphics_EndMesh to create the mesh resource.
		// @brief   Else if the stream contains "Quad",
		// @brief     Read "NumCols" as an unsigned int from the stream.
		// @brief     Read "NumRows" as an unsigned int from the stream.
		// @brief     Call BuildQuad to create a quad mesh with the correct UV sizes.
		// @brief   Else,
		// @brief     Log an appropriate warning message.
		// @brief   Return to the original location in the tree.
		// 
		// @note This function will be further expanded in future projects.   
		//
		// @param stream = The data stream providing the mesh data.
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
		// @brief The name of the Mesh.  This will be used later in the semester.
		std::string name;

		// @brief Pointer to a DGL_Mesh resource.
		// @brief [NOTE: This resource must be freed when the Mesh is destructed.]  
		const DGL_Mesh* meshResource{ nullptr };

		// @brief The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
		DGL_DrawMode drawMode{ DGL_DM_TRIANGLELIST };
	};

}	// namespace