#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include <functional>

//이동하는맵의 스크립트
class MoveMapScript :
    public Behaviour
{
	float		speed;//맵이동 속도.: 짝수여야함!!!
	float	speedFlag;//맵이동 속도.
public:
	function<void(void)> movemapLeft;

	MoveMapScript(GameObject* gameObject) :Behaviour(gameObject), speed(0.5f),speedFlag(0.0f)
    {
		
    }

	void update() override
	{
		if (speedFlag - (int)speedFlag == 0)
		{
			movemapLeft();
		}
		
		speedFlag += speed;
	}

	float getSpeed() { return speed; }
};

