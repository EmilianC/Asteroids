#include "Persistent.h"

using namespace Jwl;

Persistent::Persistent(Entity &owner)
	: Component(owner)
{
	_owningPtr = owner.GetPtr();
}

void Persistent::Destroy()
{
	alive = false;

	// Unparent the object to remove the strong reference.
	if (auto ptr = owner.GetParent())
	{
		ptr->RemoveChild(owner);
	}

	ASSERT(_owningPtr.use_count() == 1, "Persistent Entity cannot be destroyed, it has external references.");
	_owningPtr.reset();
}

void Persistent::MarkForDestruction()
{
	alive = false;
}

bool Persistent::IsMarkedForDestruction() const
{
	return !alive;
}

void Persistent::Collect()
{
	auto& index = GetComponentIndex<Persistent>();

	for (unsigned i = index.size(); i-- > 0;)
	{
		auto ptr = static_cast<Persistent*>(index[i]);
		if (ptr->IsMarkedForDestruction())
		{
			ptr->Destroy();
		}
	}
}
