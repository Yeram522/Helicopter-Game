#pragma once
#include "Behaviour.h"
#include "Transform.h"
#include "Button.h"

class ButtonScript : public Behaviour
{
protected:
	Button* button;
public:
	function<void(void)> onClick;
	ButtonScript(GameObject* obj) : Behaviour(obj){
		button = obj->getComponent<Button>();
	
	}

	void update() override {
		if (!input->getMouseButtonDown(0)) return;
		auto pos = input->getMousePosition();
		if (button->isInside(pos)) { onClick();}
	}


};

