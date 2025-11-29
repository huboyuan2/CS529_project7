//------------------------------------------------------------------------------
//
// File Name:	DemoScene.cpp
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 0
// Purpose:		Graphics demo scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <algorithm>
#include <Windows.h>

#include "DGL.h"

#include "DemoScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "SceneSystem.h"
#include "Scene.h"

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

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

// Declare Constants:

	// DGL_Vec2 Constants:
	static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f, 0.5f };
	static const DGL_Vec2 Vertex_Pos_Trc = { 0.5f, 0.5f };
	static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };
	static const DGL_Vec2 Vertex_Pos_Brc = { 0.5f, -0.5f };
	static const DGL_Vec2 Vertex_Pos_Zero = { 0.0f, 0.0f };
	static const DGL_Vec2 Vertex_Pos_Right = { 0.5f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Zero = { 0.0f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Tlc = { 0.0f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Trc = { 1.0f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Blc = { 0.0f, 1.0f };
	static const DGL_Vec2 Vertex_UV_Brc = { 1.0f, 1.0f };

	// DGL_Color constants:
	static const DGL_Color DGL_Color_Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

	// Constants used to display objects within the scene.
	static const DGL_Vec2 posColored = { -200.f, 200.f };
	static const DGL_Vec2 posTinted = { 200.f, 200.f };
	static const DGL_Vec2 posTexturedBall = { -200.f, -200.f };
	static const DGL_Vec2 posTexturedSquare = { 200.f, -200.f };

	static const DGL_Vec2 scaleColored = { 100.f, 100.f };
	static const DGL_Vec2 scaleTextured = { 100.f, 100.f };

	// Constants used to move objects within the scene:
	static const float cameraScrollSpeed = 2.0f;
	static const float spaceshipScrollSpeed = 4.0f;
	static const float uvScrollSpeed = 0.01f;
	static const float rotationSpeed = 0.5f;

	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Declare Variables:

	// Variables used for referencing loaded assets.
	static DGL_Mesh* meshColor = NULL;
	static DGL_Mesh* meshTexture = NULL;
	static DGL_Mesh* meshSpaceship = NULL;
	static DGL_Mesh* meshLine = NULL;

	static DGL_Texture* textureBall = NULL;
	static DGL_Texture* textureSquare = NULL;

	// Variables used for changing the scene.
	static DGL_Vec2 posCamera = { 0, 0 };
	static DGL_Vec2 posSpaceship = { 0.f, 0.f };

	static DGL_Vec2 uvOffset = { 0.f, 0.f };

	static float alpha = 1.0f;
	static float rotation = 0.0f;

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	DemoScene::DemoScene(void)
		: Scene("DemoScene")
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

	void DemoScene::Load()
	{
		//--------------------------------------------------------------------------
// INITIALIZATION:
//--------------------------------------------------------------------------

// Create Meshes:

// Create a simple, colored mesh.
		DGL_Graphics_StartMesh();
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
			&Vertex_Pos_Trc, &DGL_Color_Green, &Vertex_UV_Zero,
			&Vertex_Pos_Brc, &DGL_Color_Blue, &Vertex_UV_Zero);
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Cyan, &Vertex_UV_Zero,
			&Vertex_Pos_Tlc, &DGL_Color_Magenta, &Vertex_UV_Zero,
			&Vertex_Pos_Trc, &DGL_Color_Yellow, &Vertex_UV_Zero);
		meshColor = DGL_Graphics_EndMesh();

		// Create a simple, textured mesh.
		DGL_Graphics_StartMesh();
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &Vertex_UV_Blc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &Vertex_UV_Trc,
			&Vertex_Pos_Brc, &DGL_Color_Black, &Vertex_UV_Brc);
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &Vertex_UV_Blc,
			&Vertex_Pos_Tlc, &DGL_Color_Black, &Vertex_UV_Tlc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &Vertex_UV_Trc);
		meshTexture = DGL_Graphics_EndMesh();

		// Create a triangular, colored mesh.
		DGL_Graphics_StartMesh();
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Right, &DGL_Color_Yellow, &Vertex_UV_Zero,
			&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
			&Vertex_Pos_Tlc, &DGL_Color_Red, &Vertex_UV_Zero);
		meshSpaceship = DGL_Graphics_EndMesh();

		DGL_Graphics_StartMesh();
		DGL_Graphics_AddVertex(&Vertex_Pos_Trc, &DGL_Color_White, &Vertex_UV_Zero);
		DGL_Graphics_AddVertex(&Vertex_Pos_Tlc, &DGL_Color_White, &Vertex_UV_Zero);
		DGL_Graphics_AddVertex(&Vertex_Pos_Blc, &DGL_Color_White, &Vertex_UV_Zero);
		DGL_Graphics_AddVertex(&Vertex_Pos_Brc, &DGL_Color_White, &Vertex_UV_Zero);
		DGL_Graphics_AddVertex(&Vertex_Pos_Trc, &DGL_Color_White, &Vertex_UV_Zero);
		meshLine = DGL_Graphics_EndMesh();

		// Load/Create Textures:

		textureBall = DGL_Graphics_LoadTexture("Assets/ball.png");

		// Create a 2x2 texture from memory.
		const unsigned char colorsSquare[16] =
		{
			255,   0,   0, 255,
			  0, 255,   0, 255,
			  0,   0, 255, 255,
			255, 255, 255, 255
		};
		textureSquare = DGL_Graphics_LoadTextureFromMemory(colorsSquare, 2, 2);

		// Set the background color and blend mode.
		DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);


	}

	bool DemoScene::Initialize()
	{
		//	 Add code to set the following variables to their starting values.
		//   posCamera
		posCamera = { 0.0f, 0.0f };
		//   posSpaceship
		posSpaceship = { 0.0f, 0.0f };
		//   uvOffset
		uvOffset = { 0.0f, 0.0f };
		//   alpha
		alpha = 1.0f;
		//   rotation
		rotation = 0.0f;
			// Set the background color and blend mode.
		DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		return true;
	}

	void DemoScene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);

		// Update the scene.
		if (DGL_Window_HasFocus())
		{
			// Update the camera's position.
			if (DGL_Input_KeyDown('A'))
			{
				posCamera.x -= cameraScrollSpeed;
			}
			else if (DGL_Input_KeyDown('D'))
			{
				posCamera.x += cameraScrollSpeed;
			}
			if (DGL_Input_KeyDown('W'))
			{
				posCamera.y += cameraScrollSpeed;
			}
			else if (DGL_Input_KeyDown('S'))
			{
				posCamera.y -= cameraScrollSpeed;
			}
			
			// Update the triangular ("Spaceship") mesh's position.
			if (DGL_Input_KeyDown(VK_UP))
				posSpaceship.y += spaceshipScrollSpeed;
			else if (DGL_Input_KeyDown(VK_DOWN))
				posSpaceship.y -= spaceshipScrollSpeed;
			if (DGL_Input_KeyDown(VK_LEFT))
				posSpaceship.x -= spaceshipScrollSpeed;
			else if (DGL_Input_KeyDown(VK_RIGHT))
				posSpaceship.x += spaceshipScrollSpeed;

			// Update the triangular ("Spaceship") mesh's Alpha value.
			// HINT: If converting to C++, use std::max and std::min.
			if (DGL_Input_KeyDown('Z'))
			{
				alpha = std::max(0.0f, alpha - 0.02f);
			}
			else if (DGL_Input_KeyDown('X'))
			{
				alpha = std::min(1.0f, alpha + 0.02f);
			}

			// Update the Ball texture's UV offsets.
			if (DGL_Input_KeyDown('J'))
				uvOffset.x -= uvScrollSpeed;
			else if (DGL_Input_KeyDown('L'))
				uvOffset.x += uvScrollSpeed;
			if (DGL_Input_KeyDown('I'))
				uvOffset.y -= uvScrollSpeed;
			else if (DGL_Input_KeyDown('K'))
				uvOffset.y += uvScrollSpeed;

			// Update the rotation value.
			rotation += rotationSpeed * dt;
			//if (DGL_Input_KeyTriggered('1'))
			//{
			//	SceneSystem::SetPendingScene<Level1Scene>();
			//}
			//else if (DGL_Input_KeyTriggered('2'))
			//{
			//	SceneSystem::SetPendingScene<Level2Scene>();
			//}
			//else if (DGL_Input_KeyTriggered('9'))
			//{
			//	SceneSystem::SetPendingScene<SandboxScene>();
			//}
			//// Add code to restart the level when the ??key is triggered (when the key changes state from not pressed to pressed).
			//if (DGL_Input_KeyTriggered('0'))
			//{
			//	Restart();
			//}
		}
	}

	void DemoScene::Render() const
	{
		// Update the camera's position every frame.
		DGL_Camera_SetPosition(&posCamera);

		// Display a simple, colored mesh.
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
		DGL_Graphics_SetCB_Alpha(1.0f);
		DGL_Graphics_SetCB_TintColor(&DGL_Color_Zero);
		DGL_Graphics_SetCB_TransformData(&posColored, &scaleColored, 0.f);
		DGL_Graphics_DrawMesh(meshColor, DGL_DM_TRIANGLELIST);

		// Draw a simple, colored mesh with a red (50%) tint.
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
		DGL_Graphics_SetCB_Alpha(1.0f);
		const DGL_Color DGL_Tint_HalfRed = { 1.0f, 0.0f, 0.0f, 0.5f };
		DGL_Graphics_SetCB_TintColor(&DGL_Tint_HalfRed);
		DGL_Graphics_SetCB_TransformData(&posTinted, &scaleColored, rotation);
		DGL_Graphics_DrawMesh(meshColor, DGL_DM_TRIANGLELIST);

		// Draw a simple, textured mesh using the Ball texture.
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		DGL_Graphics_SetTexture(textureBall);
		DGL_Graphics_SetCB_Alpha(1.0f);
		DGL_Graphics_SetCB_TextureOffset(&uvOffset);
		DGL_Graphics_SetCB_TintColor(&DGL_Color_Zero);
		DGL_Graphics_SetCB_TransformData(&posTexturedBall, &scaleTextured, 0.f);
		DGL_Graphics_DrawMesh(meshTexture, DGL_DM_TRIANGLELIST);

		// Draw a simple, textured mesh using the 2x2 texture.
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		DGL_Graphics_SetTextureSamplerData(DGL_TSM_POINT, DGL_AM_WRAP);
		DGL_Graphics_SetTexture(textureSquare);
		DGL_Graphics_SetCB_Alpha(1.0f);
		DGL_Graphics_SetCB_TextureOffset(&Vertex_UV_Zero);
		DGL_Graphics_SetCB_TintColor(&DGL_Color_Zero);
		DGL_Graphics_SetCB_TransformData(&posTexturedSquare, &scaleTextured, 0.f);
		DGL_Graphics_DrawMesh(meshTexture, DGL_DM_TRIANGLELIST);
		DGL_Graphics_SetTextureSamplerData(DGL_TSM_LINEAR, DGL_AM_WRAP);

		// Draw a triangular, colored mesh.
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
		DGL_Graphics_SetCB_Alpha(alpha);
		DGL_Graphics_SetCB_TintColor(&DGL_Color_Zero);
		DGL_Graphics_SetCB_TransformData(&posSpaceship, &scaleColored, 0.f);
		DGL_Graphics_DrawMesh(meshSpaceship, DGL_DM_TRIANGLELIST);

		// Draw a 4-segment line strip.
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
		DGL_Graphics_SetCB_Alpha(1.0f);
		DGL_Graphics_SetCB_TintColor(&DGL_Color_Zero);
		const DGL_Vec2 scaleLineStrip = { 800.f, 600.f };
		DGL_Graphics_SetCB_TransformData(&Vertex_Pos_Zero, &scaleLineStrip, 0.f);
		DGL_Graphics_DrawMesh(meshLine, DGL_DM_LINESTRIP);
	}

	void DemoScene::Shutdown()
	{
	}

	void DemoScene::Unload()
	{

		// Free all meshes
		DGL_Graphics_FreeMesh(&meshColor);
		DGL_Graphics_FreeMesh(&meshTexture);
		DGL_Graphics_FreeMesh(&meshSpaceship);
		DGL_Graphics_FreeMesh(&meshLine);

		// Free all textures
		DGL_Graphics_FreeTexture(&textureBall);
		DGL_Graphics_FreeTexture(&textureSquare);
	}

#pragma endregion Private Functions

}	// namespace