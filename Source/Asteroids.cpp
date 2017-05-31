#include "Asteroids.h"

#include <Jewel3D/Sound/SoundSource.h>
#include <Jewel3D/Rendering/Mesh.h>
#include <Jewel3D/Rendering/Material.h>
#include <Jewel3D/Utilities/Random.h>
#include <Jewel3D/Math/Math.h>

using namespace Jwl;

void Asteroids::InitAsteroids(EntityGroup* a_rg)
{
	m_renderGroup = a_rg;
	m_spaceShip.m_parent = this;

	m_spaceShip.m_spaceShipNode->Add<Mesh>(Load<Model>("Models/ship.model"));
	m_spaceShip.m_spaceShipNode->Add<Material>(Load<Shader>("Shaders/WireFrame.shader")).CreateUniformBuffers();
	m_spaceShip.m_spaceShipNode->Add<SoundSource>(Load<Sound>("Sounds/EE_HeroBullet.wav"));

	m_spaceShip.m_victorySound->Add<SoundSource>(Load<Sound>("Sounds/EE_Victory.wav"));
	m_spaceShip.m_deathSound->Add<SoundSource>(Load<Sound>("Sounds/EE_Intro.wav"));
	m_spaceShip.m_deathSound2->Add<SoundSource>(Load<Sound>("Sounds/EE_HeroExplode.wav"));

	m_background->Add<Mesh>(Load<Model>("Models/background.model"));
	m_background->Add<Material>(Shader::MakeNewPassThrough(), Load<Texture>("Textures/title_background.texture")).CreateUniformBuffers();
	m_background->Add<SoundSource>(Load<Sound>("Sounds/EE_VictoryMusic.wav"));

	m_background->RotateX(270.0f);
	m_background->scale = -vec3::One * 20.0f;
	m_background->position -= vec3::Y * 5.0f;

	SoundSource &music = m_background->Get<SoundSource>();
	music.SetLooping(true);
	music.Play();

	m_renderGroup->Add(m_background);
	
	m_listener->Add<SoundListener>();
	m_listener->RotateY(180.0f);

	m_spaceShip.m_spaceShipNode->Get<Material>().buffers[0]->SetUniform("Color", vec3(1.0f, 1.0f, 1.0f));

	for (int i = 0; i < NUM_START_ASTEROIDS; i++)
	{
		BigDebris* tempDebris = new BigDebris();
		tempDebris->m_debrisNode->Add<Mesh>(Load<Model>("Models/asteroid_l.model"));
		tempDebris->m_debrisNode->Add<Material>(Load<Shader>("Shaders/WireFrame.shader")).CreateUniformBuffers();

		tempDebris->m_debrisNode->Get<Material>().buffers[0]->SetUniform("Color",
			vec3(RandomRangef(0,1), RandomRangef(0,1), RandomRangef(0,1)));

		tempDebris->m_debrisNode->position =
			vec3(sin(ToRadian(i * (360.0f / NUM_START_ASTEROIDS))) * 13.0f, 0.0f, cos(ToRadian(i * (360.0f / NUM_START_ASTEROIDS))) * 13.0f);
		tempDebris->MoveRandom();

		m_renderGroup->Add(tempDebris->m_debrisNode);
		tempDebris->SetShip(&m_spaceShip);

		m_debrisList.push_back(tempDebris);
	}
}

void Asteroids::ResetAsteroids()
{
	for (auto debris : m_debrisList)
	{
		m_renderGroup->Remove(*debris->m_debrisNode);
	}
	m_debrisList.clear();

	m_spaceShip.m_spaceShipNode->Enable();
	m_spaceShip.Reset();	

	for (int i = 0; i < NUM_START_ASTEROIDS + (m_spaceShip.m_level - 1); i++)
	{
		BigDebris* tempDebris = new BigDebris();
		tempDebris->m_debrisNode->Add<Mesh>(Load<Model>("Models/asteroid_l.model"));
		tempDebris->m_debrisNode->Add<Material>(Load<Shader>("Shaders/WireFrame.shader")).CreateUniformBuffers();

		tempDebris->m_debrisNode->Get<Material>().buffers[0]->SetUniform("Color", 
			vec3(RandomRangef(0, 1), RandomRangef(0, 1), RandomRangef(0, 1)));

		tempDebris->m_debrisNode->position =
			vec3(sin(ToRadian(i * (360.0f / (NUM_START_ASTEROIDS + (m_spaceShip.m_level - 1))))) * 13.0f,
			0.0f, cos(ToRadian(i * (360.0f / (NUM_START_ASTEROIDS + (m_spaceShip.m_level - 1))))) * 13.0f);
		tempDebris->MoveRandom();

		m_renderGroup->Add(tempDebris->m_debrisNode);
		tempDebris->SetShip(&m_spaceShip);

		m_debrisList.push_back(tempDebris);
	}

	m_mainMenu = false;
}

void Asteroids::UpdateAsteroids(float a_deltaT)
{
	m_spaceShip.Update(a_deltaT);

	if (m_mainMenu)
		return;

	for (auto itr = m_debrisList.begin(); itr != m_debrisList.end(); itr++)
	{
 		(*itr)->Update(a_deltaT);

		if (((*itr)->m_debrisNode->position - m_spaceShip.m_spaceShipNode->position).Length() < (*itr)->m_size + 0.5f
			&& m_spaceShip.m_spaceShipNode->IsEnabled())
		{
			m_spaceShip.Destroy();
			return;
		}

		for (auto itr2 = m_spaceShip.m_bullets.begin(); itr2 != m_spaceShip.m_bullets.end(); ++itr2)
		{
			if (((*itr)->m_debrisNode->position - (*itr2)->m_bulletNode->position).Length() < (*itr)->m_size)
			{
				(*itr2)->m_age = 50.0f; // I don't want to destroy it here.
				(*itr2)->m_bulletNode->Get<SoundSource>().Play();

				Debris* temp = (*itr);
				m_debrisList.erase(itr);
				temp->OnDestroy();
				return;
			}
		}
	}
}