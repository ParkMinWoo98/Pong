#include "Ball.h"
#include "../Framework/InputMgr.h"

Ball::Ball()
	:speed(0), isMoving(false)
{
	currDir = Utils::Normalize(Vector2f(1, 1));
}

Ball::~Ball()
{
}

void Ball::Init()
{
	speed = 0;
	isMoving = false;
}

void Ball::Update(float dt)
{
	SpriteObj::Update(dt);
	if (!isMoving)
	{
		ChangeDir(dt);
		return;
	}
	SpriteObj::SetPos(currDir * speed * dt);
}

void Ball::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Ball::SetTexture(const Texture& tex)
{
	SpriteObj::SetTexture(tex);
	SetOrigin(Origins::BC);
	SetBallRect();
	SetBallCenter();
}

void Ball::SetBallRect()
{
	ballRect = sprite.getGlobalBounds();
}

void Ball::SetBallCenter()
{
	ballCenter.x = ballRect.left + ballRect.width * 0.5f;
	ballCenter.y = ballRect.top + ballRect.height * 0.5f;
}

void Ball::SetSpeed(float speed)
{
	this->speed = speed;
}

void Ball::ChangeDir(float dt)
{
	if (InputMgr::GetKey(Keyboard::Key::A) && currDir.x > -1)
		currDir.x -= 100 * dt;
	if (InputMgr::GetKey(Keyboard::Key::D) && currDir.x < 1)
		currDir.x += 100 * dt;
	currDir = Utils::Normalize(currDir);
}

void Ball::Fire()
{
	isMoving = true;
}

bool Ball::OnCollision(const FloatRect& rect)
{
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
	sprite.setPosition(position);
	return true;
}

bool Ball::OnCollisionScreen(const Vector2i& windowSize)
{
	if (ballRect.top < 0.f)
	{
		position.y = ballRect.height;
		currDir.y *= -1;
	}
	else if (ballRect.top + ballRect.height > windowSize.y)
	{
		Init();
		currDir.y *= -1;
	}
	if (ballRect.left < 0.f)
	{
		position.x = ballRect.width * 0.5f;
		currDir.x *= -1;
	}
	if (ballRect.left + ballRect.width > windowSize.x)
	{
		position.x = windowSize.x - ballRect.width * 0.5f;
		currDir.x *= -1;
	}
	sprite.setPosition(position);
}
