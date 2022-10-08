#include "SpriteObj.h"

SpriteObj::SpriteObj()
{
}

SpriteObj::~SpriteObj()
{
}

void SpriteObj::Init()
{
}

void SpriteObj::Update(float dt)
{
	sprite.setPosition(position);
	sprite.setRotation(rotation);
}

void SpriteObj::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

void SpriteObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position);
}

void SpriteObj::SetRotation(float rotate)
{
	Object::SetRotation(rotate);
	sprite.setRotation(rotation);
}

void SpriteObj::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}
