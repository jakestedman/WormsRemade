#include "PhysicsSystem.hpp"

#include "Gravity.hpp"
#include "RigidBody.hpp"
#include "Thrust.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"


extern Coordinator g_coordinator;


void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float dt)
{
	for (auto const& entity : m_entities)
	{
		auto& rigidBody = g_coordinator.GetComponent<RigidBody>(entity);
		auto& transform = g_coordinator.GetComponent<Transform>(entity);

		// Forces
		auto const& gravity = g_coordinator.GetComponent<Gravity>(entity);

		// transform.position += rigidBody.velocity * dt;

		// rigidBody.velocity += gravity.force * dt;
	}
}
