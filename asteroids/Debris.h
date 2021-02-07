#pragma once
#include <gemcutter/Entity/Entity.h>

class Debris : public gem::Component<Debris>
{
public:
	enum Size
	{
		Small = 1,
		Medium = 2,
		Large = 3
	};

	Debris(gem::Entity &owner, float speed, Size size);

	void Update();
	void Destroy();
	bool IsAlive() const;

	const float speed;
	const Size size;
	const unsigned scoreValue;

private:
	gem::vec3 randomSpin[2];
	gem::vec3 velocity;
	
	bool alive = true;
	float elapsed = 0.0f;
};
