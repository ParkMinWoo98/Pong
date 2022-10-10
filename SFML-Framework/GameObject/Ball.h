#pragma once
#include "Object.h"
#include "Animation.h"

enum class Effects
{
	None = -1,
	SizeUp,
	SpeedUp,
	Breaker,
};

class Bat;

class Ball : public Object
{
protected:
	int life;

	Sprite* sprite;

	FloatRect ballRect;
	Vector2f ballCenter;

	float speed;
	float absRotation;
	float angle;
	Vector2f currDir;
	bool isMoving;

	bool isEffectOn;
	float effectTimer;
	float effectTimerSet;
	Effects effect;

	Animation* curAnim;
	vector<Animation*> anims;

	Bat* bat;

public:
	Ball();
	virtual ~Ball();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetStart();

	void SetSpeed(float speed);
	void SetRotation();
	void FlipX();

	void SetBat(Bat* bat);

	void SetLife(int life);
	int GetLife() const;

	void EffectOn(Effects effect);
	void EffectOff();

	void ChangeDir(float dt);
	void Fire();
	bool CollideWith(const FloatRect& rect);
	void OnCollision(const FloatRect& rect);
	void OnCollisionBlock(const FloatRect& rect);
	void OnCollisionScreen(const Vector2i& windowSize);
};
