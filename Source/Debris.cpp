#include "Debris.h"
#include "Persistent.h"

#include <Jewel3D/Application/Application.h>
#include <Jewel3D/Utilities/Random.h>
#include <Jewel3D/Rendering/Material.h>
#include <Jewel3D/Rendering/Mesh.h>

using namespace Jwl;

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
	velocity.Normalize();

	auto& mesh = owner.Require<Mesh>();
	switch (size)
	{
	case Small:
		mesh.AddData(Load<Model>("Models/asteroid_small"));
		break;

	case Medium:
		mesh.AddData(Load<Model>("Models/asteroid_medium"));
		break;

	case Large:
		mesh.AddData(Load<Model>("Models/asteroid_large"));
		break;
	}

	auto& mat = owner.Require<Material>();
	mat.shader = Load<Shader>("Shaders/WireFrame");
	mat.CreateUniformBuffers();
	mat.buffers[0]->SetUniform("Color", vec3(RandomRange(0.2f, 1.0f), RandomRange(0.2f, 1.0f), RandomRange(0.2f, 1.0f)));

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
			owner.Get<Material>().buffers[0]->SetUniform("Animation", elapsed);
		}
	}
}

void Debris::Destroy()
{
	if (size > Small)
	{
		for (unsigned i = 0; i < 3; i++)
		{
			auto debris = Entity::MakeNew();
			debris->position = owner.position;

			debris->Add<Debris>(speed * 1.5f, static_cast<Size>(size - 1));
		}
	}

	alive = false;
}
