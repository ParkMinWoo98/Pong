#include "Bat.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"

Bat::Bat()
	:speed(300), effectTimer(0.f), effectTimerSet(5.f), isEffectOn(false), anim(nullptr), currDirX(0.f)
{
	string names[] = { "graphics/bat/bat1.png", "graphics/bat/bat2.png", "graphics/bat/bat3.png", "graphics/bat/bat4.png" };
	anim = new Animation();
	for (auto& name : names)
	{
		anim->SetSprite(*RESOURCE_MGR->GetTexture(name), Origins::BC);
	}
	anim->SetCycle(0.1f);
}

Bat::~Bat()
{
	if (anim != nullptr)
		delete anim;
	anim = nullptr;
}

void Bat::FlipX()
{
	anim->FlipX(currDirX >= 0.f);
}

void Bat::EffectOn()
{
	isEffectOn = true;
	effectTimer = effectTimerSet;
	anim->SetSize(Vector2f(2.f, 2.f));
}

void Bat::EffectOff()
{
	isEffectOn = false;
	anim->SetSize(Vector2f(0.5f, 0.5f));
}

float Bat::GetDirX() const
{
	return currDirX;
}

Vector2f Bat::GetTopPos() const
{
	return Vector2f(position.x, GetRect().top);
}

FloatRect Bat::GetRect() const
{
	return anim->GetRect();
}

void Bat::Init()
{
	Object::Init();
	position = Vector2f(640 * 0.5f, 1000.f);
	anim->Init();
	FlipX();
}

void Bat::Release()
{
	Object::Release();
}

void Bat::Update(float dt)
{
	effectTimer -= dt;
	if (isEffectOn && effectTimer <= 0.f)
		EffectOff();
	currDirX = InputMgr::GetAxisRaw(Axis::Horizontal);
	if (currDirX != 0.f)
	{
		position.x += currDirX * speed * dt;
		anim->Update(dt);
		FlipX();
	}
	anim->SetPos(position);
}

void Bat::Draw(RenderWindow& window)
{
	anim->Draw(window);
}
