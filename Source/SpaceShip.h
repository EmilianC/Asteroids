#pragma once
#include <Jewel3D/Application/Logging.h>
#include <Jewel3D/Entity/Entity.h>

class Bullet;
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
		m_velocity = Jwl::vec3::Zero;
		m_spaceShipNode->position = Jwl::vec3::Zero;
		m_spaceShipNode->rotation = Jwl::quat::Identity;
		m_speed = 0.0f;
		m_coolDown = 0.0f;
		m_resetTimer = 0.0f;
		m_spaceShipNode->Enable();
	}

	Jwl::Entity::Ptr		m_spaceShipNode = Jwl::Entity::MakeNew();
	std::vector<Bullet*>	m_bullets;
	Jwl::Entity::Ptr		m_victorySound = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr		m_deathSound = Jwl::Entity::MakeNew();
	Jwl::Entity::Ptr		m_deathSound2 = Jwl::Entity::MakeNew();

	int			m_level = 1;
	Asteroids*	m_parent = nullptr;

private:
	void CreateBullet();

	Jwl::vec3	m_velocity;
	int			m_score = 0;
	float		m_speed = 0.0f;
	float		m_coolDown = 0.0f;

	float		m_resetTimer = 0.0f;
};

class Bullet
{
public:
	void Update(float a_deltaT)
	{
		m_bulletNode->position += m_bulletNode->rotation.GetForward() * m_speed * a_deltaT;
		
		if (abs(m_bulletNode->position.x) > 22.5f)
		{
			m_bulletNode->position.x *= -0.99f;
		}

		if (abs(m_bulletNode->position.z) > 22.5f)
		{
			m_bulletNode->position.z *= -0.99f;
		}

		m_age += a_deltaT;
	}

	Jwl::Entity::Ptr m_bulletNode = Jwl::Entity::MakeNew();

	float m_age = 0.0f;

private:
	float m_speed = 20.0f;
	Jwl::vec3 m_velocity;
};
