//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.h
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 4
// Purpose:		System for managing scenes.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include <memory>

#include "Scene.h"
#include "System.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Entity;

	// Typedefs:

	// Class Definition:
	class SceneSystem : public System
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		SceneSystem(void);

		// All systems need a virtual destructor to have their destructor called 
		~SceneSystem(void) override;

		// Public Static Functions:
	public:
		// @brief Determines if the system is still running.
		// @brief [NOTE: The engine should shutdown when no active or pending scene(s) remain.]
		//
		// @return bool = true if the scene system is still running, otherwise false.
		static bool IsRunning() { return (instance->activeScene || instance->pendingScene); }

		// @brief Tell the scene system to restart the active scene.
		static void Restart() { instance->isRestarting = true; }
		static void ClearRestartFlag() { instance->isRestarting = false; }
		// @brief Tell the scene system to end the active scene.
		// @brief [NOTE: The engine should shutdown when no active or pending scene(s) remain.]
		// @brief [NOTE: Any active scene is automatically deleted due to the nature of std::unique_ptr.]
		static void EndScene() { instance->isEnding = true; }

		// @brief Tell the scene system to switch to a new, pending scene.
		// @brief [NOTE: This function is templatized to avoid creating a new instance of a scene
		//   if it is already the active scene.]
		template <typename T>
		static void SetPendingScene()
		{
			// Determine if the new pending scene is the same as the active scene.
			if ((instance->activeScene) && (typeid(*instance->activeScene) == typeid(T)))
			{
				// If the same, then restart the active scene.
				instance->Restart();
			}
			else
			{
				// If different, then create an instance for the new pending scene.
				// [NOTE: Any existing pending scene is automatically deleted due to the nature of std::unique_ptr.]
				instance->pendingScene = std::make_unique<T>();
			}
		}

		// @brief Add a new entity to the active scene.
		static void AddEntity(Entity* entity) { instance->activeScene->AddEntity(entity); }

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief Initialize the system.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the active system(s) each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// @brief Render the active system(s) each frame.
		void Render() const override;

		// @brief Shutdown the system before exiting the application.
		void Shutdown() {};

		// @brief Determines if the active scene is changing.
		//
		// @return bool = true if the scene is changing, otherwise false.
		bool IsSceneChanging() const { return (isEnding || isRestarting || (pendingScene.get() != nullptr)); }

		// @brief Determines if the active scene is restarting.
		//
		// @return bool = true if the active scene is restarting, otherwise false.
		bool IsSceneRestarting() const { return isRestarting; }

		// Avoid throwing a null-reference exception when there is no active scene.
		void CallLoad() const;
		void CallInitialize() const;
		void CallUpdate(float dt) const;
		void CallRender() const;
		void CallShutdown() const;
		void CallUnload() const;

		// Private Static Constants:
	private:

		// Private Static Variables:
	private:
		static SceneSystem* instance;

		// Private Variables:
	private:
		std::unique_ptr<Scene> activeScene{ nullptr };
		std::unique_ptr<Scene> pendingScene{ nullptr };

		bool isEnding{ false };
		bool isRestarting{ false };
	};

}	// namespace