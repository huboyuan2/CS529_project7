//------------------------------------------------------------------------------
//
// File Name:	LoggingSystem.cpp
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		System for logging/tracing messages; useful for debugging.
// Notes:
//   This system is used as a wrapper around the Dragon Logging library,
// created by Professor Eric Fleegal. This library will also be used in GAM 541.
//   Encapsulation (or "Hiding Information") is a useful technique for hiding
// implementation details. This makes it possible to replace one logging library
// with another without requiring major changes to your engine.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <cassert>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string_view>

#include <dragon/logging/Level.h>
#include <dragon/logging/DebugChannel.h>
#include <dragon/logging/MultiplexChannel.h>
#include <dragon/platform_dependencies.h>

constexpr bool CS529_INCLUDE_UTC = false;
#if CS529_INCLUDE_UTC
// Output messages with timestamp information.
#include <dragon/logging/TextFileChannel.h>
#else
// Output messages without timestamp information.
// This makes comparing the actual output with the expected output much easier.
#include "SimpleTextFileChannel.h"
#endif

#include "LoggingSystem.h"
#include "System.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

namespace logging = dragon::logging;

namespace
{
	// Default message levels:
	//   Debug builds: verbose
	//   Release builds: information
	constexpr logging::Level DefaultFilterLevel = dragon::flags::debug ? logging::Level::verbose : logging::Level::information;
}

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

	//------------------------------------------------------------------------------
	// Private Static Variables:
	//------------------------------------------------------------------------------

	LoggingSystem* LoggingSystem::instance = nullptr;

	//------------------------------------------------------------------------------
	// Private Constants:
	//------------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	LoggingSystem::LoggingSystem(std::string_view applicationName, std::filesystem::path const& path)
		: System("LoggingSystem")
		, logger()
		, debugChannel()
		, logFileChannel()
	{
		// Raise an assert if this system has already been created.
		assert(instance == nullptr);

		// Store this system's instance for use by static functions.
		instance = this;

		// Set up the debug logger first because it is immediately needed.
		debugChannel = std::make_shared<logging::DebugChannel>(applicationName);
		debugLogger.channel(debugChannel);
		debugLogger.trace("LoggingSystem initialized the debug channel.");

		// Open the primary file logging channel and set the default filter level.
#if CS529_INCLUDE_UTC
		logFileChannel = std::make_shared<logging::TextFileChannel>(applicationName);
#else
		logFileChannel = std::make_shared<SimpleTextFileChannel>(applicationName);
#endif
		if (!logFileChannel->open(path))
		{
			// if the log file channel cannot be opened, we should log an error
			debugLogger.error("Failed to open log file channel at path: {}", path.string());
			throw std::runtime_error("Failed to open log file channel at specified path.");
		}
		logFileChannel->filterLevel(DefaultFilterLevel);

		if constexpr (dragon::flags::debug)
		{
			// in DEBUG mode, we want echo the log file channel to the debug console
			// (everything written to logFileChannel_ will also be written to the debugChannel_).
			// We do this with a multiplex channel whose primary channel is logFileChannel_.
			multiplexChannel = std::make_shared<logging::MultiplexChannel>(logFileChannel);
			multiplexChannel->addChannel(debugChannel); // add the debug channel as a secondary channel   

			logger.channel(multiplexChannel); // attach the multiplex channel to the main logger
		}
		else
		{
			// in release mode, we just use the logFileChannel_ as the main channel
			// NOTE: you may want to reconfigure this so that you can attach a debugger to the application in release mode
			logger.channel(logFileChannel);
		}
	}

	//--------------------------------------------------------------------------

	LoggingSystem::~LoggingSystem(void)
	{
		logger.information("LoggingSystem shutdown.");
		logger.channel(nullptr); // Detach the main logging channel.

		// Do this last.
		debugLogger.information("LoggingSystem shutdown.");
		debugLogger.channel(nullptr); // Detach the debug channel.
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

	bool LoggingSystem::Initialize()
	{
		// Return true if the initialization completed successfully.
		return true;
	}

#pragma endregion Private Functions

}	// namespace