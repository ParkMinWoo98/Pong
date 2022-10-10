#include "ItemPool.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"

ItemPool::ItemPool()
{
    for (int i = 0; i < (int)ItemType::Count; ++i)
    {
        list<Item*>* items = new list<Item*>();
        for (int j = 0; j < 5; ++j)
        {
            Item* item = new Item((ItemType)i);
            switch ((ItemType)i)
            {
            case ItemType::BallSizeUp:
                item->SetTexture(*RESOURCE_MGR->GetTexture("graphics/redball2.png"));
                break;
            case ItemType::BallSpeedUp:
                item->SetTexture(*RESOURCE_MGR->GetTexture("graphics/redball2.png"));
                break;
            case ItemType::Breaker:
                item->SetTexture(*RESOURCE_MGR->GetTexture("graphics/redball2.png"));
                break;
            case ItemType::BatLengthUp:
                item->SetTexture(*RESOURCE_MGR->GetTexture("graphics/redball2.png"));
                break;
            case ItemType::Explode:
                item->SetTexture(*RESOURCE_MGR->GetTexture("graphics/redball2.png"));
                break;
            }            
            items->push_back(item);
        }
        unUsingItems.push_back(items);
    }
    for (int i = 0; i < (int)ItemType::Count; ++i)
    {
        list<Item*>* items = new list<Item*>();
        usingItems.push_back(items);
    }
}

ItemPool::~ItemPool()
{
    Release();
    for (int i = 0; i < (int)ItemType::Count; ++i)
    {
        for (auto item : *unUsingItems[i])
        {
            delete item;
        }
    }
}

Item* ItemPool::GetItem() const
{
    // 아이템 없을 확률 66.67퍼
    ItemType type = ItemType::None;
    int itemOn = Utils::Range(0, (int)ItemType::Count * 3);
    if (itemOn / (int)ItemType::Count == 0)
        type = (ItemType)itemOn;

    if(type == ItemType::None)
        return nullptr;
    Item* temp = unUsingItems[(int)type]->front();
    unUsingItems[(int)type]->pop_front();
    usingItems[(int)type]->push_back(temp);
    return temp;
}

void ItemPool::ReturnItem(Item* item)
{
    unUsingItems[(int)item->GetType()]->push_back(item);
    usingItems[(int)item->GetType()]->remove(item);
}

void ItemPool::Init()
{
    Release();
}

void ItemPool::Release()
{
    for (int i = 0; i < (int)ItemType::Count; ++i)
    {
        auto it = usingItems[i]->begin();
        while( it != usingItems[i]->end())
        {
            unUsingItems[i]->push_back(*it);
            it = unUsingItems[i]->erase(it);
        }
    }
}
