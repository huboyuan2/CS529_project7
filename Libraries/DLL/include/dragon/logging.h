/// @details The dragon/logging was developed as an example logging system for student use.  
/// The design borrows elements from several existing logging systems, including the
/// Microsoft's Event Tracing for Windows and Apple's Unified Log Tracing Tools.
/// @see https://learn.microsoft.com/en-us/windows/win32/wes/defining-severity-levels
/// @see https://developer.apple.com/documentation/os/logger
#pragma once

#include "logging/AsynchronousChannel.h"
#include "logging/Channel.h"
#include "logging/DebugChannel.h"
#include "logging/Level.h"
#include "logging/Logger.h"
#include "logging/MultiplexChannel.h"
#include "logging/StdErrChannel.h"
#include "logging/SyslogChannel.h"
#include "logging/TextFileChannel.h"
