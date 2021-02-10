#include "Game.h"
#include "Persistent.h"
#include "Bullet.h"
#include "Debris.h"

#include <gemcutter/Application/Application.h>
#include <gemcutter/Rendering/Rendering.h>
#include <gemcutter/Resource/Shader.h>
#include <gemcutter/Sound/SoundSystem.h>
#include <gemcutter/Rendering/Camera.h>
#include <gemcutter/Input/Input.h>

using namespace gem;

Game::Game(ConfigTable& _config)
	: Config(_config)
	, asteroids(MainGroup)
{
}

bool Game::Init()
{
	SoundSystem.SetGlobalVolume(0.2f);
	SoundSystem.SetAttenuationMode(AttenuationMode::None);

	// Setup Camera.
	MainCamera->Add<Camera>(20.0f, -20.0f, -20.0f, 20.0f, 0.0f, 20.0f);
	MainCamera->position = vec3::Up * 10.0f;
	MainCamera->RotateX(270.0f);

	// Setup up renderer.
	MainRenderPass.SetCamera(MainCamera);

	MainGroup.push_back(asteroids.spaceShip.m_spaceShipNode);

	// Setup GL States.
	SetClearColor(vec4::Zero);
	SetCullFunc(CullFunc::Clockwise);
	SetDepthFunc(DepthFunc::Normal);

	return true;
}

void Game::Exit()
{
}

void Game::Update()
{
	if (Input.IsDown(Key::Escape))
	{
		Application.Exit();
		return;
	}

	for (auto& bullet : All<Bullet>())
	{
		bullet.Update();
	}

	asteroids.Update(Application.GetDeltaTime());

	Application.UpdateEngine();

	// Delete old entities.
	Persistent::Collect();
}

void Game::Draw()
{
	ClearBackBuffer();

	MainRenderPass.Render(MainGroup);

	for (auto& bullet : With<Bullet>())
	{
		MainRenderPass.Render(bullet);
	}

	for (auto& debris : With<Debris>())
	{
		MainRenderPass.Render(debris);
	}
}
