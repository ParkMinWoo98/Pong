#include "StartScene.h"
#include "../GameObject/SpriteObj.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "SceneMgr.h"

StartScene::StartScene()
	:Scene(Scenes::Start)
{
	SpriteObj* background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/map.png"));
	background->SetColor({ 255, 255, 255, 100 });
	objList.push_back(background);

	text = new TextObject();
	text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	text->SetString("Press Enter to start");
	text->SetOrigin(Origins::MC);
	text->SetPos((Vector2f)FRAMEWORK->GetWindowSize() * 0.5f);
	text->SetSize(Vector2f(1.8f, 1.8f));
	UiObjList.push_back(text);
}

StartScene::~StartScene()
{
}

void StartScene::Enter()
{
}

void StartScene::Exit()
{
}

void StartScene::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Return))
		SCENE_MGR->ChangeScene(Scenes::Menu);
}
