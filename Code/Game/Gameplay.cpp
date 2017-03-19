#include "Gameplay.h"
#include "../../resource.h"

#include "DebugFunctions/DebugFunctions.h"
#include "GameObject/GameObject/GameObject.h"
#include "GameObject/Controllers/PlayerController.h"
#include "Physics/ObjectProperties/ObjectProperties.h"
#include "UserInput/UserInput.h"

namespace Game
{
	namespace Gameplay
	{
		Gameplay* Gameplay::m_gameplay = nullptr;

		Gameplay::Gameplay() : m_player(nullptr), m_background(nullptr), m_playerController(nullptr), m_backbuffer(nullptr), m_spritedc(nullptr)
		{
			
		}

		Gameplay::~Gameplay()
		{
			if (m_player != nullptr)
			{
				delete m_player;
			}
			if (m_background != nullptr)
			{
				delete m_background;
			}
			if (m_playerController != nullptr)
			{
				delete m_playerController;
			}
			if (m_backbuffer != nullptr)
			{
				delete m_backbuffer;
			}
		}

		Gameplay* Gameplay::GetGame()
		{
			if (m_gameplay == nullptr)
			{
				m_gameplay = new Gameplay;

				DEBUG_PRINT("Created Gameplay");
			}

			DEBUG_PRINT("Called Get Game");

			return m_gameplay;
		}

		void Gameplay::DestroyGame()
		{
			if (m_gameplay != nullptr)
			{
				delete m_gameplay;

				DEBUG_PRINT("Destroyed Gameplay");
			}
			else
			{
				DEBUG_PRINT("Gameplay does not exist fro destruction");
			}
		}


		void Gameplay::InitializeSprite(HINSTANCE i_appid)
		{
			assert(i_appid != nullptr);
			
			using namespace Engine;
			
			Math::Vector2 playerpos(500.0f, 400.0f);
			Math::Vector2 backgrpos(600.0f, 400.0f);

			Physics::ObjectProperties playerprop(Math::Vector2(0.0f, 0.0f), 80.0f, 0.8f);
			Physics::ObjectProperties enemyprop(Math::Vector2(0.0f, 0.0f), 60.0f, 0.6f);

			m_background = new GameObject::GameObject(i_appid, backgrpos, enemyprop, IDB_BACKGR, IDB_BACKGRMASK);
			m_player = new GameObject::GameObject(i_appid, playerpos, playerprop, IDB_JET, IDB_JETMASK);

			m_playerController = new GameObject::PlayerController(m_player);

			m_spritedc = CreateCompatibleDC(0);

			DEBUG_PRINT("Initialized Sprites");
		}

		void Gameplay::UpdateGameObjects(const float i_dt)
		{
			using namespace Engine;
			
			Math::Vector2 playerForce(0.0f, 0.0f);

			if (UserInput::IsKeyPressed('W'))
			{
				playerForce = playerForce + Math::Vector2(0.0f, -10.0f);
			}
			else if (UserInput::IsKeyPressed('A'))
			{
				playerForce = playerForce + Math::Vector2(-10.0f, 0.0f);
			}
			else if (UserInput::IsKeyPressed('D'))
			{
				playerForce = playerForce + Math::Vector2(10.0f, 0.0f);
			}
			else if (UserInput::IsKeyPressed('S'))
			{
				playerForce = playerForce + Math::Vector2(0.0f, 10.0f);
			}

			m_playerController->Update(i_dt, playerForce);
		}
	}
}