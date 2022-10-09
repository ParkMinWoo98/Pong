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
	SpriteObj* background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/seamless_space.png"));
	background->SetColor({ 255, 255, 255, 150 });
	objList.push_back(background);

	ball = new Ball();
	objList.push_back(ball);

	for (int i = 0; i < 4; ++i)
	{
		Block* block = new Block(BlockType::BallSpeedUp);
		block->SetTexture(*RESOURCE_MGR->GetTexture("graphics/monster_block1.png"));
		block->SetPos(Vector2f(150.f * i, 300.f ));
		blocks.push_back(block);
		objList.push_back(block);
	}

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

void SceneDev1::Init()
{
	Scene::Init();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	ball->OnCollisionScreen(FRAMEWORK->GetWindowSize());
	for (const auto& block : blocks)
	{
		if (block->GetActive())
		{
			if (ball->CollideWith(block->GetRect()))
			{
				switch (block->GetType())
				{
				case BlockType::BallSizeUp:
					ball->EffectOn(Effects::SizeUp);
					break;
				case BlockType::BallSpeedUp:
					ball->EffectOn(Effects::SpeedUp);
					break;
				case BlockType::Breaker:
					ball->EffectOn(Effects::Breaker);
					break;
				case BlockType::BatLengthUp:
					break;
				case BlockType::Explode:
					break;
				default:
					break;
				}
				ball->OnCollision(block->GetRect());
				block->Release();
			}
		}
	}
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
