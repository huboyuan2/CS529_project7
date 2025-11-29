//------------------------------------------------------------------------------
//
// File Name:	Mesh.cpp
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
#include <algorithm>            // for std::max / std::min
#include "Mesh.h"
#include "DGL.h"
#include <string>
#include <string_view>
#include "Stream.h"
#include "Color.h"
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

	Mesh::Mesh(void)
	{
	}

	//--------------------------------------------------------------------------

	Mesh::~Mesh(void)
	{
		DGL_Mesh* tmp = const_cast<DGL_Mesh*>(meshResource);
		DGL_Graphics_FreeMesh(&tmp);
		meshResource = nullptr;
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
			// @brief Read the properties associated with a mesh from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "Mesh" object (PushNode).
		// @brief   Read the mesh name from the stream.
		// @brief   If the mesh name is "Spaceship",
		// @brief     Call BuildSpaceship.
		// @brief   Else,
		// @brief     Log an appropriate warning message.
		// @brief   Return to the original location in the tree.
		// 
		// @note This function will be further expanded in future projects.   
		//
		// @param stream = The data stream providing the mesh data.
	void Mesh::Read(Stream& stream)
	{	
		if (!stream.IsValid())
			return;
		stream.PushNode("Mesh");
		std::string meshname;
		if (stream.Read("Name", meshname))
		{
			if (meshname == "MeshSpaceship")
				BuildSpaceship();
				
				//
			else if (stream.Contains("Vertices"))
			{
				// free old mesh
				if (meshResource)
				{
					DGL_Mesh* tmp = const_cast<DGL_Mesh*>(meshResource);
					DGL_Graphics_FreeMesh(&tmp);
					meshResource = nullptr;
				}

				// collect vertex data in containers
				std::vector<Vector2D> positions;
				std::vector<Color> colors;
				std::vector<Vector2D> uvs;

				auto readVertex = [&]() {
					Vector2D position, uv;
					std::vector<float> colorVec;
					
					if (stream.ReadVector2D("Position", position) &&
						stream.Read("Color", colorVec) &&
						stream.ReadVector2D("UV", uv))
					{
						positions.push_back(position);
						colors.emplace_back(
							colorVec.size() > 0 ? colorVec[0] : 1.0f,
							colorVec.size() > 1 ? colorVec[1] : 1.0f,
							colorVec.size() > 2 ? colorVec[2] : 1.0f,
							colorVec.size() > 3 ? colorVec[3] : 1.0f
						);
						uvs.push_back(uv);
					}
				};

				// Read all vertices
				stream.ReadArray("Vertices", readVertex);

				// build triangles fan
				if (positions.size() >= 3)
				{
					DGL_Graphics_StartMesh();
					
					//set the first vertex as the center, build triangles fan
					for (size_t i = 1; i < positions.size() - 1; ++i)
					{
						DGL_Graphics_AddTriangle(
							&positions[0], &colors[0], &uvs[0],   // center vertex
							&positions[i], &colors[i], &uvs[i],   // current vertex
							&positions[i + 1], &colors[i + 1], &uvs[i + 1]  // next vertex
						);
					}
					
					meshResource = DGL_Graphics_EndMesh();
					drawMode = DGL_DM_TRIANGLELIST;
				}
			}
			//
			else if (stream.Contains("Quad"))
			{
				float rows,cols;
				//std::string meshname;
				stream.Read("NumRows", rows);
				stream.Read("NumCols", cols);
				//stream.Read("Name", meshname);
				BuildQuad(1.0f / cols, 1.0f / rows, meshname);
			}
				
		}
		stream.PopNode();

	}
		
			// @brief Create a "unit"-sized quad (rectangular) mesh.
		// @brief [NOTE: A unit-sized mesh extends from (-0.5,-0.5) to (0.5,0.5).]
		// @brief [HINT: Refer to the "simple, textured mesh" in DemoScene for specific information.]
		//
		// @param uSize = The width of a spritesheet cell (ranges between 0.0 and 1.0).
		// @param vSize = The height of a spritesheet cell (ranges between 0.0 and 1.0).
		// @param name = The name given to identify the mesh.
	void Mesh::BuildQuad(float uSize, float vSize, std::string_view name)
	{
		// Store mesh name.
		this->name = std::string(name);

		// Clamp UV cell size (defensive ¨C ensures valid range).
		uSize = std::max(0.0f, std::min(1.0f, uSize));
		vSize = std::max(0.0f, std::min(1.0f, vSize));

		// Free any previously built mesh.
		if (meshResource)
		{
			DGL_Mesh* tmp = const_cast<DGL_Mesh*>(meshResource);
			DGL_Graphics_FreeMesh(&tmp);
			meshResource = nullptr;
		}

		// Position constants (same as DemoScene's simple, textured mesh).
		static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f,  0.5f };
		static const DGL_Vec2 Vertex_Pos_Trc = {  0.5f,  0.5f };
		static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };
		static const DGL_Vec2 Vertex_Pos_Brc = {  0.5f, -0.5f };

		// UVs scaled by the supplied cell size (supports spritesheets).
		DGL_Vec2 uvTlc{ 0.0f, 0.0f };
		DGL_Vec2 uvTrc{ uSize, 0.0f };
		DGL_Vec2 uvBlc{ 0.0f, vSize };
		DGL_Vec2 uvBrc{ uSize, vSize };
		DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		// Build two triangles (same winding/order as DemoScene).
		DGL_Graphics_StartMesh();
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &uvBlc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &uvTrc,
			&Vertex_Pos_Brc, &DGL_Color_Black, &uvBrc);
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &uvBlc,
			&Vertex_Pos_Tlc, &DGL_Color_Black, &uvTlc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &uvTrc);

		meshResource = DGL_Graphics_EndMesh();
		drawMode = DGL_DM_TRIANGLELIST;
	}

	// @brief Create a "unit"-sized triangular "Spaceship" mesh.
	// @brief [NOTE: A unit-sized mesh extends from (-0.5,-0.5) to (0.5,0.5).]
	// @brief [HINT: Refer to the "Spaceship" mesh in DemoScene for specific information.]
	void Mesh::BuildSpaceship()
	{
		if (meshResource)
		{
			DGL_Mesh* tmp = const_cast<DGL_Mesh*>(meshResource);
			DGL_Graphics_FreeMesh(&tmp);
			meshResource = nullptr;
		}


		static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f,  0.5f };
		static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };
		static const DGL_Vec2 Vertex_Pos_Right = { 0.5f, 0.0f };
		static const DGL_Vec2 Vertex_UV_Zero = { 0.0f, 0.0f };
		// UVs scaled by the supplied cell size (supports spritesheets).

		DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
		DGL_Graphics_StartMesh();
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Right, &DGL_Color_Yellow, &Vertex_UV_Zero,
			&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
			&Vertex_Pos_Tlc, &DGL_Color_Red, &Vertex_UV_Zero);
		meshResource = DGL_Graphics_EndMesh();
		drawMode = DGL_DM_TRIANGLELIST;
	}

	// @brief Render the Mesh.
	// @brief [NOTE: This function is just one step in a multi-step rendering process.]
	// @brief [HINT: This is a one-line function.]
	void Mesh::Render() const 
	{
		if (meshResource)
			DGL_Graphics_DrawMesh(meshResource, DGL_DM_TRIANGLELIST);
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace