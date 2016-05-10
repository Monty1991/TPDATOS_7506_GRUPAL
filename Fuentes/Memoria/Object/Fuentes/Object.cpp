#include "../Headers/Object.h"

Object::Object(): refCount(0)
{
}

Object::~Object()
{
	
}

void Object::Dispose()
{
	if (--this->refCount < 1)
		delete this;
}

void Object::IncrementarContador()
{
	this->refCount++;
}
