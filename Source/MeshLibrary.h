//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This class is responsible for managing a library of meshes.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "Object.h"

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
	class Stream;

	// Typedefs:

	// Class Definition:
	class MeshLibrary : public Object
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		MeshLibrary(void);

		// All objects need a virtual destructor to have their destructor called 
		virtual ~MeshLibrary(void) override;

		// Public Static Functions:
	public:
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
		static const Mesh* Build(const std::string& meshName);
		static const Mesh* BuildQuad(unsigned numCols, unsigned numRows);
		// @brief Attempt to find the requested mesh.
		// @brief [NOTE: This function has been made public for testing purposes.]
		//
		// @param meshName = The name of the mesh to find.
		//
		// @return const Mesh* = Pointer to the mesh, if found, otherwise nullptr.
		static const Mesh* Find(const std::string meshName);

		// @brief Delete all meshes in the library.
		// @brief [HINT: Make sure to erase the container when done deleting the meshes.]
		static void DeleteAll();

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:

		// Private Constants:
	private:

		// Private Static Variables:
	private:
		static std::unordered_map<std::string, const Mesh*> meshes;

		// Private Variables:
	private:
	};

}	// namespace