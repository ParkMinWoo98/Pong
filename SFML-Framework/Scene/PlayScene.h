#pragma once
#include "Scene.h"
#include "../GameObject/Ball.h"
#include "../GameObject/Block.h"
#include "../GameObject/ItemPool.h"
#include "../GameObject/ExplosionPool.h"
#include "../GameObject/Bat.h"
#include "../GameObject/TextObject.h"

class PlayScene : public Scene
{
protected:
	Ball* ball;
	Bat* bat;
	list<Block*> blocks;
	list<Item*> items;
	list<Explosion*> exps;

	ItemPool* itemPool;
	ExplosionPool* expPool;

	TextObject* ballLife;

public:
	PlayScene(Scenes stage);
	virtual ~PlayScene();

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

