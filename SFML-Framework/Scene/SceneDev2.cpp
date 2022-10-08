#include "SceneDev2.h"
#include "../Framework/InputMgr.h"
#include "SceneMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObject.h"

SceneDev2::SceneDev2()
	:Scene(Scenes::Dev2)
{
	SpriteObj* obj = new SpriteObj();
	obj->SetTexture(*RESOURCE_MGR->GetTexture("graphics/player5.png"));
	objList.push_back(obj);

	TextObject* ui1 = new TextObject();
	ui1->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	ui1->SetString("dev2");
	ui1->SetPos({ 1200, 0 });
	UiObjList.push_back(ui1);
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Enter()
{
	
}

void SceneDev2::Exit()
{
}

void SceneDev2::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev1);
	}
	Scene::Update(dt);
}

void SceneDev2::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
