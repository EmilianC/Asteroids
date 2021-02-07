#pragma once
#include <gemcutter/Entity/Entity.h>

class Bullet : public gem::Component<Bullet>
{
public:
	Bullet(gem::Entity& owner);

	void Update();
	void Destroy();

private:
	float age = 0.0f;
};
