#pragma once
#include "Object.h"
#include <string>

using namespace std;

class TextObject : public Object
{
protected:
	Text text;

public:
	TextObject();
	virtual ~TextObject();

	virtual void Init() override;
	virtual void Release() override {}
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetSize(const Vector2f& size);
	virtual void SetOrigin(Origins origin);
	virtual void SetPos(const Vector2f& pos);
	virtual void SetRotation(float rotate);

	void SetFillColor(Color color);
	void SetString(const string& string);
	void SetFont(const Font& font);
};

