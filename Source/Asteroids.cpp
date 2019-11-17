#include "Asteroids.h"
#include "Debris.h"
#include "Bullet.h"
#include "Persistent.h"

#include <Jewel3D/Math/Math.h>
#include <Jewel3D/Rendering/Material.h>
#include <Jewel3D/Rendering/Mesh.h>
#include <Jewel3D/Resource/Model.h>
#include <Jewel3D/Sound/SoundListener.h>
#include <Jewel3D/Sound/SoundSource.h>

#define NUM_START_ASTEROIDS 4

using namespace Jwl;

Asteroids::Asteroids(std::vector<Entity::Ptr>& a_rg)
	: renderGroup(a_rg)
{
	spaceShip.m_parent = this;

	spaceShip.m_spaceShipNode->Add<Mesh>(Load<Model>("Models/ship"));
	spaceShip.m_spaceShipNode->Add<Material>(Load<Shader>("Shaders/WireFrame")).CreateUniformBuffers();
	spaceShip.m_spaceShipNode->Get<Material>().buffers[0]->SetUniform("Color", vec3(1.0f, 1.0f, 1.0f));
	spaceShip.m_spaceShipNode->Add<SoundSource>(Load<Sound>("Sounds/HeroBullet"));

	spaceShip.m_victorySound->Add<SoundSource>(Load<Sound>("Sounds/Victory"));
	spaceShip.m_deathSound->Add<SoundSource>(Load<Sound>("Sounds/Intro"));
	spaceShip.m_deathSound2->Add<SoundSource>(Load<Sound>("Sounds/HeroExplode"));

	background->Add<Mesh>(Load<Model>("Models/background"));
	background->Add<Material>(Load<Texture>("Textures/title_background"));
	background->Add<SoundSource>(Load<Sound>("Sounds/VictoryMusic"));

	background->RotateX(270.0f);
	background->scale = -vec3::One * 20.0f;
	background->position -= vec3::Up * 5.0f;

	SoundSource &music = background->Get<SoundSource>();
	music.SetLooping(true);
	music.Play();

	renderGroup.push_back(background);

	listener->Add<SoundListener>();
	listener->RotateY(180.0f);
}

void Asteroids::Reset()
{
	for (auto& ent : With<Debris>())
	{
		ent.Get<Persistent>().MarkForDestruction();
	}

	for (auto& ent : With<Bullet>())
	{
		ent.Get<Persistent>().MarkForDestruction();
	}

	spaceShip.Reset();

	PlaceAsteroids();

	mainMenu = false;
}

void Asteroids::Update(float a_deltaT)
{
	spaceShip.Update(a_deltaT);

	if (mainMenu)
		return;

	for (auto& ent : CaptureWith<Debris>())
	{
		auto& debris = ent->Get<Debris>();
		debris.Update();

		if (!debris.IsAlive())
			continue;

		if (spaceShip.alive &&
			LengthSquared(ent->position - spaceShip.m_spaceShipNode->position) < (debris.size * debris.size))
		{
			spaceShip.Destroy();
			return;
		}

		for (auto& bullet : With<Bullet>())
		{
			if (LengthSquared(debris.owner.position - bullet.position) < (debris.size * debris.size))
			{
				bullet.Get<Persistent>().MarkForDestruction();
				bullet.Get<SoundSource>().Play();

				debris.Destroy();
			}
		}
	}
}

void Asteroids::PlaceAsteroids()
{
	auto amount = NUM_START_ASTEROIDS + (spaceShip.m_level - 1);

	for (int i = 0; i < amount; i++)
	{
		auto debris = Entity::MakeNew();
		debris->Add<Debris>(1.0f, Debris::Size::Large);

		debris->position =
			vec3(sin(ToRadian(i * (360.0f / amount))),
				0.0f,
				cos(ToRadian(i * (360.0f / amount)))) * 13.0f;
	}
}
