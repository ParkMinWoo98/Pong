#pragma once
#include "SpriteObj.h"
#include <SFML/Graphics.hpp>

class Ball : public SpriteObj
{
protected:
	FloatRect ballRect;
	Vector2f ballCenter;

	float speed;
	Vector2f currDir;
	bool isMoving;

public:
	Ball();
	virtual ~Ball();

	virtual void Init() override;
	virtual void Release() override {}
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetTexture(const Texture& texture);

	void SetBallRect();
	void SetBallCenter();
	void SetSpeed(float speed);

	void ChangeDir(float dt);
	void Fire();
	bool OnCollision(const FloatRect& rect);
	bool OnCollisionScreen(const Vector2i& windowSize);
};
