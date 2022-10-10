#include "Block.h"
#include "../Framework/ResourceMgr.h"
#include "Item.h"

Block::Block()
	:isAlive(true), item(nullptr), curAnim(nullptr)
{
	vector<vector<string>> blocknames;
	blocknames.push_back({ "graphics/block1/8.png", "graphics/block1/9.png", "graphics/block1/10.png", "graphics/block1/11.png", "graphics/block1/12.png"
		, "graphics/block1/13.png" , "graphics/block1/14.png" , "graphics/block1/15.png" , "graphics/block1/16.png" });
	blocknames.push_back({ "graphics/block1/1.png", "graphics/block1/2.png", "graphics/block1/3.png", "graphics/block1/4.png", "graphics/block1/5.png"
		, "graphics/block1/5.png", "graphics/block1/6.png", "graphics/block1/7.png" });
	for (const auto& blockname : blocknames)
	{
		Animation* anim = new Animation();
		anim->SetCycle(0.1f);
		for (auto& block : blockname)
		{
			anim->SetSprite(*RESOURCE_MGR->GetTexture(block), Origins::MC);
		}
		anims.push_back(anim);
	}
	anims[1]->SetColor({ 255, 255, 255, 150 });
	anims[1]->SetLoop(false);
	curAnim = anims[0];
}

Block::~Block()
{
	for (auto anim : anims)
	{
		delete anim;
	}
}

void Block::SetAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

bool Block::GetAlive() const
{
	return isAlive;
}

void Block::SetItem(Item* item)
{
	this->item = item;
}

void Block::Die()
{
	if (item != nullptr)
	{
		item->SetPos(position);
		item->SetActive(true);
	}
	curAnim = anims[1];
	isAlive = false;
}

FloatRect Block::GetRect() const
{
	return curAnim->GetRect();
}

void Block::Init()
{
	Object::Init();
	isAlive = true;
	for (auto anim : anims)
	{
		anim->Init();
	}
	curAnim = anims[0];
	for(auto& anim : anims)
		anim->SetPos(position);
}

void Block::Release()
{
	Object::Release();
}

void Block::Update(float dt)
{
	Object::Update(dt);
	curAnim->Update(dt);
	if (!curAnim->GetActive())
		Release();
}

void Block::Draw(RenderWindow& window)
{
	curAnim->Draw(window);
}
