#include "SceneDev1.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObject.h"
#include "../Framework/SoundMgr.h"

SceneDev1::SceneDev1()
	:Scene(Scenes::Dev1)
{
	Animation* ball1 = new Animation();
	ball1->SetCycle(0.1f);
	string ballname1[] = { "graphics/redball1.png", "graphics/redball2.png", "graphics/redball3.png", "graphics/redball4.png", "graphics/redball5.png" ,"graphics/redball6.png" };
	for (auto& ballname : ballname1)
	{
		ball1->SetTexture(*RESOURCE_MGR->GetTexture(ballname));
	}
	Anims.push_back(ball1);

	ball = new Ball();
	ball->SetActive(true);
	ball->SetAnim(ball1);
	ball->Init();
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
	for (auto anim : Anims)
	{
		anim->Update(dt);
	}
	Scene::Update(dt);
	ball->OnCollisionScreen(FRAMEWORK->GetWindowSize());
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
