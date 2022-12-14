#include "Scene.h"

Scene::Scene(Scenes type)
	:type(type)
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (auto obj : objList)
	{
		obj->Init();
	}
	for (auto obj : UiObjList)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : objList)
	{
		obj->Release();
	}
	for (auto obj : UiObjList)
	{
		obj->Release();
	}
}

void Scene::Update(float dt)
{
	for ( auto obj : objList)
	{
		if (obj->GetActive())
			obj->Update(dt);
	}
	for (auto obj : UiObjList)
	{
		if (obj->GetActive())
			obj->Update(dt);
	}
}

void Scene::Draw(RenderWindow& window)
{
	for (auto obj : objList)
	{
		if (obj->GetActive())
			obj->Draw(window);
	}
	for (auto obj : UiObjList)
	{
		if (obj->GetActive())
			obj->Draw(window);
	}
}
