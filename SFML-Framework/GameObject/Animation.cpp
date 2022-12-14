#include "Animation.h"

Animation::Animation()
	:count(0), cycle(0), time(0), rotation(0), isActive(true), isLoop(true)
{
}

Animation::~Animation()
{
}

void Animation::SetSprite(const Texture& tex, Origins origin)
{
	Sprite* sprite = new Sprite();
	sprite->setTexture(tex);
	Utils::SetOrigin(*sprite, origin);
	sprites.push_back(sprite);
}

void Animation::SetCycle(float cycle)
{
	this->cycle = cycle;
}

void Animation::SetPos(const Vector2f& pos)
{
	position = pos;
	sprites[count]->setPosition(position);
}

void Animation::SetRotation(float rotate)
{
	rotation = rotate;
	sprites[count]->setRotation(rotate);
}

void Animation::SetColor(Color color)
{
	for (auto sprite : sprites)
	{
		sprite->setColor(color);
	}
}

void Animation::SetSize(const Vector2f& scale)
{
	for (auto sprite : sprites)
	{
		sprite->scale(scale);
	}
}

void Animation::FlipX(bool isFlipped)
{
	for (auto sprite : sprites)
	{
		if (isFlipped)
			sprite->setScale(abs(sprite->getScale().x), abs(sprite->getScale().y));
		else
			sprite->setScale(-abs(sprite->getScale().x), abs(sprite->getScale().y));
	}
}

void Animation::SetLoop(bool isLoop)
{
	this->isLoop = isLoop;
}

Sprite* Animation::GetSprite() const
{
	return sprites[count];
}

FloatRect Animation::GetRect() const
{
	return sprites[count]->getGlobalBounds();
}

bool Animation::GetActive() const
{
	return isActive;
}

void Animation::Init()
{
	count = 0;
	time = 0.f;
}

void Animation::Update(float dt)
{
	if (isActive)
	{
		time += dt;
		if (time >= cycle)
		{
			time = 0.f;
			if (count == sprites.size() - 1)
			{
				if (!isLoop)
					isActive = false;
				count = 0;
			}				
			else
				++count;
		}
		sprites[count]->setPosition(position);
		sprites[count]->setRotation(rotation);
	}
}

void Animation::Draw(RenderWindow& window)
{
	if(isActive)
		window.draw(*sprites[count]);
}
