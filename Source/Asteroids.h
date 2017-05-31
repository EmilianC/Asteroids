#pragma once
#include "Debris.h"
#include "SpaceShip.h"

#include <Jewel3D/Entity/EntityGroup.h>
#include <Jewel3D/Sound/SoundListener.h>
#include <vector>

#define NUM_START_ASTEROIDS 3

class Game;

class Asteroids
{
public:
	void InitAsteroids(Jwl::EntityGroup* a_rg);
	void ResetAsteroids();
	void UpdateAsteroids(float a_deltaT);

	SpaceShip				m_spaceShip;
	Jwl::Entity::Ptr		m_background = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr		m_listener = Jwl::Entity::MakeNew();
	std::vector<Debris*>	m_debrisList;

	Jwl::EntityGroup*		m_renderGroup = nullptr;
	bool					m_mainMenu = true;
};
