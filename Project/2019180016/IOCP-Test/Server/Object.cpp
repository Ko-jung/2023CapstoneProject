#include "Object.h"

Object::Object(float x, float y, float z, float rx, float ry, float rz)
{
	this->x = x; this->y = y; this->z = z;
	Pitch = rx; Yaw = ry; Roll = rz;
}

void Object::MoveLocation(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
}
