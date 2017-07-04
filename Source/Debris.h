#pragma once
#include <Jewel3D/Entity/Entity.h>

class Debris : public Jwl::Component<Debris>
{
public:
	enum Size
	{
		Small = 1,
		Medium = 2,
		Large = 3
	};

	Debris(Jwl::Entity &owner, float speed, Size size);

	void Update();
	void Destroy();

	const float speed;
	const Size size;
	const unsigned scoreValue;

private:
	Jwl::vec3 randomSpin[2];
	Jwl::vec3 velocity;
	
	bool alive = true;
	float elapsed = 0.0f;
};
