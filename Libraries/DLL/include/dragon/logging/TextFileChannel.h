#pragma once

#include <dragon/logging/Channel.h>

#include <filesystem>
#include <fstream>

namespace dragon::logging
{
    /// @brief A logging channel that writes messages to a text file.
    /// 
    /// @note When Derived classes override onClosing, it should explicitly
    /// call close() in Derived's destructor to ensure timely receipt of the
    /// onClosing() event.
    class TextFileChannel : public BasicChannel
    {
    public:
        /// @brief Constructs a text file logging channel.
        ///
        /// @param channelName A short identifier for the channel (e.g., "debug", "network").
        TextFileChannel(std::string_view const channelName);

        /// @brief Destructor. Invokes close() if the file is still open.
        /// 
        /// @note Derived classes should call close() directly at destruction
        /// time to ensure the onClosing event occurs on destruction. The event
        /// will not be raised at TextFileChannel destruction because the derived
        /// class will have already been destructed.
        virtual ~TextFileChannel();

        /// @brief Opens the log file at the specified path.
        ///
        /// @param path The filesystem path to the log file.
        /// @return True if the file was successfully opened, false otherwise.
        bool open(std::filesystem::path const& path);

        /// @brief Closes the log file and triggers onClosing().
        void close();

        /// @brief Checks whether the log file is currently open.
        ///
        /// @return True if the file is open, false otherwise.
        bool isOpen() const;

        /// @brief Writes a formatted log message to the file.
        ///
        /// @param log_time   The timestamp of the log event.
        /// @param subsystem  The subsystem generating the message (e.g., "audio", "physics").
        /// @param level      The severity level of the message.
        /// @param message    The raw message content.
        void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;

    protected:
        /// @brief event that occurs just after successfully opening the file.
        /// Derived classes can override to write initial text to the file
        virtual void onOpened(std::ofstream& file);

        /// @brief event that occurs just before closing the file.
        /// Derived classes can override to write final text to the file.
        /// 
        /// @note Any Derived class that handles onClosing should
        /// explicitly call close() in its destructor to ensure the
        /// onClosing event occurs before destruction of the Derived class.
        virtual void onClosing(std::ofstream& file);

    private:
        mutable std::mutex _mutex;
        std::filesystem::path _path;
        std::ofstream _file;
    };

}
