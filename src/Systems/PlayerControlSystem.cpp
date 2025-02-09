#include "PlayerControlSystem.hpp"

#include "Player.hpp"
#include "Thrust.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"
#include "Logger.hpp"


extern Coordinator g_coordinator;


void PlayerControlSystem::Init()
{
	g_coordinator.AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerControlSystem::InputListener));
}

void PlayerControlSystem::Update(float dt)
{
	for (auto& entity : m_entities)
	{
		auto& transform = g_coordinator.GetComponent<Transform>(entity);

		if (m_buttons.test(static_cast<std::size_t>(InputButtons::W)))
		{
			transform.position.y -= (dt * m_player_speed);
		}

		else if (m_buttons.test(static_cast<std::size_t>(InputButtons::S)))
		{
			transform.position.y += (dt * m_player_speed);
		}

		if (m_buttons.test(static_cast<std::size_t>(InputButtons::A)))
		{
			transform.position.x -= (dt * m_player_speed);
		}

		else if (m_buttons.test(static_cast<std::size_t>(InputButtons::D)))
		{
			transform.position.x += (dt * m_player_speed);
		}

		LOG("Player (" + std::to_string(static_cast<int>(round(transform.position.x))) + ", " + std::to_string(static_cast<int>(round(transform.position.y))) + ")");
	}
}

void PlayerControlSystem::InputListener(Event& event)
{
	m_buttons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}
