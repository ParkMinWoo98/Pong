#pragma once
#include "Scene.h"
#include "../GameObject/Ball.h"

class SceneDev1 : public Scene
{
protected:
	Ball* ball;
public:
	SceneDev1();
	virtual ~SceneDev1();

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

