#pragma once
#include "Object.h"

class SpriteObj : public Object
{
protected:
	Sprite sprite;
public:
	SpriteObj();
	virtual ~SpriteObj();

	virtual void Init() override;
	virtual void Release() override {}
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetOrigin(Origins origin);
	virtual void SetPos(const Vector2f& pos);
	virtual void SetRotation(float rotate);

	virtual void SetTexture(Texture& tex);
};

