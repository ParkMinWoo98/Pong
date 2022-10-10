#include "Explosion.h"
#include "../Framework/ResourceMgr.h"

Explosion::Explosion()
{
	string names[] = { "graphics/explosion/explosion1.png", "graphics/explosion/explosion2.png", "graphics/explosion/explosion3.png", "graphics/explosion/explosion4.png"
   , "graphics/explosion/explosion5.png" , "graphics/explosion/explosion6.png" , "graphics/explosion/explosion7.png" , "graphics/explosion/explosion8.png"
   , "graphics/explosion/explosion9.png" , "graphics/explosion/explosion10.png" , "graphics/explosion/explosion11.png" , "graphics/explosion/explosion12.png" };
	anim = new Animation();
	for (auto& name : names)
	{
		anim->SetSprite(*RESOURCE_MGR->GetTexture(name), Origins::MC);
	}
	anim->SetCycle(0.1f);
	anim->SetLoop(false);
}

Explosion::~Explosion()
{
}

bool Explosion::CollideWith(const FloatRect& rect)
{
	this->rect = anim->GetRect();
	return (this->rect).intersects(rect);
}

void Explosion::Explode()
{
	enabled = true;
	//사운드 재생
}

void Explosion::Init()
{
	enabled = false;
	anim->Init();
}

void Explosion::Release()
{
	Object::Release();
}

void Explosion::Update(float dt)
{
	Object::Update(dt);
	anim->SetPos(position);
	anim->Update(dt);
	if (!anim->GetActive())
		Release();
}

void Explosion::Draw(RenderWindow& window)
{
	anim->Draw(window);
}
