//------------------------------------------------------------------------------
//
// File Name:	SimpleTextFileChannel.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Derived channel for customing the messages written to the text file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <string_view>

#include <dragon/logging/TextFileChannel.h>

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

namespace logging = dragon::logging;

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	class SimpleTextFileChannel : public logging::TextFileChannel
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		// @brief Constructor for a custom text file channel that filters out timestamp information.
		//
		// @param channelName	A name assigned to the channel.
		SimpleTextFileChannel(std::string_view const channelName);

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief Formats a log entry into a human-readable string.
		//
		// @param utc_event_time the UTC timestamp of the logging event
		// @param subsystem A short identifier for the originating subsystem (e.g., "network", "audio", "physics").
		// @param level The severity level of the message (e.g., Info, Warning, Error).
		// @param message The raw message content to be formatted.
		// @param withNewline requests a newline character at the end of the result; default false
		//
		// @return A formatted string suitable for logging output.
		// @return Return a std::nullopt to supress the event from the log.
		//
		// @note derived implementations should be writtem to be thread-safe on this object
		std::optional<std::string> formatMessage(
			std::chrono::utc_clock::time_point utc_event_time,
			std::string_view subsystem,
			logging::Level level,
			std::string_view message,
			bool withNewline = false
		) const override;

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
	};

}	// namespace