#include <chrono>
#include <random>
#include <iostream>
#include <memory>

#include "Camera.hpp"
#include "Gravity.hpp"
#include "Player.hpp"
#include "Renderable.hpp"
#include "RigidBody.hpp"
#include "Thrust.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"
#include "WindowManager.hpp"

Coordinator g_coordinator;
static bool quit = false;


void QuitListener(Event& event)
{
	quit = true;
    std::cout << "App::QuitListener - Quitting.." << std::endl;
}

int main()
{
	g_coordinator.Init();

    std::unique_ptr<WindowManager> window_manager = std::make_unique<WindowManager>();
	window_manager->Init("Worms Remade!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 620, false); 

	g_coordinator.AddEventListener(FUNCTION_LISTENER(Events::Window::QUIT, QuitListener));
	g_coordinator.RegisterComponent<Transform>();
	g_coordinator.RegisterComponent<Renderable>();

    /*
	g_coordinator.RegisterComponent<Camera>();
	g_coordinator.RegisterComponent<Gravity>();
	g_coordinator.RegisterComponent<Player>();
	g_coordinator.RegisterComponent<RigidBody>();
	g_coordinator.RegisterComponent<Thrust>();
    */

   /*
	auto physics_system = g_coordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Gravity>());
		signature.set(g_coordinator.GetComponentType<RigidBody>());
		signature.set(g_coordinator.GetComponentType<Transform>());
		g_coordinator.SetSystemSignature<PhysicsSystem>(signature);
	}
	physics_system->Init();

    
	auto camera_control_system = g_coordinator.RegisterSystem<CameraControlSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Camera>());
		signature.set(g_coordinator.GetComponentType<Transform>());
		g_coordinator.SetSystemSignature<CameraControlSystem>(signature);
	}
	camera_control_system->Init();

	auto player_control_system = g_coordinator.RegisterSystem<PlayerControlSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Player>());
		signature.set(g_coordinator.GetComponentType<Transform>());
		g_coordinator.SetSystemSignature<PlayerControlSystem>(signature);
	}
	player_control_system->Init();
    */

	auto render_system = g_coordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Renderable>());
		signature.set(g_coordinator.GetComponentType<Transform>());
		g_coordinator.SetSystemSignature<RenderSystem>(signature);
	}
	render_system->Init(window_manager->GetWindow());

	std::vector<Entity> entities(MAX_ENTITIES - 1);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> rand_position(-100.0f, 100.0f);
	std::uniform_real_distribution<float> rand_rotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> rand_scale(3.0f, 5.0f);
	std::uniform_real_distribution<float> rand_color(0.0f, 1.0f);
	std::uniform_real_distribution<float> rand_gravity(-10.0f, -1.0f);

	float scale = rand_scale(generator);

    /*
	for (auto& entity : entities)
	{
		entity = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(entity, Player{});

		g_coordinator.AddComponent<Gravity>(
			entity,
			{Vec3(0.0f, rand_gravity(generator), 0.0f)});

		g_coordinator.AddComponent(
			entity,
			RigidBody{
				.velocity = Vec3(0.0f, 0.0f, 0.0f),
				.acceleration = Vec3(0.0f, 0.0f, 0.0f)
			});

		g_coordinator.AddComponent(
			entity,
			Transform{
				.position = Vec3(rand_position(generator), rand_position(generator), rand_position(generator)),
				.rotation = Vec3(rand_rotation(generator), rand_rotation(generator), rand_rotation(generator)),
				.scale = Vec3(scale, scale, scale)
			});

		g_coordinator.AddComponent(
			entity,
			Renderable{
				.color = Vec3(rand_color(generator), rand_color(generator), rand_color(generator))
			});
	}
    */

	float dt = 0.0f;

	while (!quit)
	{
		auto start_time = std::chrono::high_resolution_clock::now();

		window_manager->HandleEvents(); // Check if any keys have been pressed

        /*
		player_control_system->Update(dt); // Move the player based on what keys have been pressed

		camera_control_system->Update(dt); // Move the camera based on what keys have been pressed
        */

		//physics_system->Update(dt); // Add movement to the player from the physics of the world

		render_system->Update(dt); // Update what the user sees

		//window_manager.Update(); // Update window if needed

		auto stop_time = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stop_time - start_time).count();
	}

    std::cout << "App::main - Quit!" << std::endl;

	return 0;
}