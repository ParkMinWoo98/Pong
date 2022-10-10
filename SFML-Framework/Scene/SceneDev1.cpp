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
	bat = new Bat();
	objList.push_back(bat);
	ball = new Ball();
	objList.push_back(ball);
	ball->SetBat(bat);
	itemPool = new ItemPool();
	for (int i = 0; i < 4; ++i)
	{
		Block* block = new Block();
		block->SetPos(Vector2f(100 + 150.f * i, 300.f));
		blocks.push_back(block);
		objList.push_back(block);
	}
	expPool = new ExplosionPool();

	TextObject* ui1 = new TextObject();
	ui1->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	ui1->SetString("dev1");
	ui1->SetPos({ 1200, 0 });
	UiObjList.push_back(ui1);
}

SceneDev1::~SceneDev1()
{
	if (itemPool != nullptr)
		delete itemPool;
	itemPool = nullptr;
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
	Release();
	Scene::Init();
	itemPool->Init();
	expPool->Init();
	for (auto it = blocks.begin(); it != blocks.end(); ++it)
	{
		Item* item = itemPool->GetItem();
		(*it)->SetItem(item);
		if (item != nullptr)
		{
			items.push_back(item);
			objList.push_back(item);
		}
	}
}

void SceneDev1::Release()
{
	for (auto item : items)
	{
		itemPool->ReturnItem(item);
	}
	items.clear();
	for (auto exp : exps)
	{
		expPool->ReturnExplosion(exp);
	}
	exps.clear();
	Scene::Release();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	for (auto it = exps.begin(); it != exps.end();)
	{
		(*it)->Update(dt);
		if (!(*it)->GetActive())
		{
			expPool->ReturnExplosion((*it));
			it = exps.erase(it);
			continue;
		}
		++it;
	}
	ball->OnCollisionScreen(FRAMEWORK->GetWindowSize());
	if (ball->CollideWith(bat->GetRect()))
		ball->OnCollision(bat->GetRect());
	for (auto block : blocks)
	{
		if (block->GetAlive())
		{
			if (ball->CollideWith(block->GetRect()))
			{
				ball->OnCollisionBlock(block->GetRect());
				block->Die();
			}
			for (auto exp : exps)
			{
				if (exp->CollideWith(block->GetRect()))
				{
					block->Die();
				}
			}
		}
	}
	for (auto it = items.begin(); it != items.end();)
	{
		if ((*it)->GetActive())
		{
			if (ball->CollideWith((*it)->GetRect()))
			{
				switch ((*it)->GetType())
				{
				case ItemType::BallSizeUp:
					ball->EffectOn(Effects::SizeUp);
					break;
				case ItemType::BallSpeedUp:
					ball->EffectOn(Effects::SpeedUp);
					break;
				case ItemType::Breaker:
					ball->EffectOn(Effects::Breaker);
					break;
				case ItemType::BatLengthUp:
					bat->EffectOn();
					break;
				case ItemType::Explode:
					{
						Explosion* exp = expPool->GetExplosion();
						exp->SetPos((*it)->GetPos());
						exp->Explode();
						exps.push_back(exp);
					}
					break;
				default:
					break;
				}
				(*it)->SetActive(false);
				itemPool->ReturnItem((*it));
				objList.remove((*it));
				it = items.erase(it);
				continue;
			}
		}
		++it;
	}
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	for (auto exp : exps)
	{
		exp->Draw(window);
	}
}
