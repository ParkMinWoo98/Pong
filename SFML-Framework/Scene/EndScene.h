#pragma once
#include "Scene.h"
#include "../GameObject/TextObject.h"

class EndScene : public Scene
{
protected:
	TextObject* text;

public:
	EndScene();
	virtual ~EndScene();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt) override;
};

