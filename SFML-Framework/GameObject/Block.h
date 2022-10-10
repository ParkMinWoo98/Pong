#pragma once
#include "Object.h"
#include "Animation.h"

class Item;

class Block : public Object
{
protected:
	Animation* curAnim;
	vector<Animation*> anims;

	Item* item;

	bool isAlive;
public:
	Block();
	virtual ~Block();

	void SetAlive(bool isAlive);
	bool GetAlive() const;
	void SetItem(Item* item);
	
	void Die();

	FloatRect GetRect() const;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};
