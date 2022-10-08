#include "Animation.h"

Animation::Animation()
	:count(0), cycle(0), time(0)
{
}

Animation::~Animation()
{
}

void Animation::SetTexture(Texture& tex)
{
	textures.push_back(&tex);
}

void Animation::SetCycle(float cycle)
{
	this->cycle = cycle;
}

const Texture& Animation::GetTexture()
{
	return *textures[count];
}

void Animation::Init()
{
	count = 0;
	time = 0.f;
}

void Animation::Update(float dt)
{
	time += dt;
	if (time >= cycle)
	{
		time = 0.f;
		if (count == textures.size() - 1)
			count = 0;
		else
			++count;
	}
}
