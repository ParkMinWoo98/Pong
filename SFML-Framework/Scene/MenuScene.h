#pragma once
#include "Scene.h"
#include "../GameObject/TextObject.h"

class MenuScene : public Scene
{
protected:
	vector<TextObject*> texts;

	int stage;
public:
	MenuScene();
	virtual ~MenuScene();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt) override;
};

