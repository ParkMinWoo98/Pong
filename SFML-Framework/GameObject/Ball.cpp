#include "Ball.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include <cmath>

constexpr auto PI = 3.141592;

Ball::Ball()
	:speed(500), angle(0), isMoving(false), anim(nullptr)
{
	anim = new Animation();
	anim->SetCycle(0.1f);
	string ballname[] = { "graphics/redball1.png", "graphics/redball2.png", "graphics/redball3.png", "graphics/redball4.png", "graphics/redball5.png" ,"graphics/redball6.png" };
	for (auto& ball : ballname)
	{
		anim->SetSprite(*RESOURCE_MGR->GetTexture(ball), Origins::BC);
	}
}

Ball::~Ball()
{
}

void Ball::Init()
{
	Object::Init();
	anim->Init();
	position = Vector2f(1280 * 0.5f, 720 * 0.9f);
	rotation = 0.f;
	anim->SetPos(position);
	anim->SetRotation(rotation);
	isMoving = false;
}

void Ball::Update(float dt)
{
	Object::Update(dt);
	anim->Update(dt);
	if (!isMoving)
	{
		ChangeDir(dt);
		anim->SetRotation(rotation);
		if (InputMgr::GetKeyDown(Keyboard::Space))
			Fire();
		return;
	}
	position += currDir * speed * dt;
	SetRotation();
	anim->SetPos(position);
}

void Ball::Draw(RenderWindow& window)
{
	anim->Draw(window);
}

void Ball::SetSpeed(float speed)
{
	this->speed = speed;
}

void Ball::SetRotation()
{
	angle = acos(currDir.x);
	if (currDir.y < 0)
		angle = 2 * PI - angle;
	rotation = angle / 2 / PI * 360 + 90;
	anim->SetRotation(rotation);
}

void Ball::ChangeDir(float dt)
{
	if (InputMgr::GetKey(Keyboard::Key::A) && rotation > -90)
		rotation -= 100 * dt;
	if (InputMgr::GetKey(Keyboard::Key::D) && rotation < 90)
		rotation += 100 * dt;

	if (rotation > 90)
		rotation = 90;
	if (rotation < -90)
		rotation = -90;
	angle = (rotation - 90) / 360 * 2 * PI;
	currDir = Vector2f(cos(angle), sin(angle));
}

void Ball::Fire()
{
	isMoving = true;
}

bool Ball::OnCollision(const FloatRect& rect)
{
	ballRect = anim->GetRect();
	ballCenter.x = ballRect.left + ballRect.width * 0.5f;
	ballCenter.y = ballRect.top + ballRect.height * 0.5f;
	if (!ballRect.intersects(rect))
		return false;

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
	anim->SetPos(position);
	return true;
}

bool Ball::OnCollisionScreen(const Vector2i& windowSize)
{
	ballRect = anim->GetRect();
	if (ballRect.top < 0.f)
	{
		position.y = ballRect.height;
		currDir.y *= -1;
	}
	else if (ballRect.top + ballRect.height > windowSize.y)
	{
		Init();
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
	anim->SetPos(position);
	return true;
}
