#pragma once
#include "Asteroids.h"

#include <gemcutter/Entity/Entity.h>
#include <gemcutter/Rendering/RenderPass.h>
#include <vector>

namespace gem
{
	class ConfigTable;
}

class Game
{
public:
	Game(gem::ConfigTable& config);

	bool Init();
	void Exit();

	void Update();
	void Draw();

private:
	std::vector<gem::Entity::Ptr> MainGroup;
	gem::RenderPass MainRenderPass;
	
	gem::Entity::Ptr MainCamera = gem::Entity::MakeNew();
	gem::Entity::Ptr RootNode = gem::Entity::MakeNew();

	gem::ConfigTable& Config;

	Asteroids asteroids;
};
