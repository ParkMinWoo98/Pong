#include "SpriteObj.h"

SpriteObj::SpriteObj()
{
}

SpriteObj::~SpriteObj()
{
}

void SpriteObj::Init()
{
	Object::Init();
}

void SpriteObj::Release()
{
	Object::Release();
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

void SpriteObj::SetColor(Color color)
{
	sprite.setColor(color);
}

FloatRect SpriteObj::GetRect() const
{
	return sprite.getGlobalBounds();
}

void SpriteObj::SetTexture(const Texture& tex)
{
	sprite.setTexture(tex);
}
