#pragma once
#include "SpriteObj.h"

enum class ItemType
{
	None = -1,
	BallSizeUp,
	BallSpeedUp,
	Breaker,
	BatLengthUp,
	Explode,
	Count,
};

class Item : public SpriteObj
{
protected:
	ItemType type;
public:
	Item(ItemType type);
	virtual ~Item();

	void SetType(ItemType type);
	ItemType GetType() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

