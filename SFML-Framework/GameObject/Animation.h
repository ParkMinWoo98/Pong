#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Framework/Utils.h"

using namespace sf;
using namespace std;

class Animation
{
private:
	vector<Sprite*> sprites;
	int count;
	float cycle;
	float time;

	Vector2f position;
	float rotation;
public:
	Animation();
	~Animation();

	void SetSprite(const Texture& tex, Origins origin);
	void SetCycle(float cycle);
	void SetPos(const Vector2f& pos);
	void SetRotation(float rotate);
	void SetSize(const Vector2f& scale);
	void FlipX(bool isFlipped);

	Sprite* GetSprite() const;
	const FloatRect& GetRect();

	void Init();
	void Update(float dt);
	void Draw(RenderWindow& window);
};

