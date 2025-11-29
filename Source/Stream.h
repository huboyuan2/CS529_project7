//------------------------------------------------------------------------------
//
// File Name:	Stream.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Class to encapsulate a stream used for reading from a file.
// 
// Attribution:	Code adapted from nlohmann/json library code samples.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string_view>
#include <functional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <dragon/assert.h>
#include <dragon/platform_dependencies.h>

#include "LoggingSystem.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

using json = nlohmann::json;

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	class Stream
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Stream(std::string_view filePath);

		// All objects need a virtual destructor to have their destructor called 
		~Stream(void);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Determines if the stream is valid.
		//
		// @return bool = true if the stream is valid, otherwise false.
		ALWAYS_INLINE bool IsValid() const { return isValid; }

		// @brief Determines if the current data node contains the requested key.
		// @brief [HINT: Use the 'contains' function.]
		//
		// @param key = The key (name) of the desired data.
		//
		// @return bool = True if the key was found, otherwise false.
		bool Contains(std::string_view key);

		void ReadArray(std::string_view key, std::function<void()> lambda);

		// @brief Reads the contents of an object by iterating through the key:value pairs.
		// @brief Specific Steps:
		// @brief   If the stream contains 'key' (the 1st parameter),
		// @brief     Traverse down the tree to the 'key' node (PushNode).
		// @brief     Iterate through the component key-value pairs (use 'dataNode->items()').
		// @brief       Invoke the lambda function, passing current key (the component Name).
		// @brief     Return to the previous location in the tree (PopNode).
		//
		// @param key = The key associated with the object (AKA value) to be read.
		// @param lambda = A function to be called for each key:value in the object.
		void ReadObject(std::string_view key, std::function<void (const std::string& key)> lambda);

		// @brief Get the requested object, pushing the previous node onto the data stack.
		// @brief Specific Steps:
		// @brief   if (Contains(key))
		// @brief     Push the 'data' pointer onto the back of the data stack.
		// @brief     Set the 'data' pointer to the address of the value "at(key)".
		void PushNode(std::string_view key);

		// @brief Pops the last stored json node, traversing back up the tree.
		// @brief Specific Steps:
		// @brief   Set the 'data' pointer to the last element of the data stack.
		// @brief   Pop the last node from the data stack.
		void PopNode();

		// @brief Attempts to read a specific value from the stream.
		// @brief [NOTE: The value will not be modified if the key does not exist.]
		//
		// @param key = Name ("key") of the data to be read.
		// @param value = Memory location to store the data.
		//
		// @return bool = true if the value was reada, otherwise false.
		bool ReadVector2D(const char* key, Vector2D& value) const
		{
			// This function should never be called without a valid stream.
			DRAGON_ASSERT(isValid, "Stream: Attempted read of invalid stream.");

			// Attempt to read data from the JSON object.
			try
			{
				std::vector<float> v;
				dataNode->at(key).get_to(v);

				value.x = v[0];
				value.y = v[1];
			}
			catch (const json::out_of_range& exception)
			{
				// NOTE: Failing to locate the key is not necessarily an error.
				// Excluding variables with default values is normal behavior.
				LoggingSystem::Verbose("Stream: JSON key error: {}", exception.what());
				return false;
			}

			return true;
		}

		// @brief Attempts to read a specific value from the stream.
		// @brief [NOTE: The value will not be modified if the key does not exist.]
		//
		// @param key = Name ("key") of the data to be read.
		// @param value = Memory location to store the data.
		//
		// @return bool = true if the value was reada, otherwise false.
		template <typename T>
		bool Read(const char* key, T& value) const
		{
			// This function should never be called without a valid stream.
			DRAGON_ASSERT(isValid, "Stream: Attempted read of invalid stream.");

			// Attempt to read data from the JSON object.
			try
			{
				value = dataNode->at(key).get<T>();
			}
			catch (const json::out_of_range& exception)
			{
				// NOTE: Failing to locate the key is not necessarily an error.
				// Excluding variables with default values is normal behavior.
				LoggingSystem::Verbose("Stream: JSON key error: {}", exception.what());
				return false;
			}

			return true;
		}

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief Open a stream for reading.
		// 
		// @brief [NOTE: This function has deliberately been made private to prevent
		//   the stream from being reused. (SRP: Single-responsibility principle)]
		//
		// @param filePath = Path to the file to be opened.
		//
		// @return bool = true if the stream was opened successfully, otherwise false.
		bool Open(std::string_view filePath);

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// Flag to indicate that the stream is valid.
		bool isValid = false;

		// A hierarchical tree containing the contents of the JSON file.
		json jsonData{};

		// Reference to the json node currently being accessed.
		const json* dataNode{ nullptr };

		// A stack used to traverse back up the hierarchical tree.
		std::vector<const json*> dataStack;

	};
}	// namespace