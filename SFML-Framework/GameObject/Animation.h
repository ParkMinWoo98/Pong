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

	bool isActive;
	bool isLoop;
public:
	Animation();
	~Animation();

	void SetSprite(const Texture& tex, Origins origin);
	void SetCycle(float cycle);
	void SetPos(const Vector2f& pos);
	void SetRotation(float rotate);
	void SetColor(Color color);
	void SetSize(const Vector2f& scale);
	void FlipX(bool isFlipped);
	void SetLoop(bool isLoop);

	Sprite* GetSprite() const;
	FloatRect GetRect() const;
	bool GetActive() const;

	void Init();
	void Update(float dt);
	void Draw(RenderWindow& window);
};

