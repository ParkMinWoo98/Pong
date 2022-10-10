#include "SceneMgr.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"

bool SceneMgr::Init()
{
	sceneMap[Scenes::Start] = new StartScene();
	sceneMap[Scenes::Menu] = new MenuScene();
	sceneMap[Scenes::Stage1] = new PlayScene(Scenes::Stage1);
	sceneMap[Scenes::Stage2] = new PlayScene(Scenes::Stage2);
	sceneMap[Scenes::Stage3] = new PlayScene(Scenes::Stage3);
	sceneMap[Scenes::End] = new EndScene();

	currScene = Scenes::Start;
	sceneMap[currScene]->Init();
	sceneMap[currScene]->Enter();

	return true;
}

Scenes SceneMgr::GetCurrScene() const
{
	return currScene;
}

Scene* SceneMgr::GetScene(Scenes scene)
{
	return sceneMap[scene];
}

void SceneMgr::ChangeScene(Scenes scene)
{
	sceneMap[currScene]->Exit();
	currScene = scene;
	sceneMap[currScene]->Init();
	sceneMap[currScene]->Enter();
}

void SceneMgr::Update(float dt)
{
	sceneMap[currScene]->Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Escape))
		FRAMEWORK->Done();
}

void SceneMgr::Draw(RenderWindow& window)
{
	sceneMap[currScene]->Draw(window);
}
