#include "../Headers/Object.h"

void Object::Attach()
{
	this->refCount++;
}

void Object::Dettach()
{ 
	this->refCount--;
	if (!this->refCount)
		delete this;
}

Object *Object::UnAlias()
{
	if (this->refCount == 1)
		return this;

	this->refCount--;
	return new Object(*this);
}
