#pragma once
#include "Item.h"
#include <vector>
#include <list>

class ItemPool
{
private:
	vector<list<Item*>*> unUsingItems;
	vector<list<Item*>*> usingItems;
public:
	ItemPool();
	~ItemPool();

	Item* GetItem() const;
	void ReturnItem(Item* item);

	void Init();
	void Release();
};

