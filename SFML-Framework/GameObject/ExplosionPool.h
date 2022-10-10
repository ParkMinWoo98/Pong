#pragma once
#include "Explosion.h"
#include <list>

class ExplosionPool
{
protected:
	list<Explosion*> unUsingExp;
	list<Explosion*> usingExp;

public:
	ExplosionPool();
	~ExplosionPool();

	Explosion* GetExplosion();
	void ReturnExplosion(Explosion* exp);

	void Init();
	void Release();
};

