#include "Asteroids.h"
#include "Bullet.h"
#include "Debris.h"
#include "SpaceShip.h"

#include <Jewel3D/Input/Input.h>
#include <Jewel3D/Sound/SoundSource.h>
#include <Jewel3D/Rendering/Mesh.h>
#include <Jewel3D/Rendering/Material.h>

using namespace Jwl;

void SpaceShip::Update(float a_deltaT)
{
	if (!alive)
	{
		elapsed += a_deltaT;

		if (elapsed > 1.0f)
		{
			Log("Dead!");

			elapsed = 0.0f;
			m_score = 0;
			m_level = 1;

			m_parent->Reset();
			m_parent->mainMenu = true;
			m_parent->background->Get<Material>().textures[0] = Load<Texture>("Textures/title_background");
			m_spaceShipNode->Get<Material>().buffers[0]->SetUniform("Animation", 0.0f);

			m_parent->background->Get<SoundSource>().Play();
		}
		else
		{
			m_spaceShipNode->Get<Material>().buffers[0]->SetUniform("Animation", elapsed);
		}

		return;
	}

	if (Input.IsDown(Key::Up) && m_speed < 10.5f)
	{
		if (m_parent->mainMenu)
		{
			m_parent->mainMenu = false;
			m_parent->background->Get<Material>().textures[0] = Load<Texture>("Textures/asteroids_background");

			m_parent->background->Get<SoundSource>().Stop();
		}

		m_velocity += m_spaceShipNode->rotation.GetForward() * a_deltaT;
		m_speed += 3.0f * a_deltaT;
	}

	if (Input.IsDown(Key::Down) && m_speed > -10.5f)
	{
		if (m_parent->mainMenu)
		{
	 		m_parent->mainMenu = false;
			m_parent->background->Get<Material>().textures[0] = Load<Texture>("Textures/asteroids_background");
			m_parent->background->Get<SoundSource>().Stop();
		}

		m_velocity += m_spaceShipNode->rotation.GetForward() * a_deltaT;
		m_speed -= 3.0f * a_deltaT;
	}

	if (Input.IsDown(Key::Left))
	{
		m_spaceShipNode->RotateY(200.0f * a_deltaT);
	}

	if (Input.IsDown(Key::Right))
	{
		m_spaceShipNode->RotateY(-200.0f * a_deltaT);
	}

	if (Input.IsDown(Key::Space) && m_coolDown < 0.0f)
	{
		if (m_parent->mainMenu)
		{
			m_parent->mainMenu = false;
			m_parent->background->Get<Material>().textures[0] = Load<Texture>("Textures/asteroids_background");
			m_parent->background->Get<SoundSource>().Stop();
		}

		SoundSource &bullet = m_spaceShipNode->Get<SoundSource>();
		bullet.Play();
		m_coolDown = 0.7f;

		CreateBullet();
	}

	float length = Length(m_velocity);
	if (length > 1.0f) 
	{
		m_velocity /= length;
	}

	if (m_speed > 10.0f)
	{
		m_speed = 10.0f;
	}
	else if (m_speed < -10.0f)
	{
		m_speed = -10.0f;
	}

	m_coolDown -= a_deltaT;

	m_spaceShipNode->position += m_velocity * m_speed * a_deltaT;

	if (abs(m_spaceShipNode->position.x) > 22.5f)
	{
		m_spaceShipNode->position.x *= -0.99f;
	}

	if (abs(m_spaceShipNode->position.z) > 22.5f)
	{
		m_spaceShipNode->position.z *= -0.99f;
	}

	if (GetComponentIndex<Debris>().size() == 0 && alive)
	{
		m_level = m_level + 1;
		m_parent->Reset();
		m_parent->mainMenu = true;
		m_parent->background->Get<Material>().textures[0] = Load<Texture>("Textures/finished_background");

		Log("\nNext Level!\n");

		m_victorySound->Get<SoundSource>().Play();
	}
}

void SpaceShip::CreateBullet()
{
	auto bullet = Entity::MakeNew();
	bullet->Add<Bullet>();

	bullet->rotation = m_spaceShipNode->rotation;
	bullet->position = m_spaceShipNode->position + m_spaceShipNode->rotation.GetForward() * 1.5f;
}

void SpaceShip::Destroy()
{
	m_deathSound->Get<SoundSource>().Play();
	m_deathSound2->Get<SoundSource>().Play();

	alive = false;

	m_parent->mainMenu = true;
}
