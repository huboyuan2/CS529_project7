/// @file dragon.h
/// @brief Primary public interface for the Dragon utility library.
///
/// This header aggregates core functionality for the library,
/// including logging, error handling, and platform abstractions.
/// Designed for cross-platform correctness and teaching best practices
/// in modern C++23.
///
/// @author Eric Fleegal, DigiPen Faculty
/// @date 2017-2025
/// 
/// 
/// @license MIT License
/// 
/// Copyright (c) 2017-2025 Eric Fleegal, for DigiPen Institute of Technology
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
#pragma once

#include "dragon/platform_dependencies.h"

#include "dragon/assert.h"
#include "dragon/events.h"
#include "dragon/traits.h"
#include "dragon/logging.h"
#include "dragon/strings.h"
