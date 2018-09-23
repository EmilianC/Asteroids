#pragma once
#include "SpaceShip.h"

#include <vector>

class Asteroids
{
public:
	Asteroids(std::vector<Jwl::Entity::Ptr>& a_rg);

	void Reset();
	void Update(float a_deltaT);

	SpaceShip spaceShip;
	Jwl::Entity::Ptr background = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr listener = Jwl::Entity::MakeNew();

	std::vector<Jwl::Entity::Ptr>& renderGroup;
	bool mainMenu = true;

private:
	void PlaceAsteroids();
};
