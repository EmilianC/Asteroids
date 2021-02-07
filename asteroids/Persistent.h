#pragma once
#include <Jewel3D/Entity/Entity.h>

//- Allows an Entity to manage its own lifetime.
//- An Entity with this component will not be deleted until MarkForDestruction() or Destroy() are called.
//- For example, a projectile can keep itself alive until it collides with another entity.
class Persistent : public Jwl::Component<Persistent>
{
public:
	Persistent(Jwl::Entity &owner);

	void Destroy();
	void MarkForDestruction();

	bool IsMarkedForDestruction() const;

	//- Destroys all Persistent Entities that have been marked for destruction.
	static void Collect();

private:
	bool alive = true;
	Jwl::Entity::Ptr _owningPtr;
};
