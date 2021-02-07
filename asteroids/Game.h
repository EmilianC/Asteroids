#pragma once
#include "Asteroids.h"

#include <Jewel3D/Entity/Entity.h>
#include <Jewel3D/Rendering/RenderPass.h>
#include <vector>

namespace Jwl
{
	class ConfigTable;
}

class Game
{
public:
	Game(Jwl::ConfigTable& config);

	bool Init();
	void Exit();

	void Update();
	void Draw();

private:
	std::vector<Jwl::Entity::Ptr> MainGroup;
	Jwl::RenderPass MainRenderPass;
	
	Jwl::Entity::Ptr MainCamera = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr RootNode = Jwl::Entity::MakeNew();

	Jwl::ConfigTable& Config;

	Asteroids asteroids;
};
