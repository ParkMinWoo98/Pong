#pragma once
#include "Scene.h"
#include "../GameObject/TextObject.h"

class StartScene : public Scene
{
protected:
	TextObject* text;

public:
	StartScene();
	virtual ~StartScene();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt) override;
};

