#include "EndScene.h"
#include "../GameObject/SpriteObj.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "SceneMgr.h"

EndScene::EndScene()
	:Scene(Scenes::End)
{
	SpriteObj* background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/map.png"));
	background->SetColor({ 255, 255, 255, 100 });
	objList.push_back(background);

	text = new TextObject();
	text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	text->SetString("End");
	text->SetOrigin(Origins::MC);
	text->SetPos((Vector2f)FRAMEWORK->GetWindowSize() * 0.5f);
	text->SetSize(Vector2f(1.8f, 1.8f));
	UiObjList.push_back(text);
}

EndScene::~EndScene()
{
}

void EndScene::Enter()
{
}

void EndScene::Exit()
{
}

void EndScene::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKey(Keyboard::Return))
		FRAMEWORK->Done();
}
