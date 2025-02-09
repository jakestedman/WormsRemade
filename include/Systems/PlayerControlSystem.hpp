#pragma once

#include "System.hpp"


class Event;


class PlayerControlSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:
	std::bitset<8> m_buttons;
	float m_player_speed = 40.0f;
	void InputListener(Event& event);
};
