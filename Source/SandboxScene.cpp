//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.cpp
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <Windows.h>
#include "Stream.h"
#include "SandboxScene.h"
#include "Scene.h"
#include "SceneSystem.h"

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

	SandboxScene::SandboxScene()
		: Scene("SandboxScene")
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

	void SandboxScene::Load()
	{
	}

	bool SandboxScene::Initialize()
	{
		return true;
	}

	void SandboxScene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);
		Stream vectorstream = Stream("Data/VectorTests.json");
		if (vectorstream.IsValid())
		{
			Vector2D v = Vector2D();
			v.Zero();
			LogVector("Zero", v);
			v.Set(1.5f, 1.0f);
			LogVector("Set", v);
			v.Negate();
			LogVector("Negate", v);
			v.Add(v);
			LogVector("Add", v);
			v.Sub(v);
			LogVector("Sub", v);
			vectorstream.ReadVector2D("v", v);
			LogVector("StreamReadVector2D", v);
			v.Normalize();
			LogVector("Normalize", v);
			float scale;
			vectorstream.Read("scale", scale);
			LogFloat("StreamReadFloat", scale);
			v.Scale(scale);
			LogVector("Vector2DScale", v);
			v.ScaleAdd(scale, v);
			LogVector("Vector2DScaleAdd", v);
			v.ScaleSub(scale, v);
			LogVector("Vector2DScaleSub", v);
			float length = v.Length();
			LogFloat("Vector2DLength", length);
			length = v.SquareLength();
			LogFloat("Vector2DSquareLength", length);
			Vector2D p1 = Vector2D();
			Vector2D p2 = Vector2D();
			vectorstream.ReadVector2D("p1", p1);
			LogVector("StreamReadVector2D", p1);
			vectorstream.ReadVector2D("p2", p2);
			LogVector("StreamReadVector2D", p2);
			float distance = p1.Distance(p2);
			LogFloat("Distance", distance);
			float sqdistance = p1.SquareDistance(p2);
			LogFloat("SquareDistance", sqdistance);
			float result = p1.DotProduct(p2);
			LogFloat("Vector2DDotProduct", result);
			Vector2D u = Vector2D(v);
			float angle;
			vectorstream.Read("degrees", angle);
			LogFloat("StreamReadFloat", angle);
			u.FromAngleDeg(angle);
			LogVector("Vector2DFromAngleDeg", u);
			vectorstream.Read("radians", angle);
			LogFloat("StreamReadFloat", angle);
			u.FromAngleRad(angle);
			LogVector("Vector2DFromAngleRad", u);
			float torad = u.ToAngleRad();
			LogFloat("Vector2DToAngleRad", torad);
		}
		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		SceneSystem::EndScene();
	}

	void SandboxScene::Render() const
	{
	}

	void SandboxScene::Shutdown()
	{
	}

	void SandboxScene::Unload()
	{
	}
	void SandboxScene::LogFloat(const char* text, float f)
	{
		LoggingSystem::Verbose("Vector Test: {} = {}", text, f);
	}
	void SandboxScene::LogVector(const char* text, const Vector2D& v)
	{
		LoggingSystem::Verbose("Vector Test: {} = [{}, {}]", text, v.x, v.y);
	}
#pragma endregion Private Functions

}	// namespace