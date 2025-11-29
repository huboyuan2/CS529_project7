//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.cpp
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
#include "MeshLibrary.h"
#include "Stream.h"
#include "Mesh.h"

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
	std::unordered_map<std::string, const Mesh*> MeshLibrary::meshes;
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

	MeshLibrary::MeshLibrary(void)
	{
	}

	//--------------------------------------------------------------------------

	MeshLibrary::~MeshLibrary(void)
	{
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
			// @brief Build the specified mesh or return an previously created instance of the mesh.
		// @brief Specific Steps:
		// @brief   Attempt to find the requested mesh.
		// @brief   If the mesh doesn't already exist,
		// @brief     Create a filePath by concatenating "./Data/Meshes/", meshName, and ".json".
		// @brief     Create a stream using the filePath.
		// @brief     If (the stream is valid) AND (the stream Contains("Mesh")),
		// @brief       Create a new instance of Mesh.
		// @brief       Read the contents of the mesh from the stream.
		// @brief       Add the mesh to the library.
		// @brief   Return the requested mesh, if successful.
		//
		// @param meshName = The name of the mesh to be created.
		//
		// @return Mesh* = Pointer to a new mesh, if successful, otherwise nullptr.
	const Mesh* MeshLibrary::Build(const std::string& meshName)
	{
		if (meshes.contains(meshName))
		{
			return meshes[meshName];
		}
		else
		{
			Mesh* newmesh = new Mesh();
			std::string meshpath = "./Data/Meshes/" + std::string(meshName) + ".json";
			Stream stream(meshpath);
			if (!stream.IsValid())
				return nullptr;
			if (stream.Contains("Mesh"))
			{
				newmesh->Read(stream);
				meshes.insert({ std::string(meshName), newmesh });
			}
			return newmesh;
		}
		return nullptr;
	}
	const Mesh* MeshLibrary::BuildQuad(unsigned numCols, unsigned numRows)
	{
		std::string meshName = "MeshQuad_" + std::to_string(numCols) + "x" + std::to_string(numRows);

		auto it = meshes.find(meshName);
		if (it != meshes.end())
		{
			return it->second;
		}
		Mesh* newMesh = new Mesh();
		float uSize = 1.0f / numCols;
		float vSize = 1.0f / numRows;
		newMesh->BuildQuad(uSize, vSize, meshName);
		meshes[meshName] = newMesh;
		return newMesh;
	}

	// @brief Attempt to find the requested mesh.
	// @brief [NOTE: This function has been made public for testing purposes.]
	//
	// @param meshName = The name of the mesh to find.
	//
	// @return const Mesh* = Pointer to the mesh, if found, otherwise nullptr.
	const Mesh* MeshLibrary::Find(const std::string meshName)
	{
		if (meshes.contains(meshName))
		{
			return meshes[meshName];
		}
		else return nullptr;
	}

	// @brief Delete all meshes in the library.
	// @brief [HINT: Make sure to erase the container when done deleting the meshes.]
	void MeshLibrary::DeleteAll()
	{
		for (auto mesh : meshes)
		{
			delete(mesh.second);
		}
		meshes.clear();

	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace