#include "TextObject.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"

TextObject::TextObject()
{
}

TextObject::~TextObject()
{
}

void TextObject::Init()
{
}

void TextObject::Update(float dt)
{
	text.setPosition(position);
}

void TextObject::Draw(RenderWindow& window)
{
	window.draw(text);
}

void TextObject::SetOrigin(Origins origin)
{
	Utils::SetOrigin(text, origin);
}

void TextObject::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	text.setPosition(position);
}

void TextObject::SetRotation(float rotate)
{
	Object::SetRotation(rotate);
	text.setRotation(rotation);
}

void TextObject::SetString(const string& string)
{
	text.setString(string);
}

void TextObject::SetFont(const Font& font)
{
	text.setFont(font);
}
