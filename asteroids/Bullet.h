#pragma once
#include <Jewel3D/Entity/Entity.h>

class Bullet : public Jwl::Component<Bullet>
{
public:
	Bullet(Jwl::Entity& owner);

	void Update();
	void Destroy();

private:
	float age = 0.0f;
};
