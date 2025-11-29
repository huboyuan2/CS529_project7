//------------------------------------------------------------------------------
//
// File Name:	SimpleTextFileChannel.cpp
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Derived channel for customing the messages written to the text file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <string_view>

#include <dragon/logging/TextFileChannel.h>
#include <dragon/strings/format.h>

#include "SimpleTextFileChannel.h"

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

	SimpleTextFileChannel::SimpleTextFileChannel(std::string_view const channelName)
		: TextFileChannel(channelName)
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

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	std::optional<std::string> SimpleTextFileChannel::formatMessage(
		std::chrono::utc_clock::time_point utc_event_time,
		std::string_view subsystem,
		logging::Level level,
		std::string_view message,
		bool withNewline) const
	{
		// Output the message without any timestamp information.
		// This makes comparing the actual output with the expected output much easier.
		return std::format("{1}/{2}: [{3}] {4}{5}", utc_event_time, name(), subsystem, level, message, withNewline ? "\n" : "");
	}

#pragma endregion Private Functions

}	// namespace