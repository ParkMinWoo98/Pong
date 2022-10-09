#include "Block.h"

Block::Block(BlockType type)
	:type(type), isAlive(true)
{
}

Block::~Block()
{
}

BlockType Block::GetType() const
{
	return type;
}

const FloatRect& Block::GetRect()
{
	return sprite.getGlobalBounds();
}

bool Block::GetAlive() const
{
	return isAlive;
}

void Block::Init()
{
	isAlive = true;
}

void Block::Release()
{
	SpriteObj::Release();
	isAlive = false;
}

void Block::Update(float dt)
{
}

void Block::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}
