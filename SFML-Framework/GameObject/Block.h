#pragma once
#include "SpriteObj.h"

enum class BlockType
{
	Normal,
	BallSizeUp,
	BallSpeedUp,
	Breaker,
	BatLengthUp,
	Explode,
};

class Block : public SpriteObj
{
protected:
	BlockType type;
	
	bool isAlive;

public:
	Block(BlockType type);
	virtual ~Block();

	BlockType GetType() const;
	const FloatRect& GetRect();
	bool GetAlive() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};
