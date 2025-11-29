//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template for a new .cpp file.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "Animation.h"
#include "Stream.h"
#include "Component.h"
#include "Entity.h"
#include "Sprite.h"

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

	Animation::Animation(void)
	{
	}
	Animation::Animation(const Animation* other)
	{
		this->frameIndex = other->frameIndex;
		this->frameCount = other->frameCount;
		this->frameDelay = other->frameDelay;
		this->frameDuration = other->frameDuration;
		this->isRunning = other->isRunning;
		this->isLooping = other->isLooping;
		this->isDone = other->isDone;
	}
	////--------------------------------------------------------------------------

	//Animation::~Animation(void)
	//{
	//}

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
	void Animation::Play(unsigned frameCount, float frameDuration, bool isLooping)
	{
		this->frameIndex = 0;
		this->frameCount = frameCount;
		this->frameDuration = frameDuration;
		this->frameDelay = frameDuration;
		this->isLooping = isLooping;
		this->isRunning = true;
		this->isDone = false;
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions
	void Animation::Read(Stream& stream)
	{
		if (stream.IsValid() && stream.Contains("Animation"))
		{
			stream.PushNode("Animation");
			stream.Read("FrameIndex", frameIndex);
			stream.Read("FrameCount", frameCount);
			stream.Read("FrameDelay", frameDelay);
			stream.Read("FrameDuration", frameDuration);
			stream.Read("IsRunning", isRunning);
			stream.Read("IsLooping", isLooping);
			stream.Read("IsDone", isDone);
			stream.PopNode();
		}
	}
	void Animation::Update(float dt)
	{
		//if valid pointer
		if (Parent()->Get<Sprite>())
		{
			isDone = false;
			if (isRunning)
			{
				frameDelay -= dt;
				if (frameDelay <= 0.0f)
				{
					AdvanceFrame();
				}
			}
		}
		
	}
	void Animation::AdvanceFrame()
	{
		Sprite* sprite = Parent()->Get<Sprite>();
		if (sprite)

		{
			frameIndex++;
			if (frameIndex >= frameCount)
			{
				if (isLooping)
				{
					frameIndex = 0;
					isDone = true;
				}
				else
				{
					frameCount = frameCount - 1;
					isRunning = false;
					isDone = true;
				}
			}
			if (isRunning)
			{
				sprite->SetFrame(frameIndex);
				sprite->Update(frameDuration);
				frameDelay = frameDuration;
			}
			else
			{
				frameDelay = 0.0f;
			}
			frameDelay = frameDuration;
		}
	}
#pragma endregion Private Functions

}	// namespace