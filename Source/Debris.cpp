#include "Debris.h"
#include "Asteroids.h"
#include "SpaceShip.h"

#include <Jewel3D/Utilities/Random.h>
#include <Jewel3D/Rendering/Material.h>
#include <Jewel3D/Rendering/Mesh.h>

using namespace Jwl;

void Debris::MoveRandom()
{
	// Two Random axis of rotation
	for (int i = 0; i < 2; i++)
	{
		m_randomSpin[i] = RandomDirection();
	}

	m_velocity.x = RandomRangef(-1.0f, 1.0f);
	m_velocity.z = RandomRangef(-1.0f, 1.0f);
	m_velocity.Normalize();
}

void Debris::Update(float a_deltaT)
{
	m_debrisNode->Rotate(m_randomSpin[0], a_deltaT * 35.0f);
	m_debrisNode->Rotate(m_randomSpin[1], a_deltaT * 35.0f);

	m_debrisNode->position += m_velocity * a_deltaT * m_speed;

	if (abs(m_debrisNode->position.x) > 22.5f)
	{
		m_debrisNode->position.x *= -0.99f;
	}

	if (abs(m_debrisNode->position.z) > 22.5f)
	{
		m_debrisNode->position.z *= -0.99f;
	}
}

void SmallDebris::OnDestroy()
{
	GetShip()->AddScore(300);

	GetShip()->m_parent->m_renderGroup->Remove(*m_debrisNode);
	m_debrisNode->RemoveComponent<Material>();
	m_debrisNode->RemoveComponent<Mesh>();
}

void MediumDebris::OnDestroy()
{
	GetShip()->AddScore(200);

	for (int i = 0; i < 3; i++)
	{
		SmallDebris* tempDebris = new SmallDebris();
		tempDebris->m_debrisNode->Add<Mesh>(Load<Model>("Models/asteroid_s.model"));
		tempDebris->m_debrisNode->Add<Material>(Load<Shader>("Shaders/WireFrame.shader")).CreateUniformBuffers();

		tempDebris->m_debrisNode->Get<Material>().buffers[0]->SetUniform("Color",
			vec3(RandomRangef(0,1), RandomRangef(0,1), RandomRangef(0,1)));

		tempDebris->m_debrisNode->position = m_debrisNode->position;
		tempDebris->MoveRandom();
		tempDebris->m_speed = 3.0f;
		tempDebris->m_size = 1.0f;

		GetShip()->m_parent->m_renderGroup->Add(tempDebris->m_debrisNode);
		tempDebris->SetShip(GetShip());

		GetShip()->m_parent->m_debrisList.push_back(tempDebris);

		GetShip()->m_parent->m_renderGroup->Remove(*m_debrisNode);
		m_debrisNode->RemoveComponent<Material>();
		m_debrisNode->RemoveComponent<Mesh>();
	}
}

void BigDebris::OnDestroy()
{
	GetShip()->AddScore(100);

	for (int i = 0; i < 3; i++)
	{
		MediumDebris* tempDebris = new MediumDebris();
		tempDebris->m_debrisNode->Add<Mesh>(Load<Model>("Models/asteroid_m.model"));
		tempDebris->m_debrisNode->Add<Material>(Load<Shader>("Shaders/WireFrame.shader")).CreateUniformBuffers();

		tempDebris->m_debrisNode->Get<Material>().buffers[0]->SetUniform("Color",
			vec3(RandomRangef(0,1), RandomRangef(0,1), RandomRangef(0,1)));

		tempDebris->m_debrisNode->position = m_debrisNode->position;
		tempDebris->MoveRandom();
		tempDebris->m_speed = 2.0f;
		tempDebris->m_size = 1.5f;

		GetShip()->m_parent->m_renderGroup->Add(tempDebris->m_debrisNode);
		tempDebris->SetShip(GetShip());

		GetShip()->m_parent->m_debrisList.push_back(tempDebris);

		GetShip()->m_parent->m_renderGroup->Remove(*m_debrisNode);
		m_debrisNode->RemoveComponent<Material>();
		m_debrisNode->RemoveComponent<Mesh>();
	}
}
