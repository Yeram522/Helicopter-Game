#pragma once
#include <iostream>
#include "Input.h"
#include "GameObject.h"
#include "Position.h"
#include "Renderer.h"
#include "Component.h"
#include <functional>

using namespace std;

class Button : public Renderer
{
	string text;
public:
	Button(GameObject* gameObject)
		:Renderer(gameObject, nullptr, gameObject->getRenderer()->getDimension() + Position::ones) {}
	
	void setText(const string& text) { this->text = text; }
	string& getText() { return text; }

	void draw() override {
		Position pos = transform->local2World();
		screen->drawRectangle({ pos.x - 1, pos.y - 1 }, { dim.x, dim.y });
		if (text.length() == 0) return;
		screen->draw({ pos.x + 1, pos.y + 1 }, text.c_str());
	}

	bool isInside(const Position& pos)
	{
		return transform->getPosition().x < pos.x&& pos.x < transform->getPosition().x + getDimension().x
			&& transform->getPosition().y < pos.y&& pos.y < transform->getPosition().y + getDimension().y;
	}

	
};

