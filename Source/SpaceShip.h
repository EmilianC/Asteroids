#pragma once
#include <Jewel3D/Application/Logging.h>
#include <Jewel3D/Entity/Entity.h>

#include <string>

class Asteroids;

class SpaceShip
{
public:
	void AddScore(int a_score)
	{
		m_score += a_score * m_level;
		Jwl::Log("Score is " + std::to_string(m_score));
	}

	void Update(float a_deltaT);
	
	void Destroy();

	void Reset()
	{
		alive = true;
		m_velocity = Jwl::vec3::Zero;
		m_spaceShipNode->position = Jwl::vec3::Zero;
		m_spaceShipNode->rotation = Jwl::quat::Identity;
		m_speed = 0.0f;
		m_coolDown = 0.0f;
		m_spaceShipNode->Enable();
	}

	Jwl::Entity::Ptr m_spaceShipNode = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr m_victorySound = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr m_deathSound = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr m_deathSound2 = Jwl::Entity::MakeNew();

	int m_level = 1;
	Asteroids* m_parent = nullptr;
	bool alive = true;

private:
	void CreateBullet();

	Jwl::vec3 m_velocity;
	int m_score = 0;
	float m_speed = 0.0f;
	float m_coolDown = 0.0f;

	float elapsed = 0.0f;
};
