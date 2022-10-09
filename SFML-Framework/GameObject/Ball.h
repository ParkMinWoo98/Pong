#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Ball : public Object
{
protected:
	FloatRect ballRect;
	Vector2f ballCenter;

	float speed;
	float angle;
	Vector2f currDir;
	bool isMoving;

	Animation* anim;
public:
	Ball();
	virtual ~Ball();

	virtual void Init() override;
	virtual void Release() override {}
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSpeed(float speed);
	void SetRotation();

	void ChangeDir(float dt);
	void Fire();
	bool OnCollision(const FloatRect& rect);
	bool OnCollisionScreen(const Vector2i& windowSize);
};
