#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../Framework/Utils.h"

using namespace sf;
using namespace std;

class Object
{
protected:
	int id;
	string name;
	bool enabled;

	Vector2f position;
	float rotation;
	Vector2f scale;

public:
	Object();
	virtual ~Object();

	virtual void SetActive(bool active);
	virtual bool GetActive() const;

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetPos(const Vector2f& pos);
	virtual void SetRotation(float rotate);

	virtual const Vector2f& GetPos() const;
	virtual float GetRotation() const;	
};

