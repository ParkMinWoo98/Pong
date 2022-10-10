#pragma once
#include "Scene.h"
#include "../GameObject/Ball.h"
#include "../GameObject/Block.h"
#include "../GameObject/ItemPool.h"
#include "../GameObject/ExplosionPool.h"
#include "../GameObject/Bat.h"

class SceneDev1 : public Scene
{
protected:
	Ball* ball;
	Bat* bat;
	list<Block*> blocks;
	list<Item*> items;
	list<Explosion*> exps;

	ItemPool* itemPool;
	ExplosionPool* expPool;
public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

