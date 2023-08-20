#include "Debris.h"
#include "Persistent.h"

#include <gemcutter/Application/Application.h>
#include <gemcutter/Rendering/Mesh.h>
#include <gemcutter/Resource/Material.h>
#include <gemcutter/Resource/Model.h>
#include <gemcutter/Utilities/Random.h>

using namespace gem;

Debris::Debris(Entity &owner, float _speed, Size _size)
	: Component(owner)
	, speed(_speed)
	, size(_size)
	, scoreValue(_size * 100)
{
	randomSpin[0] = RandomDirection();
	randomSpin[1] = RandomDirection();

	velocity.x = RandomRange(-1.0f, 1.0f);
	velocity.z = RandomRange(-1.0f, 1.0f);
	velocity = Normalize(velocity);

	auto& mesh = owner.Require<Mesh>();
	switch (size)
	{
	case Small:
		mesh.SetModel(Load<Model>("Models/asteroid_small"));
		break;

	case Medium:
		mesh.SetModel(Load<Model>("Models/asteroid_medium"));
		break;

	case Large:
		mesh.SetModel(Load<Model>("Models/asteroid_large"));
		break;
	}

	mesh.SetMaterial(Load<Material>("Materials/WireFrame"));
	mesh.buffers[0].SetUniform("Color", vec3(RandomRange(0.2f, 1.0f), RandomRange(0.2f, 1.0f), RandomRange(0.2f, 1.0f)));

	owner.Require<Persistent>();
}

void Debris::Update()
{
	owner.Rotate(randomSpin[0], Application.GetDeltaTime() * 35.0f);
	owner.Rotate(randomSpin[1], Application.GetDeltaTime() * 35.0f);

	owner.position += velocity * Application.GetDeltaTime() * speed;

	// Wrap around the screen.
	if (abs(owner.position.x) > 22.5f)
	{
		owner.position.x *= -0.99f;
	}

	if (abs(owner.position.z) > 22.5f)
	{
		owner.position.z *= -0.99f;
	}

	if (!alive)
	{
		elapsed += Application.GetDeltaTime() * 3.0f;
		if (elapsed > 1.0f)
		{
			owner.Get<Persistent>().MarkForDestruction();
		}
		else
		{
			owner.Get<Renderable>().buffers[0].SetUniform("Animation", elapsed);
		}
	}
}

void Debris::Destroy()
{
	if (!alive)
		return;

	alive = false;

	if (size > Small)
	{
		for (unsigned i = 0; i < 3; i++)
		{
			auto debris = Entity::MakeNew();
			debris->position = owner.position;

			debris->Add<Debris>(speed * 1.5f, static_cast<Size>(size - 1));
		}
	}
}

bool Debris::IsAlive() const
{
	return alive;
}

REFLECT_COMPONENT_SIMPLE(Debris);
