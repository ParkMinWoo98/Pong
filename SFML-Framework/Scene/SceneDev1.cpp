#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObject.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/Ball.h"

SceneDev1::SceneDev1()
	:Scene(Scenes::Dev1)
{
	ball = new Ball();
	ball->SetTexture(*RESOURCE_MGR->GetTexture("graphics/1.png"));
	ball->SetPos({ 1280 * 0.5f, 720 * 0.9f });
	ball->SetSpeed(500);
	objList.push_back(ball);

	TextObject* ui1 = new TextObject();
	ui1->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	ui1->SetString("dev1");
	ui1->SetPos({ 1200, 0 });
	UiObjList.push_back(ui1);
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Enter()
{
	SOUND_MGR->Play("sound/normal_bgm.wav", true);
}

void SceneDev1::Exit()
{
	SOUND_MGR->StopAll();
}

void SceneDev1::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Return))
	{
		SOUND_MGR->Play("sound/select.wav");
	}
	Scene::Update(dt);
	ball->OnCollisionScreen(FRAMEWORK->GetWindowSize());
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
