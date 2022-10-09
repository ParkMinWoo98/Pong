#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

enum class Effects
{
	None = -1,
	SizeUp,
	SpeedUp,
	Breaker,
};

class Ball : public Object
{
protected:
	FloatRect ballRect;
	Vector2f ballCenter;

	float speed;
	float angle;
	Vector2f currDir;
	bool isMoving;

	float effectTimer;
	float effectTimerSet;
	bool isEffectOn;
	Effects effect;

	Animation* curAnim;
	vector<Animation*> anims;

public:
	Ball();
	virtual ~Ball();

	virtual void Init() override;
	virtual void Release() override {}
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSpeed(float speed);
	void SetRotation();
	void FlipX();

	void EffectOn(Effects effect);
	void EffectOff();

	void ChangeDir(float dt);
	void Fire();
	bool CollideWith(const FloatRect& rect);
	void OnCollision(const FloatRect& rect);
	void OnCollisionScreen(const Vector2i& windowSize);
};
