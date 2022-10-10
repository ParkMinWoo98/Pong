#include "Ball.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/SoundMgr.h"
#include <cmath>
#include "Bat.h"

constexpr auto PI = 3.141592;

Ball::Ball()
	:life(3), speed(500), angle(0), isMoving(false), curAnim(nullptr), absRotation(0.01f)
	, isEffectOn(false), effectTimer(0.f), effectTimerSet(5.f), effect(Effects::None), bat(nullptr)
{
	sprite = new Sprite();
	sprite->setTexture(*RESOURCE_MGR->GetTexture("graphics/ninja/waiting.png"));
	Utils::SetOrigin(*sprite, Origins::BC);
	vector<vector<string>> ballnames;
	ballnames.push_back({ "graphics/ninja/1.png", "graphics/ninja/2.png", "graphics/ninja/3.png", "graphics/ninja/4.png", "graphics/ninja/5.png", "graphics/ninja/6.png" });
	ballnames.push_back({"graphics/ninja/dash1.png", "graphics/ninja/dash2.png", "graphics/ninja/dash3.png", "graphics/ninja/dash4.png", "graphics/ninja/dash5.png", "graphics/ninja/dash6.png" });
	ballnames.push_back({ "graphics/ninja/breaker1.png", "graphics/ninja/breaker2.png", "graphics/ninja/breaker3.png", "graphics/ninja/breaker4.png", "graphics/ninja/breaker5.png",
		"graphics/ninja/breaker6.png", "graphics/ninja/breaker7.png", "graphics/ninja/breaker8.png", "graphics/ninja/breaker9.png", "graphics/ninja/breaker10.png",
		"graphics/ninja/breaker11.png", "graphics/ninja/breaker12.png" });
	for (const auto& ballname : ballnames)
	{
		Animation* anim = new Animation();
		anim->SetCycle(0.1f);
		for (auto& ball : ballname)
		{
			anim->SetSprite(*RESOURCE_MGR->GetTexture(ball), Origins::BC);
		}
		anims.push_back(anim);
	}
	curAnim = anims[0];
}

Ball::~Ball()
{
	for (auto anim : anims)
	{
		delete anim;
	}
}

void Ball::Init()
{
	life = 3;
	Object::Init();
	SetStart();
}

void Ball::Release()
{
	Object::Release();
}

void Ball::Update(float dt)
{
	Object::Update(dt);
	curAnim->Update(dt);
	if (!isMoving)
	{
		ChangeDir(dt);
		SetPos(bat->GetTopPos());
		curAnim->SetRotation(rotation);
		curAnim->SetPos(position + currDir * 50.f);
		sprite->setPosition(position);
		if (InputMgr::GetKeyDown(Keyboard::Space))
			Fire();
		return;
	}
	if (isEffectOn)
	{
		effectTimer -= dt;
		if (effectTimer <= 0.f)
			EffectOff();
	}
	position += currDir * speed * dt;
	SetRotation();
	curAnim->SetPos(position);
}

void Ball::Draw(RenderWindow& window)
{
	if (!isMoving)
		window.draw(*sprite);
	curAnim->Draw(window);
}

void Ball::SetStart()
{
	curAnim->Init();
	isMoving = false;
	if (isEffectOn)
		EffectOff();
	effectTimer = 0.f;
	absRotation = 0.01f;
	SetPos(bat->GetTopPos());
	curAnim->SetColor({ 255, 255, 255, 128 });
	sprite->setPosition(position);
	curAnim->SetPos(position);
	curAnim->SetRotation(rotation);
	FlipX();
}

void Ball::SetSpeed(float speed)
{
	this->speed = speed;
}

void Ball::SetRotation()
{
	angle = asin(currDir.x);
	if (currDir.y > 0)
		angle = PI - angle;
	rotation = angle / 2 / PI * 360;
	curAnim->SetRotation(rotation);
}

void Ball::FlipX()
{
	curAnim->FlipX(currDir.x >= 0.f);
}

void Ball::SetBat(Bat* bat)
{
	this->bat = bat;
}

void Ball::SetLife(int life)
{
	this->life = life;
}

int Ball::GetLife() const
{
	return life;
}

void Ball::EffectOn(Effects effect)
{
	if(isEffectOn)
		EffectOff();
	this->effect = effect;
	switch (this->effect)
	{
	case Effects::SizeUp:
		curAnim->SetSize(Vector2f(2.f, 2.f));
		break;
	case Effects::SpeedUp:
		curAnim = anims[1];
		speed *= 2.f;
		break;
	case Effects::Breaker:
		curAnim = anims[2];
		break;
	default:
		break;
	}
	isEffectOn = true;
	effectTimer = effectTimerSet;
}

void Ball::EffectOff()
{
	switch (effect)
	{
	case Effects::SizeUp:
		curAnim->SetSize(Vector2f(0.5f, 0.5f));
		break;
	case Effects::SpeedUp:
		curAnim = anims[0];
		speed *= 0.5f;
		break;
	case Effects::Breaker:
		curAnim = anims[0];
		break;
	default:
		break;
	}
	isEffectOn = false;
}

void Ball::ChangeDir(float dt)
{
	absRotation += InputMgr::GetAxisRaw(Axis::Vertical) * 100 * dt;
	if (absRotation <= 0.f)
		absRotation = 0.01f;
	if (absRotation > 90)
		absRotation = 90;
	if (InputMgr::GetAxisRaw(Axis::Horizontal) == 0.f)
		rotation = rotation >= 0.f ? absRotation : -absRotation;
	else
		rotation = InputMgr::GetAxisRaw(Axis::Horizontal) > 0.f ? absRotation : -absRotation;
	float scaleX = rotation  > 0 ? abs(sprite->getScale().x) : -abs(sprite->getScale().x);
	sprite->setScale(scaleX, abs(sprite->getScale().y));
	angle = rotation / 360 * 2 * PI;
	currDir = Vector2f(sin(angle), -cos(angle));
	FlipX();
}

void Ball::Fire()
{
	isMoving = true;
	curAnim->SetColor({ 255, 255, 255, 255 });
}

bool Ball::CollideWith(const FloatRect& rect)
{
	ballRect = curAnim->GetRect();
	return ballRect.intersects(rect);
}

void Ball::OnCollision(const FloatRect& rect)
{
	if (!isMoving)
		return;
	ballCenter.x = ballRect.left + ballRect.width * 0.5f;
	ballCenter.y = ballRect.top + ballRect.height * 0.5f;

	if (ballCenter.x < rect.left && currDir.x > 0)
	{
		position.x = rect.left - ballRect.width * 0.5f;
		currDir.x *= -1;
	}
	else if (ballCenter.x > rect.left + rect.width && currDir.x < 0)
	{
		position.x = rect.left + rect.width + ballRect.width * 0.5f;
		currDir.x *= -1;
	}
	if (ballCenter.y > rect.top + rect.height && currDir.y < 0)
	{
		position.y = rect.top + rect.height + ballRect.height;
		currDir.y *= -1;
	}
	else if (ballCenter.y < rect.top && currDir.y > 0)
	{
		position.y = rect.top;
		currDir.y *= -1;
	}
	FlipX();
	curAnim->SetPos(position);
}

void Ball::OnCollisionBlock(const FloatRect& rect)
{
	if (isEffectOn && effect == Effects::Breaker)
		return;
	OnCollision(rect);
	SOUND_MGR->Play("sound/attack.wav");
}

void Ball::OnCollisionScreen(const Vector2i& windowSize)
{
	if (!isMoving)
		return;
	ballRect = curAnim->GetRect();
	if (ballRect.top < 0.f)
	{
		position.y = ballRect.height;
		currDir.y *= -1;
	}
	else if (ballRect.top + ballRect.height > windowSize.y)
	{
		--life;
		SetStart();
	}
	if (ballRect.left < 0.f)
	{
		position.x = ballRect.width * 0.5f;
		currDir.x *= -1;
	}
	else if (ballRect.left + ballRect.width > windowSize.x)
	{
		position.x = windowSize.x - ballRect.width * 0.5f;
		currDir.x *= -1;
	}
	FlipX();
	curAnim->SetPos(position);
}
