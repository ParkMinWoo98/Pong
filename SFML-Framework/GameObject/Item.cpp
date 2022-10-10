#include "Item.h"

Item::Item(ItemType type)
    :type(type)
{
}

Item::~Item()
{
}

void Item::SetType(ItemType type)
{
    this->type = type;
}

ItemType Item::GetType() const
{
    return type;
}

void Item::Init()
{
    enabled = false;
}

void Item::Release()
{
}

void Item::Update(float dt)
{
}

void Item::Draw(RenderWindow& window)
{
    SpriteObj::Draw(window);
}
