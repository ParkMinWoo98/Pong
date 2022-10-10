#pragma once
#include "Object.h"
#include "Animation.h"

class Bat : public Object
{
protected:
	float speed;

	bool isEffectOn;
	float effectTimer;
	float effectTimerSet;

	float currDirX;

	Animation* anim;

public:
	Bat();
	virtual ~Bat();

	void FlipX();

	void EffectOn();
	void EffectOff();
	
	float GetDirX() const;
	Vector2f GetTopPos() const;
	FloatRect GetRect() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

