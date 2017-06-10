#include "SpaceShip.h"
#include "Asteroids.h"

#include <Jewel3D/Application/Application.h>
#include <Jewel3D/Input/Input.h>
#include <Jewel3D/Sound/SoundSource.h>
#include <Jewel3D/Rendering/Mesh.h>
#include <Jewel3D/Rendering/Material.h>

using namespace Jwl;

void SpaceShip::Update(float a_deltaT)
{
	if (Input.IsDown(Key::Escape))
	{
		Application.Exit();
		return;
	}

	for (auto itr = m_bullets.begin(), itrEnd = m_bullets.end(); itr != itrEnd; ++itr)
	{
		(*itr)->Update(a_deltaT);

		if ((*itr)->m_age > 2.0f)
		{
			m_parent->m_renderGroup->Remove(*(*itr)->m_bulletNode);
			m_bullets.erase(itr);
			break;
		}
	}

	if (Input.IsDown(Key::Up) && m_speed < 10.5f)
	{
		if (m_parent->m_mainMenu)
		{
			m_parent->m_mainMenu = false;
			m_parent->m_background->Get<Material>().textures[0] = Load<Texture>("Textures/asteroids_background");

			m_parent->m_background->Get<SoundSource>().Stop();
		}

		m_velocity += m_spaceShipNode->rotation.GetForward() * a_deltaT;
		m_speed += 3.0f * a_deltaT;
	}

	if (Input.IsDown(Key::Down) && m_speed > -10.5f)
	{
		if (m_parent->m_mainMenu)
		{
	 		m_parent->m_mainMenu = false;
			m_parent->m_background->Get<Material>().textures[0] = Load<Texture>("Textures/asteroids_background");
			m_parent->m_background->Get<SoundSource>().Stop();
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
		if (m_parent->m_mainMenu)
		{
			m_parent->m_mainMenu = false;
			m_parent->m_background->Get<Material>().textures[0] = Load<Texture>("Textures/asteroids_background");
			m_parent->m_background->Get<SoundSource>().Stop();
		}

		SoundSource &bullet = m_spaceShipNode->Get<SoundSource>();
		bullet.Play();
		m_coolDown = 1.0f;

		CreateBullet();
	}

	if (m_velocity.Length() > 1.0f) 
	{
		m_velocity.Normalize();
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

	m_resetTimer -= a_deltaT;

	if (m_resetTimer < 0.0f && !m_spaceShipNode->IsEnabled())
	{
		m_parent->ResetAsteroids();
		m_parent->m_spaceShip.m_score = 0;
		m_parent->m_spaceShip.m_level = 1;
		m_parent->m_mainMenu = true;
		m_parent->m_background->Get<Material>().textures[0] = Load<Texture>("Textures/title_background");

		Log("\nDead!\n");

		m_parent->m_background->Get<SoundSource>().Play();
	}

	if (m_parent->m_debrisList.size() == 0 && m_spaceShipNode->IsEnabled())
	{
		m_level = m_level + 1;
		m_parent->ResetAsteroids();
		m_parent->m_mainMenu = true;
		m_parent->m_background->Get<Material>().textures[0] = Load<Texture>("Textures/finished_background");

		Log("\nNext Level!\n");

		m_victorySound->Get<SoundSource>().Play();
	}
}

void SpaceShip::CreateBullet()
{
	Bullet* tempBullet = new Bullet();

	tempBullet->m_bulletNode->rotation = m_spaceShipNode->rotation;
	tempBullet->m_bulletNode->position = m_spaceShipNode->position + m_spaceShipNode->rotation.GetForward() * 1.5f;
	tempBullet->m_bulletNode->Add<Mesh>(Load<Model>("Models/asteroid_s"));
	tempBullet->m_bulletNode->Add<Material>(Load<Shader>("Shaders/WireFrame")).CreateUniformBuffers();
	tempBullet->m_bulletNode->Add<SoundSource>(Load<Sound>("Sounds/EE_AlienExplode"));

	tempBullet->m_bulletNode->Get<Material>().buffers[0]->SetUniform("Color", vec3(1.0f, 1.0f, 1.0f));

	m_parent->m_renderGroup->Add(tempBullet->m_bulletNode);

	m_bullets.push_back(tempBullet);
}

void SpaceShip::Destroy()
{
	m_deathSound->Get<SoundSource>().Play();
	m_deathSound2->Get<SoundSource>().Play();

	m_spaceShipNode->Disable();
	m_resetTimer = 5.0f;
	
	for (auto debris : m_parent->m_debrisList)
	{
		m_parent->m_renderGroup->Remove(*debris->m_debrisNode);
	}
	m_parent->m_debrisList.clear();
	m_parent->m_mainMenu = true;

	for (int i = 0; i < 8; i++)
	{
		SmallDebris* tempDebris = new SmallDebris();
		tempDebris->m_debrisNode->Add<Mesh>(Load<Model>("Models/asteroid_m"));
		tempDebris->m_debrisNode->Add<Material>(Load<Shader>("Shaders/WireFrame")).CreateUniformBuffers();

		tempDebris->m_debrisNode->Get<Material>().buffers[0]->SetUniform("Color", vec3(1.0f, 1.0f, 1.0f));
		tempDebris->m_speed = 4.0f;

		tempDebris->m_debrisNode->position = m_spaceShipNode->position;
		tempDebris->MoveRandom();

		m_parent->m_renderGroup->Add(tempDebris->m_debrisNode);
		tempDebris->SetShip(this);

		m_parent->m_debrisList.push_back(tempDebris);
	}
}