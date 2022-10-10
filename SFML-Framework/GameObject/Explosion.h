#pragma once
#include "Object.h"
#include "Animation.h"

class Explosion : public Object
{
protected:
	Animation* anim;

	FloatRect rect;
public:
	Explosion();
	virtual ~Explosion();

	bool CollideWith(const FloatRect& rect);
	void Explode();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

