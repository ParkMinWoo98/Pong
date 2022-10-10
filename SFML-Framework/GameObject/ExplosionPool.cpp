#include "ExplosionPool.h"

ExplosionPool::ExplosionPool()
{
    for (int i = 0; i < 5; ++i)
    {
        unUsingExp.push_back(new Explosion());
    }
}

ExplosionPool::~ExplosionPool()
{
    Release();
    for (auto exp : unUsingExp)
    {
        delete exp;
    }
}

Explosion* ExplosionPool::GetExplosion()
{
    Explosion* exp = unUsingExp.front();
    unUsingExp.pop_front();
    usingExp.push_back(exp);
    exp->Init();
    return exp;
}

void ExplosionPool::ReturnExplosion(Explosion* exp)
{
    unUsingExp.push_back(exp);
    usingExp.remove(exp);
}

void ExplosionPool::Init()
{
    Release();
    for (auto exp : unUsingExp)
    {
        exp->Init();
    }
}

void ExplosionPool::Release()
{
    auto it = usingExp.begin();
    while (it != usingExp.end())
    {
        unUsingExp.push_back(*it);
        it = unUsingExp.erase(it);
    }
}
