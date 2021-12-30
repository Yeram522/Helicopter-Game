#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Button.h"
#include <time.h>

class boardScript : public Behaviour
{
	clock_t start, current;
	int duration;

	Button* button;
	bool isStop;
public:
	boardScript(GameObject* gameObject) : Behaviour(gameObject)
	{
		button = gameObject->getComponent<Button>();
		
	}

	void stopTimer() { isStop = true;}
	void startTimer() { start = clock(); }

	void update() override {
		if (isStop) return;
		current = clock();
		duration = (double)(current - start) / CLOCKS_PER_SEC;

		string timetxt = "Time:" + to_string(duration) + "s";

		button->setText(timetxt);
	}
};

