#include "Bullet.h"
#include "Persistent.h"

#include <gemcutter/Application/Application.h>
#include <gemcutter/Rendering/Mesh.h>
#include <gemcutter/Resource/Material.h>
#include <gemcutter/Resource/Model.h>
#include <gemcutter/Sound/SoundSource.h>

using namespace gem;

Bullet::Bullet(Entity& owner)
	: Component(owner)
{
	auto& mesh = owner.Require<Mesh>();
	mesh.SetMaterial(Load<Material>("Materials/WireFrame"));
	mesh.SetModel(Load<Model>("Models/asteroid_small"));

	auto& sound = owner.Require<SoundSource>();
	sound.SetData(Load<Sound>("Sounds/AlienExplode"));

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

	owner.position -= owner.rotation.GetForward() * 20.0f * Application.GetDeltaTime();

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
