#pragma once
#include "SpaceShip.h"

#include <vector>

class Asteroids
{
public:
	Asteroids(std::vector<gem::Entity::Ptr>& a_rg);

	void Reset();
	void Update(float a_deltaT);

	SpaceShip spaceShip;
	gem::Entity::Ptr background = gem::Entity::MakeNew();
	gem::Entity::Ptr listener = gem::Entity::MakeNew();

	std::vector<gem::Entity::Ptr>& renderGroup;
	bool mainMenu = true;

private:
	void PlaceAsteroids();
};
