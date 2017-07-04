#include "Bullet.h"
#include "Persistent.h"

#include <Jewel3D/Application/Application.h>
#include <Jewel3D/Rendering/Material.h>
#include <Jewel3D/Rendering/Mesh.h>
#include <Jewel3D/Sound/SoundSource.h>

using namespace Jwl;

Bullet::Bullet(Entity &owner)
	: Component(owner)
{
	auto& mesh = owner.Require<Mesh>();
	mesh.AddData(Load<Model>("Models/asteroid_small"));

	auto& mat = owner.Require<Material>();
	mat.shader = Load<Shader>("Shaders/WireFrame");
	mat.CreateUniformBuffers();

	auto& sound = owner.Require<SoundSource>();
	sound.AddData(Load<Sound>("Sounds/AlienExplode"));

	owner.Require<Persistent>();
}

void Bullet::Update()
{
	age += Application.GetDeltaTime();
	if (age > 20.0f)
	{
		Destroy();
		return;
	}

	owner.position += owner.rotation.GetForward() * 20.0f * Application.GetDeltaTime();

	// Wrap around the screen.
	if (abs(owner.position.x) > 22.5f)
	{
		owner.position.x *= -0.99f;
	}

	if (abs(owner.position.z) > 22.5f)
	{
		owner.position.z *= -0.99f;
	}
}

void Bullet::Destroy()
{
	owner.Get<Persistent>().MarkForDestruction();
}
