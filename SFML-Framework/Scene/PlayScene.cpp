#include "PlayScene.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../Framework/SoundMgr.h"
#include <fstream>

PlayScene::PlayScene(Scenes stage)
	:Scene(stage)
{
	SpriteObj* background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/map.png"));
	background->SetColor({ 255, 255, 255, 150 });
	objList.push_back(background);
	bat = new Bat();
	objList.push_back(bat);
	ball = new Ball();
	objList.push_back(ball);
	ball->SetBat(bat);
	itemPool = new ItemPool();
	string blockFileName = "tables/stage" + to_string((int)type - 1) + ".txt";
	ifstream ifs(blockFileName);
	vector<string> blockLocation;
	string str;
	while (getline(ifs, str))
	{
		blockLocation.push_back(str);
	}
	ifs.close();
	Vector2f curLocation = { 40.f, 40.f };
	for (const auto& string : blockLocation)
	{
		for (auto it = string.begin(); it != string.end(); ++it)
		{
			int count;
			switch (*it)
			{
			case 'N':
				count = *(++it) - 48;
				for (int i = 0; i < count; ++i)
				{
					Block* block = new Block(BlockType::Normal);
					block->SetPos(curLocation);
					blocks.push_back(block);
					objList.push_back(block);
					curLocation.x += 100.f;
				}
				break;
			case 'E':
				count = *(++it) - 48;
				for (int i = 0; i < count; ++i)
				{
					Block* block = new Block(BlockType::Elite);
					block->SetPos(curLocation);
					blocks.push_back(block);
					objList.push_back(block);
					curLocation.x += 100.f;
				}
				break;
			case 'S':
				count = *(++it) - 48;
				for (int i = 0; i < count; ++i)
				{
					curLocation.x += 100.f;
				}
				break;
			default:
				break;
			}
		}
		curLocation.x = 40.f;
		curLocation.y += 100.f;
	}
	expPool = new ExplosionPool();

	TextObject* stageText = new TextObject();
	stageText->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	stageText->SetString("Stage " + to_string((int)stage - 1));
	stageText->SetPos({ 20, 20 });
	stageText->SetFillColor({ 255, 255, 0, 255 });
	UiObjList.push_back(stageText);

	ballLife = new TextObject();
	ballLife->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	ballLife->SetPos(Vector2f(FRAMEWORK->GetWindowSize().x - 20, 20));
	ballLife->SetOrigin(Origins::TR);
	ballLife->SetFillColor({ 255, 255, 0, 255 });
	UiObjList.push_back(ballLife);
}

PlayScene::~PlayScene()
{
	if (itemPool != nullptr)
		delete itemPool;
	itemPool = nullptr;
}

void PlayScene::Enter()
{
	SOUND_MGR->Play("sound/normal_bgm.wav", true);
}

void PlayScene::Exit()
{
	SOUND_MGR->StopAll();
}

void PlayScene::Init()
{
	SOUND_MGR->Play("sound/normal_bgm.wav", true);
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

void PlayScene::Release()
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
	SOUND_MGR->StopAll();
}

void PlayScene::Update(float dt)
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
	ballLife->SetString("Life = " + to_string(ball->GetLife()));
	ballLife->SetOrigin(Origins::TR);
	if (ball->GetLife() <= 0)
		Init();
	if (ball->CollideWith(bat->GetRect()))
		ball->OnCollision(bat->GetRect());
	for (auto block : blocks)
	{
		if (block->GetAlive())
		{
			if (ball->CollideWith(block->GetRect()))
			{
				ball->OnCollisionBlock(block->GetRect());
				block->Hit();
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
	auto it = blocks.begin();
	while (1)
	{
		if (it == blocks.end())
		{
			SCENE_MGR->ChangeScene(Scenes((int)type + 1));
			break;
		}
		if ((*it)->GetActive())
			break;
		++it;
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
						SOUND_MGR->Play("sound/explosion.wav");
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

void PlayScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	for (auto exp : exps)
	{
		exp->Draw(window);
	}
}
