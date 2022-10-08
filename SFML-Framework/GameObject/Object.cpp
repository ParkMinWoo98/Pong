#include "Object.h"

Object::Object()
{
	Init();
}

Object::~Object()
{
	Release();
}

void Object::SetActive(bool active)
{
	enabled = active;
}

bool Object::GetActive() const
{
	return enabled;
}

void Object::Init()
{
}

void Object::Release()
{
}

void Object::Update(float dt)
{
}

void Object::Draw(RenderWindow& window)
{
}

void Object::SetPos(const Vector2f& pos)
{
	position = pos;
}

void Object::SetRotation(float rotate)
{
	rotation = rotate;
}

const Vector2f& Object::GetPos() const
{
	return position;
}

float Object::GetRotation() const
{
	return rotation;
}
