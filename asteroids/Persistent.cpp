#include "Persistent.h"

#include <gemcutter/Entity/Hierarchy.h>

using namespace gem;

Persistent::Persistent(Entity &owner)
	: Component(owner)
{
	_owningPtr = owner.GetPtr();
}

void Persistent::Destroy()
{
	alive = false;

	// Unparent the object to remove the strong reference.
	if (auto* hierarchy = owner.Try<Hierarchy>())
	{
		if (auto parent = hierarchy->GetParent())
		{
			parent->Get<Hierarchy>().RemoveChild(owner);
		}
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

REFLECT_COMPONENT_SIMPLE(Persistent);
