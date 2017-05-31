#pragma once
#include <Jewel3D/Entity/Entity.h>

class SpaceShip;

class Debris
{
public:
	virtual void OnDestroy() = 0;

	SpaceShip* GetShip() { return m_ship; }
	void SetShip(SpaceShip* a_ship) { m_ship = a_ship; }
	
	void MoveRandom();
	void Update(float a_deltaT);

	Jwl::Entity::Ptr	m_debrisNode = Jwl::Entity::MakeNew();
	float				m_speed = 1.0f;
	float				m_size = 2.0f;

private:
	Jwl::vec3	m_randomSpin[2];
	Jwl::vec3	m_velocity;
	SpaceShip*	m_ship = nullptr;
};

class SmallDebris : public Debris
{
public:
	void OnDestroy();
};

class MediumDebris : public Debris
{
public:
	void OnDestroy();
};

class BigDebris : public Debris
{
public:
	void OnDestroy();
};
