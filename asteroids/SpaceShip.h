#pragma once
#include <gemcutter/Application/Logging.h>
#include <gemcutter/Entity/Entity.h>

#include <string>

class Asteroids;

class SpaceShip
{
public:
	void AddScore(int a_score)
	{
		m_score += a_score * m_level;
		gem::Log("Score is " + std::to_string(m_score));
	}

	void Update(float a_deltaT);
	
	void Destroy();

	void Reset()
	{
		alive = true;
		m_velocity = gem::vec3::Zero;
		m_spaceShipNode->position = gem::vec3::Zero;
		m_spaceShipNode->rotation = gem::quat::Identity;
		m_speed = 0.0f;
		m_coolDown = 0.0f;
		m_spaceShipNode->Enable();
	}

	gem::Entity::Ptr m_spaceShipNode = gem::Entity::MakeNew();
	gem::Entity::Ptr m_victorySound = gem::Entity::MakeNew();
	gem::Entity::Ptr m_deathSound = gem::Entity::MakeNew();
	gem::Entity::Ptr m_deathSound2 = gem::Entity::MakeNew();

	int m_level = 1;
	Asteroids* m_parent = nullptr;
	bool alive = true;

private:
	void CreateBullet();

	gem::vec3 m_velocity;
	int m_score = 0;
	float m_speed = 0.0f;
	float m_coolDown = 0.0f;

	float elapsed = 0.0f;
};
