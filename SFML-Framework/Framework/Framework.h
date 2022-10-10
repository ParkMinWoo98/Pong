#pragma once
#include <SFML/Graphics.hpp>
#include "../3rd/SingleTon.h"

using namespace sf;
class Framework : public Singleton<Framework>
{
protected:
	RenderWindow window;
	Vector2i windowSize;

	// TimeMgr
	Clock clock;
	Time deltaTime;
	float timeScale;

public:
	Framework();
	virtual ~Framework();

	void SetWindowSize(int width, int height);
	const Vector2i& GetWindowSize() const;

	float GetDT() const;
	float GetRealDT() const;

	bool Init();
	bool Do();

	void Done();
};

#define FRAMEWORK (Framework::GetInstance())