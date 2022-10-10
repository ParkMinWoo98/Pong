#pragma once
#include "Object.h"
#include "Animation.h"

enum class BlockType
{
	Normal,
	Elite,
};

class Item;

class Block : public Object
{
protected:
	Animation* curAnim;
	vector<Animation*> anims;

	BlockType type;
	int life;

	Item* item;

	bool isAlive;
public:
	Block(BlockType type);
	virtual ~Block();

	void SetAlive(bool isAlive);
	bool GetAlive() const;
	void SetItem(Item* item);
	
	void Hit();
	void Die();

	FloatRect GetRect() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};
