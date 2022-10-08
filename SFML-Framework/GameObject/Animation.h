#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Animation
{
private:
	vector<Texture*> textures;
	int count;
	float cycle;
	float time;
public:
	Animation();
	~Animation();

	void SetTexture(Texture& tex);
	void SetCycle(float cycle);

	const Texture& GetTexture();

	void Init();
	void Update(float dt);
};

