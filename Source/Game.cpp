#include "Game.h"

#include <Jewel3D/Application/Application.h>
#include <Jewel3D/Application/Logging.h>
#include <Jewel3D/Rendering/Rendering.h>
#include <Jewel3D/Resource/Shader.h>
#include <Jewel3D/Sound/SoundSystem.h>
#include <Jewel3D/Rendering/Camera.h>

using namespace Jwl;

Game::Game(ConfigTable& _config)
	: Config(_config)
{
}

bool Game::Init()
{
	SoundSystem.SetGlobalVolume(0.2f);
	SoundSystem.SetAttenuationMode(AttenuationMode::None);

	//Setup Camera
	MainCamera->Add<Camera>(20.0f, -20.0f, -20.0f, 20.0f, 0.0f, 20.0f);
	MainCamera->position = vec3::Up * 10.0f;
	MainCamera->RotateX(270.0f);

	//Setup up renderer
	MainRenderPass.SetCamera(MainCamera);

	game.InitAsteroids(&MainGroup);

	MainGroup.Add(game.m_spaceShip.m_spaceShipNode);

	//Setup GL States
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
	game.UpdateAsteroids(Application.GetDeltaTime());

	Application.UpdateEngine();
}

void Game::Draw()
{
	ClearBackBuffer();

	MainRenderPass.Render(MainGroup);
}
