//------------------------------------------------------------------------------
//
// File Name:	LoggingSystem.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Template class for a new system.
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

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <filesystem>
#include <format>
#include <memory>
#include <string_view>

#include <dragon/logging/Level.h>
#include <dragon/logging/Logger.h>
#include <dragon/logging/DebugChannel.h>
#include <dragon/logging/MultiplexChannel.h>
#include <dragon/logging/TextFileChannel.h>
#include <dragon/platform_dependencies.h>

#include "System.h"

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
	class LoggingSystem : public System
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		LoggingSystem(std::string_view applicationName, std::filesystem::path const& path);

		// All systems need a virtual destructor to have their destructor called 
		~LoggingSystem(void) override;

		// Public Static Functions:
	public:
		template <typename... Args>
		static ALWAYS_INLINE void Debug(std::format_string<Args...> const format, Args&&... args) noexcept {
			instance->logger.log(logging::Level::debug, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static ALWAYS_INLINE void Verbose(std::format_string<Args...> const format, Args&&... args) noexcept {
			instance->logger.log(logging::Level::verbose, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static ALWAYS_INLINE void Info(std::format_string<Args...> const format, Args&&... args) noexcept {
			instance->logger.log(logging::Level::information, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static ALWAYS_INLINE void Warning(std::format_string<Args...> const format, Args&&... args) noexcept {
			instance->logger.log(logging::Level::warning, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static ALWAYS_INLINE void Error(std::format_string<Args...> const format, Args&&... args) noexcept {
			instance->logger.log(logging::Level::error, format, std::forward<Args>(args)...);
		}

		// Public Functions:
	public:

		// Public Event Handlers
	public:
		// Windows message event handler.
		//virtual bool HandleMessage(const Message& message) = 0;

		// Private Functions:
	private:
		// @brief Initialize the system.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// Private Static Constants:
	private:

		// Private Static Variables:
	private:
		static LoggingSystem* instance;

		// Private Variables:
	private:
		std::string_view applicationName;

		dragon::logging::Logger debugLogger{};
		dragon::logging::Logger logger{};

		// the debug channel : typically declared first in your logging system to ensure it is destructed last
		std::shared_ptr<dragon::logging::DebugChannel> debugChannel;
		std::shared_ptr<dragon::logging::TextFileChannel> logFileChannel;
		std::shared_ptr<dragon::logging::MultiplexChannel> multiplexChannel;
	};

}	// namespace