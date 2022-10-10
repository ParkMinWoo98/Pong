#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../GameObject/Object.h"

using namespace sf;

enum class Scenes
{
	Start,
	Menu,
	Stage1,
	Stage2,
	Stage3,
	End,
};

class Scene
{
protected:
	Scenes type;
	list<Object*> objList;
	list<Object*> UiObjList;

public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

