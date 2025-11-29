//------------------------------------------------------------------------------
//
// File Name:	Animation.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 3
// Purpose:		This component class is responsible for updating a Sprite's
//   frame index based upon animation timing data.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Component.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Stream;

	// Typedefs:

	// Class Definition:
	class Animation : public Component
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Animation(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		Animation(const Animation* other);

		~Animation(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Initiate a new animation sequence.
		// @brief [NOTE: Every private variable must be initialized correctly.]
		//
		// @param frameCount = Number of frames to display in the sequence.
		// @param frameDuration = Amount of time to display each frame.
		// @param isLooping = Should the animation loop at the end of a sequence.
		void Play(unsigned frameCount, float frameDuration, bool isLooping);

		// @brief Get the state of the isDone flag.
		// @brief [NOTE: This is used to detect when the end of an animation sequence has been reached.]
		//
		// @return bool = true if the end of the sequence has been reached, otherwise false.
		bool IsDone() const { return isDone; }

		// @brief Get the state of the isRunning flag.
		// @brief [NOTE: This is used to determine if an animation is still running.]
		// @brief [NOTE: This function has been added primarily for testing purposes.]
		//
		// @return bool = true if the animation is still running, otherwise false.
		bool IsRunning() const { return isRunning; }

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		Animation* Clone() const override { return new Animation(this); }

		// @brief Update the component each frame.
		// @brief [NOTE: Refer to the flow diagram in the "Animation II" slide deck
		//   for implementation details.]
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// Read the properties of a Animation component from a stream.
		// @brief Specific Steps:
		// @brief   Check for valid stream (optional).
		// @brief   Traverse down the tree to the "Animation" object (PushNode).
		// @brief   Read all private variables from the stream.
		// @brief     [NOTE: Refer to Monkey.json for the associated keys.]
		// @brief   Return to the original location in the tree (PopObject).
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// @brief Advance the animation to the next frame, handling looping, if necessary.
		// @brief [NOTE: Refer to the flow diagram in the "Animation II" slide deck
		//   for implementation details.]
		void AdvanceFrame();

		// Private Constants:
	private:

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// @brief The current frame being displayed.
		unsigned int frameIndex{ 0 };

		// @brief The maximum number of frames in the sequence.
		unsigned int frameCount{ 1 };

		// @brief The time remaining for the current frame.
		float frameDelay{ 0.0f };

		// @brief The amount of time to display each successive frame.
		float frameDuration{ 0.0f };

		// @brief True if the animation is running; false if the animation has stopped.
		bool isRunning{ false };

		// @brief True if the animation loops back to the beginning.
		bool isLooping{ false };

		// @brief True if the end of the animation sequence has been reached, false otherwise.
		// @brief (Hint: This applies to both looping and non-looping animations.)
		// @brief (Hint: This should be true for only one game loop.)
		bool isDone{ false };
	};

}	// namespace