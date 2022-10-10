#include "MenuScene.h"
#include "../GameObject/SpriteObj.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Framework.h"
#include "SceneMgr.h"

MenuScene::MenuScene()
	:Scene(Scenes::Menu), stage(0)
{
	SpriteObj* background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/map.png"));
	background->SetColor({ 255, 255, 255, 100 });
	objList.push_back(background);

	for (int i = 0; i < 3; ++i)
	{
		TextObject* text = new TextObject();
		text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		text->SetString("Stage " + to_string(i + 1));
		text->SetOrigin(Origins::MC);
		text->SetPos(Vector2f(FRAMEWORK->GetWindowSize().x * 0.5f, FRAMEWORK->GetWindowSize().y * 0.25f * (i + 1)));
		texts.push_back(text);
		UiObjList.push_back(text);
	}
	texts[0]->SetSize(Vector2f(1.5f, 1.5f));
}

MenuScene::~MenuScene()
{
}

void MenuScene::Enter()
{
}

void MenuScene::Exit()
{
}

void MenuScene::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Down) && stage < 2)
	{
		texts[stage++]->SetSize(Vector2f(1.f, 1.f));
		texts[stage]->SetSize(Vector2f(1.5f, 1.5f));
	}
	if (InputMgr::GetKeyDown(Keyboard::Up) && stage > 0)
	{
		texts[stage--]->SetSize(Vector2f(1.f, 1.f));
		texts[stage]->SetSize(Vector2f(1.5f, 1.5f));
	}
	
	if (InputMgr::GetKeyDown(Keyboard::Return))
		SCENE_MGR->ChangeScene((Scenes)(stage + 2));
}
