#pragma once
#include "SpaceShip.h"

#include <Jewel3D/Entity/EntityGroup.h>

class Asteroids
{
public:
	void Init(Jwl::EntityGroup* a_rg);
	void Reset();
	void Update(float a_deltaT);

	SpaceShip spaceShip;
	Jwl::Entity::Ptr background = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr listener = Jwl::Entity::MakeNew();

	Jwl::EntityGroup* renderGroup = nullptr;
	bool mainMenu = true;

private:
	void PlaceAsteroids();
};
